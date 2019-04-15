#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

int main(int argc,char **argv)
{	
	//if (argc > 1) {
		//
		//printf_s(str);
		//HANDLE hSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, argv[0]);
		//if (hSem)
		//{
			while (1)
			{
				//WaitForSingleObject(hSem, INFINITE);
					cout << GetCurrentProcessId() << endl;
					//Sleep(1000);
			//	ReleaseSemaphore(hSem, 1, NULL);
			}

		//}

	//}
	//exit(0);
}