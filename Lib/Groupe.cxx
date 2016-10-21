#include "Groupe.h"

using namespace std;

Groupe::Groupe()
{
	categorie = NULL;
	setCategorie("");
	setNiveau(0);
	setNumero(0);
	type = 'm';
}

Groupe::Groupe(char* categorie, int niveau, int groupe)
{
	categorie = NULL;
	setCategorie(categorie);
	setNiveau(niveau);
	setNumero(groupe);
	type = 'm';
}

Groupe::Groupe(const Groupe& g) : Planifiable(g)
{
	categorie = NULL;
	setCategorie(g.getCategorie());
	setNiveau(g.getNiveau());
	setNumero(g.getNumero());
	type = g.type;
}

Groupe::~Groupe()
{
	if(categorie) delete categorie;
}

const void Groupe::Affiche()
{
	cout << "Categorie : " << categorie << endl;
	cout << "Niveau : " << niveau << endl;
	cout << "Numero : " << numero << endl;
}

void Groupe::Save(ofstream& ofs)
{
	int length;

	length = strlen(categorie) + 1;

	ofs.write((char*) &length, sizeof(int));
	ofs.write(categorie, length);

	ofs.write((char*) &niveau, sizeof(int));
	ofs.write((char*) &numero, sizeof(int));
}

void Groupe::Load(ifstream& ifs)
{
	int length;
	char buffer[100];

	ifs.read((char*) &length, sizeof(int));
	ifs.read((char*) buffer, length);
	setCategorie(buffer);

	ifs.read((char*) &length, sizeof(int));
	setNiveau(length);

	ifs.read((char*) &length, sizeof(int));
	setNumero(length);
}

void Groupe::setCategorie(const char* cat)
{
	if(categorie != NULL) delete categorie;

	categorie = new char[strlen(cat) + 1];

	strcpy(categorie, cat);
}

void Groupe::setNiveau(int niv)
{
	niveau = niv;
}

void Groupe::setNumero(int num)
{
	if (num >= 0)
		numero = num;
}

char* Groupe::getCategorie() const
{
	return categorie;
}

int Groupe::getNiveau() const
{
	return niveau;
}

int Groupe::getNumero() const
{
	return numero;
}

char* Groupe::getIdentifiant()
{
	char buffer[50];
	sprintf(buffer, "G%d", getNumero());
	char *re = new char[strlen(buffer) + 1];
	strcpy(re, buffer);
	return re;
}

int Groupe::operator<(const Groupe& g)
{
	if(getNumero() < g.getNumero())
		return 1;
	
	return 0;
}

int Groupe::operator>(const Groupe& g)
{
	if(getNumero() > g.getNumero())
		return 1;
	
	return 0;
}

int Groupe::operator==(const Groupe& g)
{
	if(getNumero() == g.getNumero())
		return 1;
	
	return 0;
}

Groupe& Groupe::operator=(const Groupe& g)
{
	Planifiable::operator=(g);
	setCategorie(g.getCategorie());
	setNiveau(g.getNiveau());
	setNumero(g.getNumero());
	return *this;
}

ostream& operator<<(ostream& o, const Groupe& g)
{
	o << "Categorie : " << g.getCategorie();
	o << ", niveau : " << g.getNiveau();
	o << ", numero : " << g.getNumero() << endl;
	return o;
}

istream& operator>>(istream& i, Groupe& groupe)
{
	int num;
	char buffer[100];

	cout << "Categorie : ";
	cin >> buffer;
	groupe.setCategorie(buffer);

	cout << "Niveau : ";
	cin >> num;
	groupe.setNiveau(num);

	cout << "Numero : ";
	i >> num;
	groupe.setNumero(num);
	return i;
}