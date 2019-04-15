#ifndef ABSENT_EXCETION_H
#define ABSENT_EXCETION_H

#include <stdexcept>
#include <string>
namespace manager
{
	class AbsentException : std::logic_error
	{
	public:
		explicit AbsentException(const char* message);
		explicit AbsentException(std::string message);
		~AbsentException();
	};
}

#endif