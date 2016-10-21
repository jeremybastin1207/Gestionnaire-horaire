#include "InvalidTimingException.h"

using namespace std;


InvalidTimingException::InvalidTimingException()
{
	message = NULL;
	setMessage("Erreur Inconnue");
}

InvalidTimingException::InvalidTimingException(const InvalidTimingException& e)
{
	message = NULL;
	setMessage(e.getMessage());
}

InvalidTimingException::InvalidTimingException(const char *s)
{
	message = NULL;
	setMessage(s);	
}

InvalidTimingException::~InvalidTimingException()
{
	if(message!= NULL) delete message;
}
void InvalidTimingException::setMessage(const char* s)
{
	if (message!= NULL) delete message;

	message = new char [strlen(s) + 1];
	strcpy(message, s);
}

char * InvalidTimingException::getMessage() const
{
	return message;
}