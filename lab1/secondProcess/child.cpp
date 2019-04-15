#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>

using namespace std;
int main(int argc, char *argv[])
{
	srand(time(0));
	cout << "This is children" << endl;
	cout << GetCurrentProcessId() << endl;

	char arr[10];
	ofstream file(argv[0]);

	for(int i=0; i<10; i++)
	{
		int x = rand()%10;
		cout << x << " ";
		arr[i] = x + '0';
		file << arr[i];
	}
	
	file.close();

	Sleep(10000);
	return 0;
}