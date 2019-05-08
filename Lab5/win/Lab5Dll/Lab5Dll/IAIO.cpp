#include <string>

using namespace std;

class IAIO
{
public:
	virtual int ConcatFiles(string source_folder_path, string output_file_path) = 0;
	virtual void Release() = 0;
	virtual ~IAIO()
	{
	}
};