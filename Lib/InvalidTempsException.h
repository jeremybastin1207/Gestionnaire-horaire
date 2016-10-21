#ifndef INVALIDTEMPSEXCEPTION
#define INVALIDTEMPSEXCEPTION
#include <iostream>
#include <stdlib.h>
#include <string.h>

class InvalidTempsException
{
private:
	char *message;

public:
	InvalidTempsException();
	InvalidTempsException(const char *);
	InvalidTempsException(const InvalidTempsException&);
	~InvalidTempsException();


	char * getMessage() const;
	void setMessage(const char *);

};
#endif