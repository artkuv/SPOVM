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
//	HANDLE printClient = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, "PrintClient");	//����� �������, ����������� ������������, ���
//
//	HANDLE conn;	//���������� �������� ��������
//	conn = OpenFileMappingA(FILE_MAP_ALL_ACCESS,	//����� �������
//		FALSE,									//���� ������������
//		"FileMap");								//���
//
//	PVOID buff = MapViewOfFile		//��������� ��������� �� ��������������� ������� ������
//	(conn,
//		FILE_MAP_ALL_ACCESS,		//����� ������� � ������� ������
//		0,							//������� ����� �������� �����
//		0,
//		50);						//����� ������������ ����
//
//	char string[50];
//
//	printf("%s\n", "PERSON");
//
//	while (TRUE)
//	{
//		if (WaitForSingleObject(printClient, 0) == WAIT_OBJECT_0)		//���� ����� ������
//		{
//			memset(string, '\0', 50);
//			strncpy_s(string, (char*)buff, 50);	//��������� ������ �� ������������ ������
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
//					printf("%c", string[i]);	//������������ ����� ������
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