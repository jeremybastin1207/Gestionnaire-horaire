#include "Timing.h"
using namespace std;

const char *Timing::LUNDI = "Lundi";
const char *Timing::MARDI = "Mardi";
const char *Timing::MERCREDI = "Mercredi";
const char *Timing::JEUDI = "Jeudi";
const char *Timing::VENDREDI = "Vendredi";
const char *Timing::SAMEDI = "Samedi";
const char *Timing::DIMANCHE = "Dimanche";
Timing::Timing()
{	
	jour = NULL;
	setJour(Timing::LUNDI);
	heure.setHeure(0);
	heure.setMinute(0);
	duree.setMinute(0);
	duree.setHeure(0);
}
Timing::Timing(const char *iniJour, Temps iniHeure, Temps iniDuree)
{
	jour = NULL;
	setHeure(iniHeure);
	setDuree(iniDuree);
	setJour(iniJour);
}
Timing::Timing(const Timing &t)
{	
	jour = NULL;
	setHeure(t.getHeure());
	setDuree(t.getDuree());
	setJour(t.getJour());
}
Timing::~Timing()
{
	if(jour != NULL) delete jour;
}
void Timing::setHeure(const Temps pTemps)
{
	heure.setHeure(pTemps.getHeure());
	heure.setMinute(pTemps.getMinute());
}
void Timing::setDuree(const Temps pTemps)
{
	duree.setHeure(pTemps.getHeure());
	duree.setMinute(pTemps.getMinute());
}
void Timing::setJour(const char *day)
{
	char *test;
	if(jour != NULL)
		delete jour;

	test = new char[strlen(day)+1];
	strcpy(test, day);
	if(numDay(test) == -1) throw InvalidTimingException("Le jour n'existe pas.");

	jour = new char [strlen(test)+1];
	strcpy(jour, test);
	delete test;
}
void Timing::Affiche()
{
	cout << "Jour : " << jour << endl;
	cout << "Heure : ";
	heure.Affiche();
	cout << endl << "Duree : ";
	duree.Affiche();
}
void Timing::Save(ostream &fichier)
{
    heure.Save(fichier);
	duree.Save(fichier);
	int lenght = strlen(getJour());
    fichier.write((char *)&lenght,sizeof(int));
    fichier.write((char *)jour, lenght);

}
void Timing::Load(istream &fichier)
{
	char buffer[100];
	int lenght;

	heure.Load(fichier);
	duree.Load(fichier);

    fichier.read((char *)&lenght, sizeof(int));
    fichier.read((char *)buffer, lenght);
    buffer[lenght] = '\0';
    setJour(buffer);
}
int Timing::numDay(const char * jour)
{
	if(strcasecmp(jour, LUNDI) == 0) return 1;
	if(strcasecmp(jour, MARDI) == 0) return 2;
	if(strcasecmp(jour, MERCREDI) == 0) return 3;
	if(strcasecmp(jour, JEUDI) == 0) return 4;
	if(strcasecmp(jour, VENDREDI) == 0) return 5;
	if(strcasecmp(jour, SAMEDI) == 0) return 6;
	if(strcasecmp(jour, DIMANCHE) == 0) return 7;
	
	return -1;
}
/*
t1 > t2 => 1
t1 < t2 => -1
t1 == t3 => 0*/
int Timing::cmpTiming(const Timing& t1, const Timing& t2)
{
	if(numDay(t1.getJour()) > numDay(t2.getJour()))
		return 1;
	if(numDay(t1.getJour()) < numDay(t2.getJour()))
		return -1;
	if(Temps::cmpHeure(t1.getHeure(), t2.getHeure()) == 1)
		return 1;
	if(Temps::cmpHeure(t1.getHeure(), t2.getHeure()) == -1)
		return -1;
	if(Temps::cmpHeure(t1.getDuree(), t2.getDuree()) == 1)
		return 1;
	if(Temps::cmpHeure(t1.getDuree(), t2.getDuree()) == -1)
		return -1;
	return 0;
}

void Timing::choisirJour()
{
	int choix;

	cout << "1. Lundi" << endl;
	cout << "2. Mardi" << endl;
	cout << "3. Mercredi" << endl;
	cout << "4. Jeudi" << endl;
	cout << "5. Vendredi" << endl;
	cout << "6. Samedi" << endl;
	cout << "7. Dimanche" << endl;
	cout << endl;

	do
	{	
		cout << "Veuillez choisir un jour : ";
		cin >> choix;
	}while(choix < 1 || choix > 7);

	switch(choix)
	{
		case 1:
			setJour(LUNDI);
		break;
		case 2:
			setJour(MARDI);
		break;
		case 3:
			setJour(MERCREDI);
		break;
		case 4:
			setJour(JEUDI);
		break;
		case 5:
			setJour(VENDREDI);
		break;
		case 6:
			setJour(SAMEDI);
		break;
		case 7:
			setJour(DIMANCHE);
		break;
	}
}

std::ostream& operator<< (std::ostream& c, const Timing& t)
{
  c << "Jour: "<<t.getJour() <<endl<<"Heure: " <<t.getHeure()<<endl << "Duree: " <<t.getDuree()<<endl;
  return c;
}
int Timing::operator<(const Timing&t)
{
  if(cmpTiming(*this, t) == -1)
    return 1;
  else
    return 0;
}
int Timing::operator>(const Timing&t)
{
  if(cmpTiming(*this, t) == 1)
    return 1;
  else
    return 0;
}
int Timing::operator==(const Timing&t)
{  
  if(cmpTiming(*this, t) == 0)
    return 1;
  else
    return 0;	
}

Timing& Timing::operator=(const Timing& _a)
{
	setJour(_a.getJour());
	setHeure(_a.getHeure());
	setDuree(_a.getDuree());

	return *this;
}

Temps Timing::getHeure() const
{
	return heure;
}
Temps Timing::getDuree() const
{
	return duree;
}
char * Timing::getJour() const
{
	return jour;
}