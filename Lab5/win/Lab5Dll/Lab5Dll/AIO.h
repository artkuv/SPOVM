#ifndef AIO_H
#define AIO_H

#ifndef IODLL_H
#define IODLL_H

//is done to import/export only public methods
#ifdef AIO_EXPORTS
//Enabled as "export" while compiling the dll project
#define AIO_API __declspec(dllexport)
#else
//Enabled as "import" in the Client side for using already created dll file
#define AIO_API __declspec(dllimport)
#endif

#endif

#include <string>
#include <vector>
#include <utility>
#include <Windows.h>
#include "IAIO.h"

namespace A_I_O
{

	class AIO : public IAIO
	{
	private:
	private:
		struct ThreadData
		{
			AIO* caller_instance;
			HANDLE file;
			int file_number;
			OVERLAPPED overlapped;
		};

		struct ReadFileData
		{
			int offset; //позиция для записывания
			int size;   //размер блока данных, который мы будем записывать
			char* data; //сопсна, сам блок данных
		};

	public:
		int ConcatFiles(std::string source_folder_path, std::string output_file_path);
		void Release();

	private:
		static DWORD WINAPI Read(LPVOID param); //служат как стартовая рутина для потоков
		static DWORD WINAPI Write(LPVOID param);

	private:
		void ReleaseData();
		std::vector<std::string> GetFilesFromSource(const std::string& source_folder);

	private:
		AIO(const AIO&) = delete;
		AIO& operator=(const AIO&) = delete;

	public:
		AIO();
		~AIO();

	private:
		int files_to_write_;
		std::vector<std::string> source_file_names_;
		std::string output_file_;

		std::vector<ThreadData*> thread_data_vector_;
		std::vector<ReadFileData*> read_files_data_;
		std::vector<HANDLE> read_events_;

		std::vector<HANDLE> reading_threads_;
		HANDLE writing_thread_;
	};

}

extern "C" AIO_API IAIO* __cdecl AIOFactory();

#endif