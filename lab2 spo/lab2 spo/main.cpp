#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <sstream>

using namespace std;

HANDLE hSem;

//int AddHandle(HANDLE* handles, HANDLE h1,int size)
//{
	/*size++;
	if(size == 2)
	handles[0] = h1;
	else
	{
		HANDLE* handles2 = new HANDLE[size+1];
		for (int i = 0; i < size-1; i++)
		{
			handles2[i] = handles[i];
		}
		handles2[size-1] = h1;
		handles = handles2;
	}*/
	/*size++;
	if(size == 1)
		handles[0] = h1;
	else{
		for (int i = size; i > 0; i--){
			handles[i] = handles[i-1];
		}
		handles[0] = h1;
	}*/
	//return size;
//}

int deleteProcess(HANDLE* handles, int size)
{
	if(size == 0)
		return 0;
	cout << TerminateProcess(handles[size], 0);
		size--;	
	//ReleaseSemaphore(hSem,1,NULL);
	return 0;
}

int main(int argc, char* argv[])
{
	char ch;
	int size = 0;
	HANDLE* handles = new HANDLE[100];
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	
	//hSem = CreateSemaphore(NULL, 1, 1, "MySemaphore");
	cout << "'+' - add process" << endl
		<< "'-' - kill process" << endl
		<< "'q' - exit" << endl;
	while (1) {
		cin >> ch;
		if (ch == 'q')
		{
			while (size) 
				deleteProcess(handles, size);
			exit(0);
		}
		if (ch == '+')
		{
			if (!CreateProcess("proc.exe",//argv[1],
				NULL, 
				NULL, 
				NULL, 
				TRUE,
				NULL, 
				NULL, 
				NULL, 
				&si, 
				&pi))
				cout << "Failed";

			//size = AddHandle(handles, pi.hProcess, size);
			handles[size] = pi.hProcess;
			size++;
			cout << size << endl;
		}
		if (ch == '-')
		{
			deleteProcess(handles, size);
			cout<< size << endl;
		}
	}
}
