#include "BadPackageException.h"
#include <iostream>


BadPackageException::BadPackageException(void)
{
}


BadPackageException::~BadPackageException(void)
{
}

void BadPackageException::send() {
	//TODO narazie nic nie robimy z tym fantem, ogolnie mozna to ominac, albo wyslac informacje o zlym parsowaniu
	std::cout<<"Pakiet jest bardzo zly!\n";
}