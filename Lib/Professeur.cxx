#include "Professeur.h"

Professeur::Professeur()
{
	nom = NULL;
	prenom	= NULL;
	type = 'h';

	setNom("");
	setPrenom("");
}

Professeur::Professeur(const char* n, const char* p)
{
	nom = NULL;
	prenom = NULL;
	type= 'h';

	setNom(n);
	setPrenom(p);
}

Professeur::Professeur(const Professeur& p) : Planifiable(p)
{
	nom = NULL;
	prenom = NULL;

	setNom(p.getNom());
	setPrenom(p.getPrenom());
	type = p.type;
}

Professeur::~Professeur()
{
	if(nom) delete nom;
	if(prenom) delete prenom;
}

const void Professeur::Affiche()
{
	cout << nom << " " << prenom;
}

void Professeur::Save(ofstream& ofs)
{
	int length;

	length = strlen(nom) + 1;

	ofs.write((char*) &length, sizeof(int));
	ofs.write(nom, length);

	length = strlen(prenom) + 1;

	ofs.write((char*) &length, sizeof(int));
	ofs.write(prenom, length);
}

void Professeur::Load(ifstream& ifs)
{
	int length;
	char buffer[100];

	ifs.read((char*) &length, sizeof(int));
	ifs.read(buffer, length);

	setNom(buffer);

	ifs.read((char*) &length, sizeof(int));
	ifs.read(buffer, length);

	setPrenom(buffer);
}

void Professeur::setNom(const char *p)
{
	if(nom)
		delete(nom);

	nom = new char [strlen(p) + 1];
	strcpy(nom, p);
}
void Professeur::setPrenom(const char *p)
{
	if(prenom)
		delete(prenom);

	prenom = new char [strlen(p) + 1];
	strcpy(prenom, p);
}

char* Professeur::getIdentifiant()
{
	char *id = NULL;
	id = new char [strlen(nom) + strlen(prenom) + 2];
	strcpy(id, nom);
	strcat(id, ".");
	strcat(id, prenom);
	return id;
}

char* Professeur::getNom() const
{
	return nom;
}

char* Professeur::getPrenom() const
{
	return prenom;
}


int Professeur::operator<(const Professeur& p)
{
	int result = strcasecmp(p.getNom(), getNom());
	if(result == 0)
		result = strcasecmp(p.getPrenom(), getPrenom());

	if(result == 1)
		return 1;

	return 0;
}

int Professeur::operator>(const Professeur& p)
{
	int result = strcasecmp(getNom(), p.getNom());
	if(result == 0)
		result = strcasecmp(getPrenom(), p.getPrenom());

	if(result == 1)
		return 1;
	
	return 0;
}

int Professeur::operator==(const Professeur& p)
{

	if(strcmp(getNom(), p.getNom()) == 0 && strcmp(getPrenom(), p.getPrenom()) == 0)
		return 1;
	return 0; 
}

Professeur& Professeur::operator=(const Professeur& p)
{
	Planifiable::operator=(p);
	setPrenom(p.getPrenom());
	setNom(p.getNom());
	return *this;
}


istream& operator>>(istream& i, Professeur& p)
{
	char prenom[50];
	char nom[50];

	cout << "Nom : ";
	i >> nom;
	cout << "Prenom : ";
	i >> prenom;

	p.setPrenom(prenom);
	p.setNom(nom);
	return i;
}

ostream& operator<<(ostream& o, Professeur& p)
{
	o << p.prenom;
	o << " "; 
	o << p.nom;
	return o;
}
