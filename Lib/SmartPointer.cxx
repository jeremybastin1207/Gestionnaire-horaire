#include "SmartPointer.h"
#include "Cours.h" // Laisser cette inclusion afin que delete val puisse fonctionner
#include "Groupe.h"

using namespace std;

template<class T> SmartPointer<T>::SmartPointer()
{
	val = NULL;
}

template<class T> SmartPointer<T>::SmartPointer(T* t)
{
	val = t;
}


template<class T> SmartPointer<T>::SmartPointer(const SmartPointer& t)
{
	val = NULL;
	val = t.getValeur();
}

template<class T> SmartPointer<T>::~SmartPointer()
{

}

template<class T> void SmartPointer<T>::Delete()
{
	if(val) delete val;
}

template<class T> void SmartPointer<T>::setValeur(T* v)
{
	val = v;
}

template<class T> T* SmartPointer<T>::getValeur() const
{
	return val;
}

template<class T> int SmartPointer<T>::operator<(const SmartPointer& t)
{
	T t1, t2;

	t1 = *(val);
	t2 = *(t.getValeur());

	return t1 < t2;
}

template<class T> int SmartPointer<T>::operator>(const SmartPointer& t)
{
	T t1, t2;

	t1 = *(val);
	t2 = *(t.getValeur());

	return t1 > t2;
}

template<class T> int SmartPointer<T>::operator==(const SmartPointer& t)
{
	T t1, t2;

	t1 = *(val);
	t2 = *(t.getValeur());

	return t1 == t2;
}

template<class T> SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& t)
{
	val = NULL;
	setValeur(t.getValeur());
	return *this;
}

istream& operator>>(istream& i, SmartPointer<Cours>& sp)
{

}

ostream& operator<<(ostream& o, const SmartPointer<Cours>& sp)
{
	o << sp.getValeur() << endl;
}

istream& operator>>(istream& i, SmartPointer<Groupe>& sp)
{

}

ostream& operator<<(ostream& o, const SmartPointer<Groupe>& sp)
{
	o << sp.getValeur() << endl;
}

template class SmartPointer<int>;
template class SmartPointer<Cours>;
template class SmartPointer<Groupe>;