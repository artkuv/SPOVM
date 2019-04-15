
#include "MutexOperationsSet.h"

MutexOperationsSet::MutexOperationsSet()
{
	this->threadNumber = 0;
	currentThread = -1;	//������ ��������� ������
	this->hMutex = CreateMutex(NULL, FALSE, NULL);//�������� ������, true-������������ ���� �������� ���������,���

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
		this->args[i]->canClose = true;	//���������� ���� ���������� ��� ������� ������
	}
}

void MutexOperationsSet::addThread()
{
	if (this->COUNT == this->threadNumber) return;	//���� ���������� ������� - ��������

	args[this->threadNumber] = new ThreadArgs();	//��������� � ����������� ��� ������ ������
	args[this->threadNumber]->canClose = false;
	args[this->threadNumber]->cl = this;
	args[this->threadNumber]->number = this->threadNumber;	//����� ������

	threads[this->threadNumber] = getThread(args[this->threadNumber], MutexOperationsSet::threadFunction);//���������, ���� ������
	this->threadNumber++;
}


DWORD WINAPI MutexOperationsSet::printUniqueString(PVOID args)//���� ������
{
	ThreadArgs* ta = reinterpret_cast<ThreadArgs*>(args);	//�������� ��������� � ����������� ��� �������� ������

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

	HANDLE conn = OpenFileMappingA(FILE_MAP_ALL_ACCESS,	//����� �������
		FALSE,											//���� ������������
		"FileMap");										//���

	PVOID buff;				//��������� �� ��������������� ������� ������
	buff = MapViewOfFile(conn,	//���������� �������� ��������
		FILE_MAP_ALL_ACCESS,	//����� ������� � ������� ������
		0,						//������� ����� �������� �����
		0,
		50);					//����� ������������ ����	

	char empty[50];
	memset(empty, '\0', 50);	//������ ��� �������� ������ ����� ����������

	while (!ta->canClose)
	{
		//EnterCriticalSection(&this->section);	

		WaitForSingleObject(hMutex, INFINITE);
		WaitForSingleObject(endPrintServer, INFINITE);	

		CopyMemory(buff, empty, sizeof(empty));							   //�������� ������� ������
		CopyMemory(buff, strings[ta->number], strlen(strings[ta->number])); //������ � ������������ ������

		ReleaseSemaphore(printServer, 1, NULL);		

		//LeaveCriticalSection(&this->section);

		ReleaseMutex(hMutex);	//������������ ��������
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
	
	return CreateThread(&sa, 0, function, arg, 0, NULL);	//�������� ������������, ������ �����, ����� ��������� �������,
															//��-�� �� ���������, ���� ���������, ��-�� ��. ������
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