
#include "MutexOperationsSet.h"

MutexOperationsSet::MutexOperationsSet()
{
	this->threadNumber = 0;
	currentThread = -1;	//индекс активного потока
	this->hMutex = CreateMutex(NULL, FALSE, NULL);//атрибуты защиты, true-приобретение прав владения мьютексом,имя

	//InitializeCriticalSection(&this->section);
}

MutexOperationsSet::~MutexOperationsSet()
{
	CloseHandle(hMutex);

	//DeleteCriticalSection(&this->section);
}

void MutexOperationsSet::removeAll()
{
	for (int i = 0; i < this->threadNumber; i++)
	{
		this->args[i]->canClose = true;	//установить флаг завершения для каждого потока
	}
}

void MutexOperationsSet::addThread()
{
	if (this->COUNT == this->threadNumber) return;	//если количество потоков - максимум

	args[this->threadNumber] = new ThreadArgs();	//структура с аргументами для нового потока
	args[this->threadNumber]->canClose = false;
	args[this->threadNumber]->cl = this;
	args[this->threadNumber]->number = this->threadNumber;	//номер потока

	threads[this->threadNumber] = getThread(args[this->threadNumber], MutexOperationsSet::threadFunction);//аргументы, тело потока
	this->threadNumber++;
}


DWORD WINAPI MutexOperationsSet::printUniqueString(PVOID args)//тело потока
{
	ThreadArgs* ta = reinterpret_cast<ThreadArgs*>(args);	//получаем структуру с аргументами для текущего потока

	char strings[5][50] =
	{
		{ "FIRST string" },
		{ "SECOND string" },
		{ "THIRD string" },
		{ "FOURTH string" },
		{ "FIFTH string" }
	};

	HANDLE printServer = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, "PrintServer");
	if (printServer == NULL)
	{
		CloseHandle(printServer);
		cout << "ERROR (printServer) (" << GetLastError() << ")" << endl;
		_getch();
		return -1;
	}
	HANDLE endPrintServer = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, "EndPrintServer");
	if (printServer == NULL)
	{
		CloseHandle(endPrintServer);
		cout << "ERROR (endPrintServer) (" << GetLastError() << ")" << endl;
		_getch();
		return -1;
	}

	HANDLE conn = OpenFileMappingA(FILE_MAP_ALL_ACCESS,	//режим доступа
		FALSE,											//флаг наследования
		"FileMap");										//имя

	PVOID buff;				//указатель на спроецированную область памяти
	buff = MapViewOfFile(conn,	//дескриптор файловой проекции
		FILE_MAP_ALL_ACCESS,	//режим доступа к области памяти
		0,						//старшее слово смещения файла
		0,
		50);					//число отображаемых байт	

	char empty[50];
	memset(empty, '\0', 50);	//строка для передачи данных между процессами

	while (!ta->canClose)
	{
		//EnterCriticalSection(&this->section);	

		WaitForSingleObject(hMutex, INFINITE);
		WaitForSingleObject(endPrintServer, INFINITE);	

		CopyMemory(buff, empty, sizeof(empty));							   //очистить область памяти
		CopyMemory(buff, strings[ta->number], strlen(strings[ta->number])); //строка в отображаемую память

		ReleaseSemaphore(printServer, 1, NULL);		

		//LeaveCriticalSection(&this->section);

		ReleaseMutex(hMutex);	//освобождение мьютекса
		currentThread = ta->number;
	}

	delete ta;
	CloseHandle(endPrintServer);
	CloseHandle(printServer);
	CloseHandle(conn);
	return 0;
}

HANDLE MutexOperationsSet::getThread(ThreadArgs *arg, PTHREAD_START_ROUTINE function)
{	
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	
	return CreateThread(&sa, 0, function, arg, 0, NULL);	//атрибуты безопасности, размер стека, адрес потоковой функции,
															//ук-ль на параметры, флаг состояния, ук-ль ид. потока
}

DWORD WINAPI MutexOperationsSet::threadFunction(PVOID args)
{
	return (reinterpret_cast<ThreadArgs*>(args))->cl->printUniqueString(args);
}

void MutexOperationsSet::removeThread()
{
	if (this->threadNumber == 0) return;
	this->threadNumber--;
	args[this->threadNumber]->canClose = true;
}