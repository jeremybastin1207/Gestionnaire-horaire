#include "Planifiable.h"
#include "Cours.h"

Planifiable::Planifiable()
{

}

Planifiable::Planifiable(const Planifiable& p)
{
	setType(p.getType());
	cours = p.getCours();
}

Planifiable::~Planifiable()
{

}

const void Planifiable::Affiche() 
{
	if(type == 'h')
		cout << "Planifiable humain";
	else if(type == 'm')
		cout << "Planifiable matériel";
	else
		cout << "Type de planifiable non défini";

	cout << endl;
}

bool Planifiable::PossedeCours()
{
	return !cours.estVide();
}

void Planifiable::AjouterCours(Cours *pC)
{
	SmartPointer<Cours> sp(pC);

	cours.insere(sp);
}

void Planifiable::SupprimerCours(Cours *pC)
{
	Iterateur<SmartPointer<Cours> > itsc(cours);

	for(itsc.reset() ; !itsc.end() ; itsc++)
	{

		SmartPointer<Cours> sc = (SmartPointer<Cours>) itsc;
		Cours* c = sc.getValeur();

		if(c == pC)
		{
			sc.Delete();
			itsc.remove();
			break;
		}
	}
}

const ListeTriee<SmartPointer<Cours> >& Planifiable::getCours() const
{
	return cours;
}

char Planifiable::getType() const
{
	return type;
}

void Planifiable::setType(const char t)
{
	type = t;
}

Planifiable& Planifiable::operator=(const Planifiable& p)
{
	setType(p.getType());
	cours = p.getCours();

	return *this;
}