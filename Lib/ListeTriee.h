#ifndef LISTETRIEE
#define LISTETRIEE

#include <stdlib.h>
#include <iostream>
#include "Liste.h"

using namespace std;

template <class type> class ListeTriee : public Liste<type>
{
private:

public:
	ListeTriee();
	ListeTriee(const ListeTriee&);
	~ListeTriee();
	type* insere(const type&);
};

#endif