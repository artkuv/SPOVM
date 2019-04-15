#ifndef AINOUT_H
#define AINOUT_H

#include <aio.h>
#include <string>
#include <vector>
#include <utility>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/wait.h>

namespace A_I_O
{

	class AInOut
	{
	private:
		struct ReadFileData
		{
			int offset; //позиция записи
			int size;   //размер блока записи
			char* data; //сопсна, блок записи
			int* ready; //готов ли для записи
		};

	public:
		int ConcatFiles(std::vector<std::string> source_files, std::string output_file_path);

	private:
		static void* Read(void* arg);
		static void* Write(void* arg);
		static void ReadEndRoutine(sigval_t arg);
		static void WriteEndRoutine(sigval_t arg);

	private:
		void ReleaseData();
		int CreateSemaphoreSet(key_t key);
		void DeleteSemaphoreSet(int semid);

	private:
		AInOut(const AInOut&) = delete;
		AInOut& operator=(const AInOut&) = delete;

	public:
		AInOut();
		~AInOut();

	private:
		std::vector<std::string> source_file_names_;
		std::string output_file_;

		std::vector<aiocb*> thread_data_vector_;
		std::vector<ReadFileData*> read_files_data_;
		int files_to_write_;

		std::vector<pthread_t> reading_threads_;
		pthread_t writing_thread_;

	private:
		int semaphoreId;
		key_t semaphoreKey;

	private:
		static const int kWriteSemaphoreIndex;
		static const int kReadSemaphoreIndex;
		static short kSetArray[];
	};

}

#endif
