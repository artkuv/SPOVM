//
//#define _CRT_SECURE_NO_WARNINGS
//#include <windows.h>
//#include <iostream>
//#include <conio.h>
//#include <string.h>
//
//using namespace std;
//
//int main(int argc, char* argv[])
//{
//	HANDLE printServer = CreateSemaphoreA(NULL, 0, 1, "PrintServer");		//0-начальное состояние 
//	HANDLE endPrintServer = CreateSemaphoreA(NULL, 1, 1, "EndPrintServer");	//1-начальное состояние
//
//	//Cоздание файловой проекции (дескриптор):
//	HANDLE conn = CreateFileMappingA(INVALID_HANDLE_VALUE,	//для выделения общей области памяти (проецируемый файл - системный файл подкачки)	
//		NULL,												//атрибуты безопасности	
//		PAGE_READWRITE,										//флаги защиты выделенной области
//		0,													//старшее слово размера (4Б)
//		50,													//младшее слово размера
//		"FileMap");											//уникальное имя
//
//	PVOID buff = MapViewOfFile		//получение указателя на спроецированную область памяти
//	(conn,
//		FILE_MAP_ALL_ACCESS,		//режим доступа к области памяти
//		0,							//старшее слово смещения файла
//		0,
//		50);						//число отображаемых байт
//
//	STARTUPINFOA si;
//	PROCESS_INFORMATION procInf;
//	ZeroMemory(&si, sizeof(STARTUPINFO));
//	si.cb = sizeof(STARTUPINFO);
//	ZeroMemory(&procInf, sizeof(PROCESS_INFORMATION));
//	if (!CreateProcessA(NULL, "Main.exe", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &procInf))
//	{
//		cout << "Create Process failed:" << GetLastError() << endl;
//		CloseHandle(printServer);
//		CloseHandle(endPrintServer);
//		CloseHandle(conn);
//		return -1;
//	}
//
//	char str[50];
//
//	while (TRUE)
//	{
//		if (WaitForSingleObject(printServer, 200) == WAIT_OBJECT_0)		//если можно писать
//		{
//			memset(str, '\0', 50);
//			strncpy_s(str, (char*)buff, 50);
//
//			for (int i = 0; i < strlen(str); i++)
//			{
//				printf("%c", str[i]);	//посимвольный вывод строки
//				Sleep(60);
//			}
//			
//			printf("\n");
//			ReleaseSemaphore(endPrintServer,1,NULL);		//строка дописана				
//		}
//		if (WaitForSingleObject(procInf.hProcess, 200) == WAIT_OBJECT_0)	//если дочерний процесс завершился
//		{
//			break;
//		}
//	}
//
//	CloseHandle(printServer);
//	CloseHandle(endPrintServer);
//	CloseHandle(conn);
//	CloseHandle(procInf.hProcess);
//	CloseHandle(procInf.hThread);
//
//	return 0;
//}