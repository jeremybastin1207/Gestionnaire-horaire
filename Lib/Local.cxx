#include "Local.h"

using namespace std;

Local::Local(const char* n, const int nbr)
{
	nom = 0;
	type = 'm';
	setNom(n);
	setNbPlaces(nbr);
}

Local::Local()
{
	nom = 0;
	type = 'm';

	setNom("---");
	setNbPlaces(0);
}

Local::Local(const Local& l) : Planifiable(l)
{
	nom = 0;
	type = 'm';

	setNom(l.getNom());
	setNbPlaces(l.getNbPlaces());
}

Local::~Local()
{
	if(nom)
		delete nom;
}

const void Local::Affiche()
{
	cout << "Nom : " << nom << endl << "Nombre de places : " << nbPlaces << endl; 
}

void Local::Save(ofstream& ofs)
{
	int length;

	length = strlen(nom) + 1;

	ofs.write((char*) &length, sizeof(int));
	ofs.write((char*) nom, length);

	ofs.write((char*) &nbPlaces, sizeof(int));
}

void Local::Load(ifstream& ifs)
{
	int length;
	char buffer[100];

	ifs.read((char*) &length, sizeof(int));
	ifs.read(buffer, length);

	setNom(buffer);

	ifs.read((char*) &length, sizeof(int));

	setNbPlaces(length);
}

char* Local::getIdentifiant()
{
	char buffer[50];
	sprintf(buffer, "%s(%d)", getNom(), getNbPlaces());
	char *re = new char[strlen(buffer)+1];
	strcpy(re, buffer);
	return re;
}

void Local::setNom(const char *n)
{
	if(nom) delete nom;
	nom = new char[strlen(n)+1];
	strcpy(nom, n);
}

void Local::setNbPlaces(const int p)
{
	nbPlaces = p;
}

const char* Local::getNom() const 
{
	return nom;
}

const int Local::getNbPlaces() const
{
	return nbPlaces;
}

int Local::operator<(const Local& l)
{
	if(getNom() < l.getNom())
		return 1;
	return 0;
}

int Local::operator>(const Local& l)
{
	if(getNom() > l.getNom())
		return 1;

	return 0;
}

int Local::operator==(const Local& l)
{
	if(getNom() == l.getNom())
		return 1;
	return 0;
}

Local& Local::operator=(const Local& l)
{
	Planifiable::operator=(l);
	setNom(l.getNom());
	setNbPlaces(l.getNbPlaces());
	type = l.type;
	return *this;
}

std::ostream& operator<<(std::ostream& o, Local& l)
{
	o << l.getIdentifiant();
	return o;
}

std::istream& operator>>(std::istream& i, Local& l)
{
	int pl;
	char n[50];
	cout << "Nom : ";
	i >> n;
	cout << "Nombre de place : ";
	i >> pl;
	l.setNom(n);
	l.setNbPlaces(pl);
	return i;
}

