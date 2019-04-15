#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;
int main(int argc, char *argv[])
{
	char buff[100];
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	//TCHAR SecondProcess[] = TEXT("secondProcess");
	ZeroMemory (&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	
	if (!CreateProcess(argv[1],
        argv[2],
        NULL,
        NULL,
        TRUE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi))
		printf("CreateProcess failed\n");

	WaitForSingleObject(pi.hProcess, 2000);

	cout << "This is parent" << endl;
	printf("Descr: %d\nID: %d\n", pi.hProcess, pi.dwProcessId);

	ifstream file(argv[2]);
	file >> buff;
	cout << buff;
	file.close();

	cout << endl;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
	return 0;
}