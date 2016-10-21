#include "Liste.h"
#include "Timing.h"
#include "Professeur.h"
#include "Local.h"
#include "Groupe.h"
#include "Cours.h"
#include "SmartPointer.h"

using namespace std;

template<class type> Liste<type>::Liste()
{
	pStart = NULL;
}

template<class type> Liste<type>::Liste(const Liste& l)
{

}

template<class type> Liste<type>::~Liste()
{
	Cellule<type> *pWork = NULL;
	while(pWork != NULL)
	{
		pWork = pStart;
		pStart = pStart->pNext;
		delete pWork;
	}
}

template<class type> void Liste<type>::Affiche() const
{
	Cellule<type> *pWork = pStart;

	while(pWork != NULL)
	{
		cout << pWork->val << endl;
		pWork = pWork->pNext;
	}
}

template<class type> bool Liste<type>::estVide()
{
	if(pStart == NULL) 
		return true ;
	else
		return false;
}

template<class type> bool Liste<type>::existe(type& elem)
{
	Cellule<type> *pWork = NULL;
	pWork = pStart;

	while(pWork != NULL)
	{
		if(pWork->val == elem)
			return true;

		pWork = pWork->pNext;
	}

	return false;
}

template<class type> void Liste<type>::truncate()
{
	Cellule<type> *pWork = NULL, *pTemp = NULL;

	pWork = pStart;

	while(pWork != NULL)
	{
		pTemp = pWork->pNext;
		delete pWork;
		pWork = pTemp; 
	}	

	pStart = NULL;
}

template<class type> Cellule<type>* Liste<type>::getStartElement() const
{
	return pStart;
}

template<class type> int Liste<type>::getNombreElements() const
{
	Cellule<type> *pWork = pStart;
	int nbr = 0;
	while(pWork != NULL)
	{
		nbr++;
		pWork = pWork->pNext;
	}
	return nbr;
}

template<class type> Liste<type>& Liste<type>::operator=(const Liste<type>& l)
{
	Cellule<type> *pWork = NULL;
	pWork = l.getStartElement();

	while(pWork != NULL)
	{
		insere(pWork->val);
		pWork = pWork->pNext;
	}
}

template class Liste<char*>;
template class Liste<int>;
template class Liste<Timing>;
template class Liste<Professeur>;
template class Liste<Local>;
template class Liste<Groupe>;
template class Liste<Cours>;
template class Liste<SmartPointer<Groupe> >;
template class Liste<SmartPointer<Cours> >;