#include "AllocationExeption.h"

using  namespace manager;

AllocationException::AllocationException(const char* message) : runtime_error(message)
{
}


AllocationException::AllocationException(std::string massage) : runtime_error(massage)
{
}

AllocationException::~AllocationException()
{
}