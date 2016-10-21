#include "Event.h"

using namespace std;

int Event::codeCourant = 0;

Event::Event()
{
	intitule = NULL;
	lieu = NULL;
	setIntitule("");
	setCode(0);
	setLieu("");

}
Event::Event(const int c, const char *pInti, const char *pLieu)
{
	intitule = NULL;
	lieu = NULL;
	setCode(c);
	setIntitule(pInti);
	setLieu(pLieu);

}
Event::Event(const Event& pEvent)
{
	intitule = NULL;
	lieu = NULL;
	setCode(pEvent.getCode());
	setIntitule(pEvent.getIntitule());
	setLieu(pEvent.getLieu());
	setTiming(pEvent.getTiming());
}
Event::~Event()
{
	if (intitule) delete intitule;
	if (lieu) delete lieu;
}
void Event::Save(ostream& fichier)
{
    fichier.write((char *)&code, sizeof(int));
	
	int length = strlen(getIntitule());

    fichier.write((char *)&length, sizeof(int));
    fichier.write((char *)intitule, length);

    length = strlen(getLieu());
    fichier.write((char *)&length,sizeof(int));

    fichier.write((char *)lieu, length);
    heure.Save(fichier);
}
void Event::Load(istream& fichier)
{
    char buffer [100];
	int lenght;

    fichier.read((char *)&code, sizeof(int));

    fichier.read((char *)&lenght, sizeof(int));
    fichier.read((char *)buffer, lenght);
    buffer[lenght] = '\0';
    setIntitule(buffer);

    fichier.read((char *)&lenght, sizeof(int));
    fichier.read((char *)buffer, lenght);
    buffer[lenght] = '\0';
    setLieu(buffer);

    heure.Load(fichier);
   }
void Event::setCode(const int c)
{
	if(c >= 0)
		code = c;
}
void Event::setIntitule(const char *n)
{
	if(intitule)
		delete intitule;
	intitule = new char [strlen(n)+1];
	strcpy(intitule, n);
}
void Event::setLieu(const char *n)
{
	if(lieu)
		delete lieu;
	lieu = new char [strlen(n)+1];
	strcpy(lieu, n);
}

int Event::getCode() const
{
	return code;
}
 
char* Event::getLieu() const
{
	return lieu;
}

char* Event::getIntitule() const
{
	return intitule;
}
void Event::Affiche()
{
	cout << "Code : " << code << endl;
	cout << "Intitule : " << intitule << endl;
	cout << "Lieu : " << lieu << endl;	
	cout << "Timing : " ;
	heure.Affiche(); 
}
void Event::setTiming(const Timing t)
{
	heure = t;
}

Timing Event::getTiming() const
{
	return heure;
}

Event& Event::operator=(const Event& e)
{
	setCode(e.getCode());
	setIntitule(e.getIntitule());
	setLieu(e.getLieu());
	setTiming(e.getTiming());

	return *this;
}

