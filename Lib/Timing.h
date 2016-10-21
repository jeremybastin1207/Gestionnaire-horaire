#ifndef LIBTIMING
#define LIBTIMING

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Temps.h"
#include "InvalidTimingException.h"

class Timing
{
	private:	
		Temps heure;
		Temps duree;
		char* jour;	
		int numDay(const char *);

	public:
		Timing();
		Timing(const char *, Temps , Temps);
		Timing(const Timing&);
		~Timing();
		
		void Affiche();
		int cmpTiming(const Timing&, const Timing&);
		void choisirJour();

		void setJour(const char *);
		void setHeure(const Temps);
		void setDuree(const Temps);
		void Save(std::ostream&);
		void Load(std::istream&);
		Temps getHeure() const;
		Temps getDuree() const;
		char* getJour() const;

	    int operator<(const Timing&);
	    int operator>(const Timing&);
	    int operator==(const Timing&);
		Timing& operator=(const Timing& _a);

		static const char *LUNDI;
		static const char *MARDI;
		static const char *MERCREDI;
		static const char *JEUDI;
		static const char *VENDREDI;
		static const char *SAMEDI;
		static const char *DIMANCHE;
		friend std::ostream& operator<< (std::ostream& c, const Timing& t);

};







#endif