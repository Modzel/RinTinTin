#pragma once
#include "Exception.h"

class BadPackageException :
	public Exception
{
public:
	BadPackageException(void);
	~BadPackageException(void);

	void send();
};

