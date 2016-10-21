#ifndef LIBTEMP
#define LIBTEMP

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "InvalidTempsException.h"

class Temps
{
    private:
      int minutes;
      int heures;
    public:
      Temps();
      Temps(int, int);
      Temps(const Temps &);
      Temps(int);
      
      //FONCTIONS
      void Affiche();
      void addMinutes(const int);      
      static int cmpHeure(const Temps&, const Temps&);

      //SETTERS
      void setMinute(const int);
      void setHeure(const int);

      //GETTERS
      int getMinute ()const;
      int getHeure()const;
      
      void Save(std::ostream&);
      void Load(std::istream&);

      //SURCHARGES
      Temps& operator=(const Temps&);
      Temps operator+(const int);
      Temps operator+(const Temps&);
      friend Temps operator+(int, Temps&);
      Temps operator-(const int);
      Temps operator-(const Temps&);
      friend Temps operator-(int, Temps&);
      int operator<(const Temps&);
      int operator<=(const Temps&);
      int operator>(const Temps&);
      int operator>=(const Temps&);
      int operator==(const Temps&);
      Temps operator++();
      Temps operator++(int);
      Temps operator--();
      Temps operator--(int);
      friend std::ostream& operator<<(std::ostream&,const Temps&);
      friend std::istream& operator>>(std::istream& i, Temps& t);

};
#endif