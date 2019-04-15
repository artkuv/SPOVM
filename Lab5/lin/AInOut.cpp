#include "AInOut.h"
#include <aio.h>
#include <iostream>
#include <csignal>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/unistd.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <exception>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <signal.h>

using namespace A_I_O;
using namespace std;

short AInOut::kSetArray[] = { 0, 0 };
const int AInOut::kWriteSemaphoreIndex = 1;
const int AInOut::kReadSemaphoreIndex = 0;

AInOut::AInOut()
{
	semaphoreKey = ftok("/dev/null", 38); //преобразовывает имя файла и идентификатор проекта в ключ для системных вызовов
	if (semaphoreKey == (key_t)-1)
	{
		throw runtime_error("ftok() error...");
	}

	semaphoreId = CreateSemaphoreSet(semaphoreKey);
	if (semaphoreId == -1)
	{
		throw runtime_error("Semaphore creation error...");
	}
}

int AInOut::CreateSemaphoreSet(key_t key)
{
	int id;
	int check = 0;

	id = semget(key, 2, IPC_CREAT| 0666 );
	if (id != -1)
	{
		check = semctl(id, 0, SETALL,                    //зануляем еще раз
			const_cast<short*>(this->kSetArray));        // SETALL ignores

														 // semnum (second) argument
	}

	return (check == -1) ? check : id;
}

AInOut::~AInOut()
{
	DeleteSemaphoreSet(this->semaphoreId);
}

void AInOut::DeleteSemaphoreSet(int semid)
{
	semctl(semid, 0, IPC_RMID, NULL);
}

void AInOut::ReleaseData() //сборка мусора
{
	for (auto &read_data : this->read_files_data_)
	{
		delete read_data->data;
		delete read_data;
	}

	for (auto &thread_data : this->thread_data_vector_)
	{
		delete thread_data;
	}

	this->thread_data_vector_.clear();
	this->read_files_data_.clear();

	for (auto &read_data : this->read_files_data_)
	{
		delete read_data;
	}

	this->read_files_data_.clear();
	this->reading_threads_.clear();
	this->writing_thread_ = 0;
}



int AInOut::ConcatFiles(std::vector<std::string> source_files, std::string output_file_path)
{
	this->files_to_write_ = 0;
	this->output_file_ = output_file_path;
	this->source_file_names_ = source_files;

	int offset = 0;
	for (auto &file_name : this->source_file_names_)
	{
		this->thread_data_vector_.push_back(new aiocb);  //для каждого файла новый aiocb, равная 0
		aiocb empty = { 0 }; 
		*this->thread_data_vector_.back() = empty;
		FILE* file = fopen(file_name.c_str(), "r");
		if (file == NULL)   //если не открыли файл, то просто пропускаем
		{
			cout << "Error while loading file..." << endl; 
			continue;
		}
		this->thread_data_vector_.back()->aio_fildes = fileno(file); //преобразуем в дескриптор
		struct stat file_info = { 0 };                               //описание файлового дескриптора
		fstat(thread_data_vector_.back()->aio_fildes, &file_info);   //получаем описание

		if (file_info.st_size == 0)
		{
			delete this->thread_data_vector_.back();
			this->thread_data_vector_.pop_back();
			fclose(file);
			continue;
		}

		this->read_files_data_.push_back(new ReadFileData);
		this->read_files_data_.back()->offset = offset;
		this->read_files_data_.back()->size = file_info.st_size;
		this->read_files_data_.back()->data = new char[file_info.st_size]; //память под буфер
		memset(this->read_files_data_.back()->data, 0, sizeof(char));
		this->read_files_data_.back()->data[0] = '\0'; //пока будет стоять \0 -- пустой блок данных

		this->thread_data_vector_.back()->aio_buf = this->read_files_data_.back()->data;
		this->thread_data_vector_.back()->aio_nbytes = file_info.st_size;
		this->thread_data_vector_.back()->aio_reqprio = 0;
		this->thread_data_vector_.back()->aio_offset = 0;
		this->thread_data_vector_.back()->aio_sigevent.sigev_notify = SIGEV_THREAD; //создаем поток, в котором будет выполняться ReadEndRoutine (завершение чтения)
		this->thread_data_vector_.back()->aio_sigevent.sigev_notify_function = AInOut::ReadEndRoutine;
		this->thread_data_vector_.back()->aio_sigevent.sigev_notify_attributes = NULL;
		this->thread_data_vector_.back()->aio_sigevent.sigev_value.sival_int = this->semaphoreId;

		pthread_t id; //поток читатель
		pthread_create(&id, NULL, AInOut::Read, reinterpret_cast<void*>(this->thread_data_vector_.back()));
		this->reading_threads_.push_back(id);

		offset += file_info.st_size;
		files_to_write_++;
	}
	pthread_create(&this->writing_thread_, NULL, AInOut::Write, reinterpret_cast<void*>(this)); //поток писатель

	//void** threadReciever = new void*;

	pthread_join(this->writing_thread_, NULL);

	this->ReleaseData();

	return this->thread_data_vector_.size();
}

void* AInOut::Write(void* arg)
{
	AInOut* caller_instance = reinterpret_cast<AInOut*>(arg); //parent

	vector<aiocb*> aio_data;

	FILE* output_file = fopen(caller_instance->output_file_.c_str(), "w");

	while (caller_instance->files_to_write_)
	{
		sembuf semaphoreSetr = { 0 };
		semaphoreSetr.sem_num = caller_instance->kReadSemaphoreIndex; //по сути, WaitForSingleObject
		semaphoreSetr.sem_op = -1;
		semaphoreSetr.sem_flg = 0;
		semop(caller_instance->semaphoreId, &semaphoreSetr, 1);

		semaphoreSetr.sem_num = caller_instance->kReadSemaphoreIndex;
		semaphoreSetr.sem_op = 1;
		semaphoreSetr.sem_flg = 0;
		semop(caller_instance->semaphoreId, &semaphoreSetr, 1);

		for (auto &element : caller_instance->read_files_data_)
		{
			if (element->data[0] != '\0') //если туда записали
			{
				aiocb empty = { 0 };

				aio_data.push_back(new aiocb);

				*aio_data.back() = empty;
				aio_data.back()->aio_buf = element->data;
				aio_data.back()->aio_fildes = fileno(output_file);
				aio_data.back()->aio_nbytes = element->size;
				aio_data.back()->aio_reqprio = 0;
				aio_data.back()->aio_offset = element->offset;
				aio_data.back()->aio_sigevent.sigev_notify = SIGEV_THREAD;
				aio_data.back()->aio_sigevent.sigev_notify_function = AInOut::WriteEndRoutine;
				aio_data.back()->aio_sigevent.sigev_notify_attributes = NULL;
				aio_data.back()->aio_sigevent.sigev_value.sival_int = caller_instance->semaphoreId;

				aio_write(aio_data.back());

				semaphoreSetr.sem_num = caller_instance->kReadSemaphoreIndex;
				semaphoreSetr.sem_op = -1;
				semaphoreSetr.sem_flg = 0;
				semop(caller_instance->semaphoreId, &semaphoreSetr, 1);
				caller_instance->files_to_write_--;
			}
		}
	}

	sembuf semaphoreSetw = { 0 };
	semaphoreSetw.sem_num = caller_instance->kWriteSemaphoreIndex;
	semaphoreSetw.sem_op = (int)((-1) * caller_instance->thread_data_vector_.size()); //сможем пройти, если семофор = общему колличеству файлов для чтения
	semaphoreSetw.sem_flg = 0;
	semop(caller_instance->semaphoreId, &semaphoreSetw, 1);

	for (auto &data : aio_data)
	{
		delete data;
	}

	fclose(output_file);

	return 0;
}

void AInOut::WriteEndRoutine(sigval_t arg)
{
	sembuf semaphoreSet = { 0 };
	semaphoreSet.sem_num = AInOut::kWriteSemaphoreIndex;
	semaphoreSet.sem_op = 1;
	semaphoreSet.sem_flg = 0;
	semop(arg.sival_int, &semaphoreSet, 1);
}

void AInOut::ReadEndRoutine(sigval_t arg) //нарастили индекс семафора чтения
{
	sembuf semaphoreSet = { 0 };
	semaphoreSet.sem_num = AInOut::kReadSemaphoreIndex;
	semaphoreSet.sem_op = 1;
	semaphoreSet.sem_flg = 0;
	semop(arg.sival_int, &semaphoreSet, 1);
}

void* AInOut::Read(void* arg)
{
	aiocb* thisAiocb = reinterpret_cast<aiocb*>(arg); //да, я опасен
	aio_read(thisAiocb);
	return 0;
}

extern "C" void PerformConcat(std::vector<std::string> source_files, std::string output_file_path)
{
	AInOut* object = new AInOut;
	object->ConcatFiles(source_files, output_file_path);
	delete object;
}
