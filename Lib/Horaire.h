#ifndef HORAIRE_H
#define HORAIRE_H

#include <fstream>
#include <iostream>
#include <string.h>
#include <iomanip>
#include "ListeTriee.h"
#include "Groupe.h"
#include "Local.h"
#include "Planifiable.h"
#include "Professeur.h"
#include "Cours.h"
#include "Timing.h"
#include "Temps.h"


class Horaire
{
private:
	ListeTriee<Professeur> professeurs;
	ListeTriee<Groupe> groupes;
	ListeTriee<Local> locaux;
	ListeTriee<Cours> courses;

	char* horaire;

public:
	Horaire();
	~Horaire();

	int selectMenu();
	void executeAction(int choix);

	void createHoraire();
	void openHoraire();
	void saveHoraire();
	void closeHoraire();

	void addElement();
	void importElement();
	void showElements();
	void deleteElement();

	void showCours(const Cours&);
	int checkTiming(const Cours&, const ListeTriee<SmartPointer<Cours> >&);


	void planCourse();
	void removeOneCourse();
	void removeAllCourses();
	void removeCourse(Cours*);
	void showAllCourses();
	void showAllCoursesOfDay();
	void exportElements();

	void exportProfesseur(ofstream& ofs, const Cours& c, char* day);
	void exportGroupe(ofstream& ofs, const Cours& c, char* day);
	void exportLocal(ofstream& ofs, const Cours& c, char* day);

	void setHoraire(const char* h);
};
#endif