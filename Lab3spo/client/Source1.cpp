#include <windows.h>
#include <stdio.h>
#include <conio.h>

int main(int argc, char *argv[])
{
	HANDLE hSem;
	hSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, "MySemaphore");
	
	HANDLE hNamedPipe;
	DWORD  cbWritten;
	DWORD  cbRead;
	char   szBuf[256];
	char   szPipeName[256];

	printf("Syntax: pipec [servername]\n"); //?

	if (argc > 1)
		sprintf_s(szPipeName, "\\\\%s\\pipe\\$MyPipe$",
			argv[1]);
	else
		strcpy_s(szPipeName, "\\\\.\\pipe\\$MyPipe$");

	hNamedPipe = CreateFile(szPipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile: Error %ld\n", GetLastError());
		return 0;
	}

	printf_s("\nConnected. Type 'exit' to terminate\n");

	while (1)
	{
		printf("cmd>");
		gets_s(szBuf);
		
		//WaitForSingleObject(hSem, INFINITE);
		if (!WriteFile(hNamedPipe, szBuf, strlen(szBuf) + 1, &cbWritten, NULL))
			break;
		if (ReadFile(hNamedPipe, szBuf, 512, &cbRead, NULL))
			printf("Received back: <%s>\n", szBuf);

		else
		{
			printf("ReadFile: Error %ld\n",	GetLastError());
			break;
		}
		//ReleaseSemaphore(hSem, 1, NULL);
		
		if (!strcmp(szBuf, "exit"))
			break;
	}

	CloseHandle(hNamedPipe);
	return 0;
}
