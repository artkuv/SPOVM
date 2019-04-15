#ifndef IAIO_H
#define IAIO_H

#include <string>

class IAIO
{
public:
	virtual int ConcatFiles(std::string source_folder_path, std::string output_file_path) = 0;
	virtual void Release() = 0;
	virtual ~IAIO();
};

#endif