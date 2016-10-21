#include "InvalidTempsException.h"

using namespace std;

InvalidTempsException::InvalidTempsException()
{
	message = NULL;
	setMessage("Erreur Inconnue");
}

InvalidTempsException::InvalidTempsException(const InvalidTempsException& e)
{
	message = NULL;
	setMessage(e.getMessage());
}

InvalidTempsException::InvalidTempsException(const char *s)
{
	message = NULL;
	setMessage(s);	
}

InvalidTempsException::~InvalidTempsException()
{
	if(message!= NULL) delete message;
}
void InvalidTempsException::setMessage(const char* s)
{
	if (message!= NULL) delete message;

	message = new char [strlen(s) + 1];
	strcpy(message, s);
}

char * InvalidTempsException::getMessage() const
{
	return message;
}