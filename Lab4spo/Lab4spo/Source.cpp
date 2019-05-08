#include<Windows.h>
#include<iostream>
#include<thread>

using namespace std;

CRITICAL_SECTION csection;
int id = 0;

DWORD WINAPI ThreadProc(LPVOID LParam) {
	while (id < 8)
	{
		EnterCriticalSection(&csection);
		cout << "Work thread " << GetCurrentThreadId() << endl;
		LeaveCriticalSection(&csection);
		WaitForSingleObject(GetCurrentThread(), 1000);
	}
	ExitThread(0);
	return 0;
}

int main() {

	InitializeCriticalSection(&csection);
	char ch;
	DWORD thid = 1000;
	HANDLE ArrayOfThreads[8];
	cout << "+ - Create Thread" << endl
		<< "- - Kill Thread " << endl
		<< "q - Exit" << endl;
	while (1)
	{
		cin >> ch;
		if (ch == 'q')
		{
			DeleteCriticalSection(&csection);
			for (byte i = 0; i < id; i++)
			{
				TerminateThread(ArrayOfThreads[id - 1], 0);
			}
			exit(0);
		}
		if (ch == '+')
		{
			if (id < 8)
			{
				id++;
				thid += id;
				ArrayOfThreads[id - 1] = CreateThread(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, &thid);
				cout << "start thread  " << GetThreadId(ArrayOfThreads[id - 1]) << endl;
				ResumeThread(ArrayOfThreads[id - 1]);
			}
		}
		if (ch == '-')
		{
			if (id > 0)
			{
				cout << "kill thread " << GetThreadId(ArrayOfThreads[id - 1]) << endl;
				TerminateThread(ArrayOfThreads[id - 1], 0);
				id--;
			}
			else
				cout << "No threads" << endl;
		}
	}
	return 0;
}

