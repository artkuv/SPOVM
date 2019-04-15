#include <iostream>
#include "MutexOperationsSet.h"
#include <conio.h>

int main(int argc, char** argv)
{
	MutexOperationsSet* set = new MutexOperationsSet();
	bool flagEnd = 0;

	cout << "+ -- Add new thread\n- -- remove thread\nq -- close program" << endl;

	while (!flagEnd)
	{
		switch (_getch())
		{
		case '+':
			set->addThread();
			break;
		case '-':
			set->removeThread();
			break;
		case 'q':
			set->removeAll();
			flagEnd = 1;
		}
	}

	cin.ignore();
	delete set;
	return 0;
}