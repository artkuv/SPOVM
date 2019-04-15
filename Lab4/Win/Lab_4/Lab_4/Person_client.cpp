//#include <windows.h>
//#include <iostream>
//#include <conio.h>
//#include <ctime>
//
//using namespace std;
//
//void printString()
//{
//	HANDLE hPrint = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, "CanWriteSemaphore");
//
//
//	HANDLE printClient = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, "PrintClient");	//права доступа, возможность наследования, имя
//
//	HANDLE conn;	//дескриптор файловой проекции
//	conn = OpenFileMappingA(FILE_MAP_ALL_ACCESS,	//режим доступа
//		FALSE,									//флаг наследования
//		"FileMap");								//имя
//
//	PVOID buff = MapViewOfFile		//получение указателя на спроецированную область памяти
//	(conn,
//		FILE_MAP_ALL_ACCESS,		//режим доступа к области памяти
//		0,							//старшее слово смещения файла
//		0,
//		50);						//число отображаемых байт
//
//	char string[50];
//
//	printf("%s\n", "PERSON");
//
//	while (TRUE)
//	{
//		if (WaitForSingleObject(printClient, 0) == WAIT_OBJECT_0)		//если можно писать
//		{
//			memset(string, '\0', 50);
//			strncpy_s(string, (char*)buff, 50);	//получение строки из отображаемой памяти
//
//			while (TRUE)
//			{
//				for (int i = 0; i < strlen(string); i++)
//				{
//					if (_kbhit())
//					{
//						_getch();
//						return;
//					}
//
//					printf("%c", string[i]);	//посимвольный вывод строки
//					Sleep(80);
//				}
//				printf("\n");
//			}
//		}
//	}
//	return;
//}
//
//int main(int argc, char* argv[])
//{
//	printString();
//	return 0;
//}