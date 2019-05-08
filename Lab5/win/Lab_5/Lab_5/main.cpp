#include <iostream>
#include "IAIO.cpp"

typedef IAIO* (*__cdecl  AIOFactoryMethod)();

int main()
{
	BOOL freeResult, runTimeLinkSuccess = FALSE;
	HINSTANCE dllHandle = NULL;
	AIOFactoryMethod AIOFactory = NULL;

	//Load the dll and keep the handle to it
	dllHandle = LoadLibraryA("Lab5Dll.dll");
	// If the handle is valid, try to get the function address. 
	if (NULL != dllHandle)
	{
		//Get pointer to our function using GetProcAddress:
		AIOFactory = (AIOFactoryMethod)GetProcAddress(dllHandle,
			"AIOFactory");

		// If the function address is valid, call the function. 
		if (runTimeLinkSuccess = (NULL != AIOFactory))
		{
			IAIO* async_read_write_pointer = AIOFactory();

			cout << "Starting processing..." << endl;

			async_read_write_pointer->ConcatFiles("Files_to_read", "output.txt");

			// Is necessary to use to release class object (just like using delete to free dynamicly allocated memory)
			async_read_write_pointer->Release();

			cout << "The task was executed..." << endl;
			cout << "Press any key to continue..." << endl;
		}

		//Free the library:
		freeResult = FreeLibrary(dllHandle);
	}

	//If unable to call the DLL function, use an alternative. 
	if (!runTimeLinkSuccess)
	{
		cout << "Unable to call dll function" << endl;
		if (NULL != dllHandle)
		{
			freeResult = FreeLibrary(dllHandle);
		}
	}

	cin.ignore();

	return 0;
}