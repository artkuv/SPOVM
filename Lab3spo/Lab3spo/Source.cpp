#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
using namespace std;
HANDLE hSem;

int main(int argc, char** argv)
{
	/*if (argc < 3)
	{
		argv[1] = "MySemaphore";
		argv[2] = "\\\\.\\pipe\\$MyPipe$";
	}*/
	//char * name = "MySemaphore";
	hSem = CreateSemaphore(NULL, 1, 1, argv[1]);
	DWORD  cbRead;
	DWORD  cbWritten;
	HANDLE handle;
	//char *str = "\\\\.\\pipe\\$MyPipe$";
	char bufer[256];
	handle = CreateNamedPipe(argv[2], PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 512, 512, 1000, NULL);

	if (handle == INVALID_HANDLE_VALUE)// == 0
	{
		printf("CreateNamedPipe: Error %ld\n", GetLastError());
		return 1;
	}
	printf("Waiting for connect...\n");

	printf("\nConnected. Waiting for command...\n");
	while (1)
	{
		if (ReadFile(handle, bufer, 512, &cbRead, NULL))
		{
			//ReleaseSemaphore(hSem, 1, NULL);
			//WaitForSingleObject(hSem, INFINITE);
			if (!WriteFile(handle, bufer, strlen(bufer) + 1, &cbWritten, NULL))
				break;
			printf("Received: <%s>\n", bufer);
			Sleep(3000);
			if (!strcmp(bufer, "exit"))
				break;
		}
		else
		{
			printf("ReadFile: Error %ld\n", GetLastError());
			_getch();
			break;
		}
	}
	return 0;
}