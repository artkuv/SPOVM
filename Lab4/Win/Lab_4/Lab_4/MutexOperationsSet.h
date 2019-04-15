#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <conio.h>
#include <ctime>

using namespace std;

class MutexOperationsSet
{
	HANDLE hMutex;

	int threadNumber;
	//CRITICAL_SECTION section;
	static const int COUNT = 5;
	HANDLE threads[COUNT];
	DWORD WINAPI printUniqueString(PVOID args);
	static DWORD WINAPI threadFunction(PVOID args);
public:
	MutexOperationsSet();
	~MutexOperationsSet();
	void addThread();
	void removeThread();
	void removeAll();
private:
	struct ThreadArgs 
	{
		MutexOperationsSet *cl;
		bool canClose;//флаг закрытия потока
		int number;//номер потока
	}* args[COUNT];

	HANDLE getThread(ThreadArgs *arg, PTHREAD_START_ROUTINE function);
	int currentThread;//номер текущего потока
};

