#include <vector>
#include <utility>
#include <Windows.h>
#include "IAIO.cpp"

class AIO : public IAIO
{
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
		char* data; //сам блок данных
	};

public:
	int ConcatFiles(string source_folder_path, string output_file_path);
	void Release();
	static DWORD WINAPI Read(LPVOID param); //служат как стартовая рутина для потоков
	static DWORD WINAPI Write(LPVOID param);
	void ReleaseData();
	vector<string> GetFilesFromSource(const string& source_folder);
	AIO(const AIO&) = delete;
	AIO& operator=(const AIO&) = delete;
	AIO();
	~AIO();
	int files_to_write_;
	vector<string> source_file_names_;
	string output_file_;
	vector<ThreadData*> thread_data_vector_;
	vector<ReadFileData*> read_files_data_;
	vector<HANDLE> read_events_;
	vector<HANDLE> reading_threads_;
	HANDLE writing_thread_;
};