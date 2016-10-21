#ifndef DEF_EVENT
#define DEF_EVENT
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Temps.h"
#include "Timing.h"
class Event
{
  private :
	int code;
	char *intitule;
	char *lieu;
	Timing heure;
  public:
	
	Event();
	Event(const int c, const char *pInti, const char *pLieu);
	Event(const Event& pEvent);
	~Event();

	void setCode(const int c);
	void setIntitule(const char *n);
	void setLieu(const char *n);
	void setTiming(const Timing);

	void Save(std::ostream&);
	void Load(std::istream&);
	Timing getTiming() const;
	int getCode() const;
	char* getLieu()const;
	char* getIntitule()const;

	void Affiche();
	static int codeCourant;

	Event& operator=(const Event& e);
};

#endif
