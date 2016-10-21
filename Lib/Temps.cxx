#include "Temps.h"

using namespace std;

Temps::Temps()
{
  setHeure(0);
  setMinute(0);
}
Temps::Temps(const Temps& pTemps)
{
  setHeure(pTemps.getHeure());

  setMinute(pTemps.getMinute());
}
Temps::Temps(const int heur, const int min)
{
  setHeure(heur);
  setMinute(min);
}
Temps::Temps(const int min)
{
  setHeure(min/60);
  setMinute(min%60);
}
void Temps::Save(ostream& fichier)
{
    fichier.write((char *)&minutes, sizeof(int));
    fichier.write((char *)&heures, sizeof(int));
}
void Temps::Load(istream& fichier)
{
    fichier.read((char *)&minutes, sizeof(int));
    fichier.read((char *)&heures, sizeof(int));
}
void Temps::setMinute(const int min)
{
    minutes = min;
    if(minutes >= 60)
    {
      setHeure(getHeure()+(minutes / 60));
      minutes %= 60;
    }
    else if(minutes < 0)
    {
      setHeure(getHeure() + (minutes / 60) -1);
      minutes = 60 + (minutes % 60); 
    }
}

void Temps::setHeure(const int heur)
{

  if(heur < 0 || heur >= 24) throw InvalidTempsException("L'heure rentrée n'est pas correcte.");
  

  heures = heur;
  
}
int Temps::getMinute ()const
{
  return minutes;
}
int Temps::getHeure()const
{
  return heures;
}
void Temps::Affiche()
{
  cout << heures << ":" << minutes << endl;
}

int Temps::operator<(const Temps& t)
{
  if(cmpHeure(*this, t) == -1)
    return 1;
  else
    return 0;
}

int Temps::operator<=(const Temps& t)
{
  if(cmpHeure(*this, t) <= 0)
    return 1;
  else
    return 0;
}

int Temps::operator>(const Temps& t)
{
  if(cmpHeure(*this, t) == 1)
    return 1;
  else
    return 0;
}

int Temps::operator>=(const Temps& t)
{
  if(cmpHeure(*this, t) >= 0)
    return 1;
  else
    return 0;
}

/*
t1 > t2 => 1
t1 < t2 => -1
t1 = t2 => 0
*/
int Temps::cmpHeure(const Temps& t1, const Temps& t2)
{
  if(t1.getHeure() > t2.getHeure() )
    return 1;
  if(t1.getHeure() < t2.getHeure() )
    return -1;

  if(t1.getMinute() > t2.getMinute())
    return 1;
  if(t1.getMinute() < t2.getMinute())
    return -1;

  return 0;

}

Temps& Temps::operator=(const Temps& t)
{
  setHeure(t.getHeure());
  setMinute(t.getMinute());

  return *this;
}

int Temps::operator==(const Temps& t)
{
  if(cmpHeure(*this, t) == 0)
    return 1;
  else
    return 0;
}
std::ostream& operator<< (std::ostream& c, const Temps& t)
{
  c << t.getHeure() << ":" << t.getMinute();
  return c;
}
std::istream& operator>> (std::istream& i, Temps& t)
{
  int hours, minutes;
  char colon;
  i >> hours >> colon >> minutes;
  t.setHeure(hours);
  t.setMinute(minutes);
  return i;
}
Temps Temps::operator-(const int min)
{
  Temps t;
  t.setHeure(getHeure());
  t.setMinute(getMinute() - min);
  return t;
}

Temps Temps::operator-(const Temps& t)
{
  Temps n;
  n.setHeure(getHeure() - t.getHeure());
  n.setMinute(getMinute() - t.getMinute());
  return n;
}

Temps operator-(int min, Temps& t)
{
  Temps n;
  n.setHeure((min/60) - t.getHeure());
  n.setMinute((min%60) - t.getMinute());
  return n;

}
Temps Temps::operator+(const int min)
{
  Temps t;
  t.setHeure(getHeure());
  t.setMinute(getMinute() + min);
  return t;
}
Temps Temps::operator+(const Temps& t)
{
  Temps n;
  n.setHeure(t.getHeure() + getHeure());
  n.setMinute(t.getMinute() + getMinute());
  return n;
}
Temps operator+(int min, Temps& t)
{
  return t + min;
}
Temps Temps::operator--()//pré
{
  (*this).setMinute((*this).getMinute() - 30);
  return *this;
}
Temps Temps::operator--(int) //post
{
  Temps temp(*this);
  (*this).setMinute((*this).getMinute() - 30);
  return temp;

}
Temps Temps::operator++()//pré
{
  (*this).setMinute((*this).getMinute() + 30);
  return *this;
}
Temps Temps::operator++(int) //post
{
  Temps temp(*this);
  (*this).setMinute((*this).getMinute() + 30);
  return temp;

}