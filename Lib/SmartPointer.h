#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <iostream>

class Cours;
class Groupe;

template<class T>
class SmartPointer
{
private:
	T* val;
public:
	SmartPointer();
	SmartPointer(T*);
	SmartPointer(const SmartPointer&);
	~SmartPointer();

	void Delete();
	void setValeur(T* v);
	T* getValeur() const;

	int operator<(const SmartPointer&);
	int operator>(const SmartPointer&);
	int operator==(const SmartPointer&);
	SmartPointer<T>& operator=(const SmartPointer<T>&);

	friend std::istream& operator>>(std::istream&, SmartPointer<Cours>&);
	friend std::ostream& operator<<(std::ostream&, const SmartPointer<Cours>&);
	friend std::istream& operator>>(std::istream&, SmartPointer<Groupe>&);
	friend std::ostream& operator<<(std::ostream&, const SmartPointer<Groupe>&);
};

#endif