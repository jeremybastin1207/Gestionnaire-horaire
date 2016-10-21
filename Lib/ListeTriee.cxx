#include "ListeTriee.h"
#include "Timing.h"
#include "Professeur.h"
#include "Local.h"
#include "Groupe.h"
#include "Cours.h"
#include "SmartPointer.h"

template <class type> ListeTriee<type>::ListeTriee()
{

}

template <class type> ListeTriee<type>::ListeTriee(const ListeTriee& l)
{
	*this = l;
}

template <class type> ListeTriee<type>::~ListeTriee()
{

}

template <class type> type* ListeTriee<type>::insere(const type& val)
{
	Cellule<type> *pNew = new Cellule<type>;
	pNew->val = val;
	pNew->pNext = NULL;

	if(this->estVide())
	{
		this->pStart = pNew;
	}
	else
	{
		Cellule<type> *pWork = this->pStart;
		Cellule<type> *pPrec = NULL;

		while(pWork!= NULL && pNew->val > pWork->val)
		{
			pPrec = pWork;
			pWork = pWork->pNext; 
		}

		if(pPrec == NULL)
		{
			pNew->pNext = this->pStart;
			this->pStart = pNew;
		}
		else
		{
			pNew->pNext = pWork;
			pPrec->pNext = pNew;
		}

	}
	
	return &pNew->val;
}

template class ListeTriee<char*>;
template class ListeTriee<int>;
template class ListeTriee<Timing>;
template class ListeTriee<Professeur>;
template class ListeTriee<Local>;
template class ListeTriee<Groupe>;
template class ListeTriee<Cours>;
template class ListeTriee<SmartPointer<Groupe> >;
template class ListeTriee<SmartPointer<Cours> >;