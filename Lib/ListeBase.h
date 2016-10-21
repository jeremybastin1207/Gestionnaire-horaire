#ifndef LISTEBASE
#define LISTEBASE

#include <stdlib.h>
#include <iostream>

#include "Liste.h"

using namespace std;

template <class type> class ListeBase : public Liste<type>
{
private:

public:
	type* insere(const type&);
};

#endif