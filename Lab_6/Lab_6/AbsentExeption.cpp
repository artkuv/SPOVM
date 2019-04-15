#include "AbsentExeption.h"

using namespace manager;

AbsentException::AbsentException(const char* message) : logic_error(message)
{
}

AbsentException::AbsentException(std::string massage) : logic_error(massage)
{
}

AbsentException::~AbsentException()
{
}