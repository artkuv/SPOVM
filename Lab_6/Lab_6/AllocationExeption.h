#ifndef ALLOCATION_EXCEPTION_H
#define ALLOCATION_EXCEPTION_H

#include <stdexcept>
#include <string>
namespace manager
{
	class AllocationException : public std::runtime_error
	{
	public:
		explicit AllocationException(const char* message);
		explicit AllocationException(std::string message);
		~AllocationException();
	};
}

#endif