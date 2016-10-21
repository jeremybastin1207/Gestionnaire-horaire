#include "Iterateur.h"
#include "Professeur.h"
#include "Groupe.h"
#include "Local.h"
#include "Cours.h"
#include "Timing.h"
#include "SmartPointer.h"

using namespace std;

template<class T> Iterateur<T>::Iterateur(Liste<T>& _liste) : liste(_liste)
{
	pPosition = NULL;
	pPrevious = NULL;
}

template<class T> void Iterateur<T>::reset()
{
	pPosition = liste.pStart;
	pPrevious = NULL;
}

template<class T> T& Iterateur<T>::get(int position)
{
	int i;

	reset();

	for(i = 0; i < position; i++)
	{
		pPosition = pPosition->pNext;
	}

	return pPosition->val;
}

template<class T> bool Iterateur<T>::end()
{
	return (pPosition == NULL);
}

template<class T> T Iterateur<T>::remove()
{
	//T value = pPosition->val; throwing an instance of 'InvalidTimingException en utilisant la fonction
	T value;

	if(pPrevious != NULL)
		pPrevious->pNext = pPosition->pNext;
	else
		liste.pStart = pPosition->pNext;

	delete pPosition;

	return value;
}

template<class T> void Iterateur<T>::operator++(int)
{
	Cellule<T>* temp = pPosition;
	pPrevious = pPosition;
	pPosition = pPosition->pNext;
}

template<class T> Iterateur<T>::operator T() const
{
	return pPosition->val;
}

template<class T> T* Iterateur<T>::operator&()
{
	return &pPosition->val;
}

template class Iterateur<char*>;
template class Iterateur<int>;
template class Iterateur<Timing>;
template class Iterateur<Professeur>;
template class Iterateur<Groupe>;
template class Iterateur<Local>;
template class Iterateur<Cours>;
template class Iterateur<SmartPointer<Groupe> >;
template class Iterateur<SmartPointer<Cours> >;
