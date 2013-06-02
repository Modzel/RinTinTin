#include "Exception.h"
#include <iostream>

Exception::Exception(void)
{
}


Exception::~Exception(void)
{
}

Exception::Exception(std::string message) {
	this->message = message;
}