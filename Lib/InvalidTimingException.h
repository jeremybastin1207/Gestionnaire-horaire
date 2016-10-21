#ifndef INVALIDTIMINGEXCEPTION
#define INVALIDTIMINGEXCEPTION

#include <iostream>
#include <stdlib.h>
#include <string.h>

class InvalidTimingException
{
private:
	char *message;

public:
	InvalidTimingException();
	InvalidTimingException(const char *);
	InvalidTimingException(const InvalidTimingException&);
	~InvalidTimingException();


	char * getMessage() const;
	void setMessage(const char *);

};
#endif