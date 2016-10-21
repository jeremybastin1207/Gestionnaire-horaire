#include "ListeBase.h"
#include "Timing.h"

template <class type> type* ListeBase<type>::insere(const type& val)
{
	Cellule<type>* pNew = new Cellule<type>;
	Cellule<type>* pWork = this->pStart;
	pNew->val = val;
	pNew->pNext = this->pStart;
	this->pStart = pNew;
	return &pNew->val;
}

template class ListeBase<int>;
template class ListeBase<Timing>;