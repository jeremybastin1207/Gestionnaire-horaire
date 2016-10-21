#include "Horaire.h"

using namespace std;

#define UNIX

#ifdef UNIX
void ClearScreen()
{
	cout << "\033[2J\033[;H";
}

void Pause()
{
	fflush(stdin);
	cout << endl << endl << "Appuyer sur Enter pour continuer...";
	getchar();
} 

#else
void ClearScreen()
{
	system("cls");
}

void Pause()
{
	system("pause");
}
#endif
ostream& tab(ostream &e)
{
	e << "\t";
	return e;	
}

Horaire::Horaire()
{
	horaire = NULL;
}

Horaire::~Horaire()
{
	if(horaire) delete horaire;
}

int Horaire::selectMenu()
{
	int choice;

	do
	{
		cout << "**************************************************************" << endl;
		cout << "*************** Gestion d'un horaire de Cours ****************" << endl;
		cout << "**************************************************************" << endl;

		cout << "\t0. Quitter" << endl;
		
		cout << "Fichier ***** En cours : ";

		if(horaire)
			cout << horaire;
		else
			cout << "Aucun fichier ouvert";

		cout << endl;

		cout << "\t1. Nouvel Horaire" << endl;
		cout << "\t2. Ouvrir un horaire" << endl;
		cout << "\t3. Enregistrer l'horaire" << endl;
		cout << "\t4. Fermer l'horaire" << endl;

		cout << "Gestion des Plannifiables ************************************" << endl;
		cout << "\t5. Ajouter un Professeur/Groupe/Local" << endl;
		cout << "\t6. Importer des Professeurs/Groupes/Locaux au format csv" << endl;
		cout << "\t7. Afficher la liste des Professeurs/Groupes/Locaux" << endl;
		cout << "\t8. Supprimer un Professeur/Groupe/Local" << endl;

		cout << "Gestion de l'horaire *****************************************" << endl;
		cout << "\t9. Plannifier un Cours" << endl;
		cout << "\t10. Deplannifier un Cours" << endl;
		cout << "\t11. Deplannifier tous les Cours d'un Professeur/Groupe/Local" << endl;
		cout << "\t12. Afficher tous les Cours d'un Professeur/Groupe/Local" << endl;
		cout << "\t13. Afficher tous les Cours d'un jour particulier" << endl;

		cout << "Publier l'horaire ********************************************" << endl;
		cout << "\t14. Exporter l'horaire d'un Professeur/Groupe/Local au format txt" << endl << endl;

		cout << "Votre choix : ";
		cin >> choice;

		ClearScreen();
	}while(choice < 0 || choice > 14);

	return choice;
}

void Horaire::executeAction(int choice)
{
	switch(choice)
	{
		case 0:
			cout << "Fin du programme. A bientot" << endl << endl;
			Pause();
			break;
		case 1:
			createHoraire();
			break;
		case 2:
			openHoraire();
			break;
		case 3:
			saveHoraire();
			break;
		case 4:
			closeHoraire();
			break;
		case 5:
			addElement();
			break;
		case 6:
			importElement();
			break;
		case 7:
			showElements();
			break;
		case 8:
			deleteElement();
			break;
		case 9:
			planCourse();
			break;
		case 10:
			removeOneCourse();
			break;
		case 11:
			removeAllCourses();
			break;
		case 12:
			showAllCourses();
			break;
		case 13:
			showAllCoursesOfDay();
			break;
		case 14:
			exportElements();
			break;		
	}
}

void Horaire::createHoraire()
{
	char fileName[100];
	ofstream ofs;
	int length = 0;

	if(horaire != NULL)
	{
		cout << "/!\\ Veuillez d'abord fermer l'horaire actuel" << endl << endl;
		return;
	}

	cout << "Ajout d'un horaire ************************************" << endl;

	cout << "Denomination de l'horaire : ";
	cin >> fileName;

	strcat(fileName, ".hor");

	ofs.open(fileName);

	ClearScreen();

	if(ofs.is_open())
	{
		/* Lorsque l'on ouvrira le fichier par après, il faut indiquer qu'il y a 0 professeur, 0 groupe et 0 locaux */
		ofs.write((char*) &length, sizeof(int));
		ofs.write((char*) &length, sizeof(int));
		ofs.write((char*) &length, sizeof(int));
		setHoraire(fileName);

		cout << ">>> Horaire ajoute" << endl;
		ofs.close();
	}

	else
		cout << ">>> Impossible de créer l'horaire" << endl;

	Pause();
	ClearScreen();	
}

void Horaire::openHoraire()
{
	char fileName[100], choice;
	ifstream ifs;
	int length, i, j;
	Iterateur<Professeur> itp(professeurs);
	Iterateur<Local> itl(locaux);
	Iterateur<Groupe> itg(groupes);
	Professeur *p1 = NULL;
	Groupe *g1 = NULL;
	Local *l1 = NULL;
	Cours *c1 = NULL;

	ClearScreen();

	if(horaire != NULL)
	{
		cout << "/!\\ Veuillez d'abord fermer l'horaire actuel" << endl << endl;
		return;
	}

	do
	{
		cout << "Ouverture d'un horaire ************************************" << endl;
		cout << "Denomination de l'horaire : ";
		cin >> fileName;

		strcat(fileName, ".hor");

		ifs.open(fileName);

		if(!ifs.is_open())
		{
			cout << "Horaire non existant" << endl;
			cout << "Nouvelle tentative (O/N)?";
			cin >> choice;
			ClearScreen();
		}
		else
		{
			ClearScreen();
			cout << ">>> Chargment...";

			setHoraire(fileName);
	
			ifs.read((char*) &length, sizeof(int));

			for (i = 0 ; i < length ; i++)
			{
				p1 = new Professeur;
				p1->Load(ifs);
				professeurs.insere(*p1);
			}
			
			ifs.read((char*) &length, sizeof(int));
			
			for (i = 0 ; i < length ; i++)
			{
				g1 = new Groupe;
				g1->Load(ifs);
				groupes.insere(*g1);
			}
			
			ifs.read((char*) &length, sizeof(int));
			
			for (i = 0 ; i < length ; i++)
			{
				l1 = new Local;
				l1->Load(ifs);
				locaux.insere(*l1);
			}

			ifs.read((char*) &length, sizeof(int));	

			for(i = 0 ; i < length ; i++)
			{
				c1 = new Cours;

				c1->Load(ifs);

				c1 = courses.insere(*c1);

				for (itp.reset(), j = 0 ; !itp.end(); itp++, j++)
				{
					Professeur& p1 = (Professeur&) itp.get(j);

					if(strcmp(p1.getIdentifiant(), c1->getProfesseur()) == 0)
					{
						p1.AjouterCours(c1);
						break;
					}
				}

				for(itg.reset(), j = 0 ; !itg.end() ; itg++, j++)
				{
					Groupe& g1 = (Groupe&) itg.get(j);

					ListeTriee<char*> gg(c1->getGroupes());
					Iterateur<char*> itgg(gg);

					for(itgg.reset() ; !itgg.end() ; itgg++)
					{
						if(strcmp(g1.getIdentifiant(), (char*)itgg) == 0)
						{
							g1.AjouterCours(c1);
							break;
						}
					}
				}

				for(itl.reset(), j = 0 ; !itl.end() ; itl++, j++)
				{
					Local& l1 = (Local&) itl.get(j);

					if(strcmp(l1.getIdentifiant(), c1->getLieu()) == 0)
					{
						l1.AjouterCours(c1);
						break;
					}
				}

				
			}

			ClearScreen();

			cout << ">>> Horaire ouvert" << endl;

   			Pause();
			ClearScreen();	
		}

	}while(tolower(choice) == 'o' && !ifs.is_open());

	if(ifs.is_open())
		ifs.close();
}

void Horaire::saveHoraire()
{
	ofstream ofs(horaire, ios::out);
	int length;

	Iterateur<Professeur> itp(professeurs);
	Iterateur<Groupe> itg(groupes);
	Iterateur<Local> itl(locaux);
	Iterateur<Cours> itc(courses);

	ClearScreen();

	length = professeurs.getNombreElements();
	ofs.write((char*) &length, sizeof(int));

	for (itp.reset(); !itp.end(); itp++)
	{
		Professeur* p1 = (Professeur*) &itp;
		p1->Save(ofs);
	}

	length = groupes.getNombreElements();
	ofs.write((char*) &length, sizeof(int));

	for (itg.reset(); !itg.end(); itg++)
	{
		Groupe* g1 = (Groupe*) &itg;
		g1->Save(ofs);
	}

	length = locaux.getNombreElements();
	ofs.write((char*) &length, sizeof(int));

	for (itl.reset(); !itl.end(); itl++)
	{
		Local* l1 = (Local*) &itl;
		l1->Save(ofs);
	}

	length = courses.getNombreElements();
	ofs.write((char*) &length, sizeof(int));

	for(itc.reset(); !itc.end(); itc++)
	{
		Cours* c1 = (Cours*) &itc;
		c1->Save(ofs);
	}

	cout << ">>> Sauvegarde effectuee" << endl;

	Pause();
	ClearScreen();	
}

void Horaire::closeHoraire()
{
	if(horaire)
	{
		delete horaire;
		horaire = NULL;
		professeurs.truncate();
		groupes.truncate();
		locaux.truncate();
		courses.truncate();
		cout << ">>> Fichier ferme" << endl;
	}
	else
		cout << "/!\\ Aucun fichier n'est actuellement ouvert" << endl;

	Pause();
	ClearScreen();	
}

void Horaire::addElement()
{
	int choice;
	Professeur *p1 = NULL;
	Groupe *g1 = NULL;
	Local *l1 = NULL;

	if(horaire == NULL)
	{
		cout << ">>> Veuillez d'abord ouvrir ou creer un horaire" << endl;
		Pause();
		ClearScreen();
		return;
	}
	else
	{
		do
		{
			ClearScreen();

			cout << "Ajouter un Professeur/Groupe/Local ************************************" << endl;

			cout << "\t1. Nouveau professeur" << endl;
			cout << "\t2. Nouveau groupe" << endl;
			cout << "\t3. Nouveau local" << endl;
			cout << "\t4. revenir au menu principal" << endl << endl;

			cout << "Votre choix : ";
			cin >> choice;
		}while(choice < 0 || choice > 4);

		switch(choice)
		{
			case 1:
				p1 = new Professeur;
				cin >> (*p1);
				ClearScreen();
				professeurs.insere(*p1);
				cout << ">>> Professeur ajoute" << endl;
			break;
			case 2:
				g1 = new Groupe;
				cin >> (*g1);
				ClearScreen();
				groupes.insere(*g1);
				cout << ">>> Groupe ajoute" << endl;
			break;
			case 3:
			    l1 = new Local;
				cin >> (*l1);
				ClearScreen();
				locaux.insere(*l1);
				cout << ">>> Local ajoute" << endl;
			break;
			default:
				ClearScreen();
			break;
		}
	}
}

void Horaire::importElement()
{
	ifstream ifs;
	char buffer[100];
	int number;

	if(horaire == NULL)
	{
		cout << "/!\\ Veuillez d'abord ouvrir un horaire" << endl;
		Pause();
		ClearScreen();	
	}
	else
	{
		ifs.open("Data/Professeurs.csv", ifstream::in);

		if(ifs.is_open())
		{
			ifs.getline(buffer, 100, ';');

			do
			{	
				Professeur p1;
				
				p1.setNom(buffer);

				ifs.getline(buffer, 100);
				buffer[strlen(buffer) - 1] = 0;
				p1.setPrenom(buffer);


				if(!professeurs.existe(p1))
					professeurs.insere(p1);

				ifs.getline(buffer, 100, ';');

			}while(!ifs.eof());

			cout << ">>> Professeurs importes" << endl;

			ifs.close();
		}
		else
			cout << ">>> Erreur lors de l'ouverture du fichier des professeurs" << endl;



		
		ifs.open("Data/Groupes.csv", ifstream::in);

		if(ifs.is_open())
		{
			ifs.getline(buffer, 100, ';');

			do
			{
				Groupe g1;

				g1.setCategorie(buffer);

				ifs.getline(buffer, 100, ';');
				number = atoi(buffer);
				g1.setNiveau(number);

				ifs.getline(buffer, 100);
				number = atoi(buffer);
				g1.setNumero(number);
				
				if(!groupes.existe(g1))
					groupes.insere(g1);

				ifs.getline(buffer, 100, ';');

			}while(!ifs.eof());

			cout << ">>> Groupes importes" << endl;

			ifs.close();
		}
		else
			cout << ">>> Erreur lors de l'ouverture du fichier des professeurs" << endl;

		ifs.open("Data/Locaux.csv", ifstream::in);

		if(ifs.is_open())
		{
			ifs.getline(buffer, 100);

			do
			{
				Local l1;

				buffer[strlen(buffer) - 1] = 0;
				l1.setNom(buffer);

				if(!locaux.existe(l1))
					locaux.insere(l1);

				ifs.getline(buffer, 100);

			}while(!ifs.eof());

			cout << ">>> Locaux importes" << endl;

			ifs.close();
		}
		else
			cout << ">>> Erreur lors de l'ouverture du fichier des locaux" << endl;

	}

	Pause();
	ClearScreen();	
}

void Horaire::showElements()
{
	int choice, i;
	Professeur p1;
	Groupe g1;
	Local l1;

	Iterateur<Professeur> itp(professeurs);
	Iterateur<Groupe> itg(groupes);
	Iterateur<Local> itl(locaux);

	if(horaire == NULL)
	{
		cout << ">>> Veuillez d'abord ouvrir ou creer un horaire" << endl;
		Pause();
		ClearScreen();	
		return;
	}

	if(professeurs.estVide() && groupes.estVide() && locaux.estVide())
	{
		cout << ">>> Les listes des professeurs, groupes et locaux sont vides" << endl;
		Pause();
		ClearScreen();	
		return;
	}
	else
	{
		do
		{
			ClearScreen();

			cout << "Afficher la liste des Professeurs/Groupes/Locaux ************************************" << endl;

			cout << "\t1. Afficher les professeurs" << endl;
			cout << "\t2. Afficher les groupes" << endl;
			cout << "\t3. Afficher les locaux" << endl;
			cout << "\t4. revenir au menu principal" << endl;

			cout << "Votre choix : ";
			cin >> choice;
		}while(choice < 0 || choice > 4);

		ClearScreen();

		switch(choice)
		{
			case 1:
				if(professeurs.estVide())
				{
					cout << ">>> La liste des professeurs est vide" << endl;
				}
				else
				{
					cout << "Liste des professeurs ************************************" << endl;
					for (itp.reset(), i = 1; !itp.end(); itp++, i++)
					{
						p1 = (Professeur) itp;

						cout << '\t' << i << ". " << p1.getNom() << ' ' << p1.getPrenom() << endl;
					}
				}
			break;
			case 2:
				if(groupes.estVide())
				{
					cout << ">>> La liste des groupes est deja vide" << endl;
				}
				else
				{
					cout << "Liste des groupes ************************************" << endl;
					for (itg.reset(), i = 1; !itg.end(); itg++, i++)
					{
						g1 = (Groupe) itg;
						cout << "\t" << i << ". " << g1.getNumero() << endl;
					}
				}		
			break;
			case 3:
				if(locaux.estVide())
				{
					cout << ">>> La liste des locaux est deja vide" << endl;
				}
				else
				{
					cout << "Liste des locaux ************************************" << endl;
					for (itl.reset(), i = 1; !itl.end(); itl++, i++)
					{
						l1 = (Local) itl;
						cout << "\t" <<i << ". " << l1.getNom() << " (" << l1.getNbPlaces() << ")" << endl;
					}
				}
				
			break;
			default:

			break;
		}

		Pause();
		ClearScreen();
	}
}

void Horaire::deleteElement()
{
	int choice, elem, i, length;
	Professeur p1;
	Groupe g1;
	Local l1;

	Iterateur<Professeur> itp(professeurs);
	Iterateur<Groupe> itg(groupes);
	Iterateur<Local> itl(locaux);

	if(horaire == NULL)
	{
		cout << ">>> Veuillez d'abord ouvrir ou creer un horaire" << endl;
		Pause();
		ClearScreen();	
		return;
	}

	if(professeurs.estVide() && groupes.estVide() && locaux.estVide())
	{
		cout << ">>> Les listes des professeurs, groupes et locaux sont deja vides" << endl;
		Pause();
		ClearScreen();	
		return;
	}
	else
	{
		do
		{
			ClearScreen();

			cout << "Supprimer un Professeur/Groupe/Local ************************************" << endl;

			cout << "\t1. Supprimer un professeur" << endl;
			cout << "\t2. Supprimer un groupe" << endl;
			cout << "\t3. Supprimer un local" << endl;
			cout << "\t4. Revenir au menu principal" << endl;

			cout << "Votre choix : ";
			cin >> choice;
			--choice;
		}while(choice < 0 || choice > 3);

		ClearScreen();

		switch(choice)
		{
			case 0:
				if(professeurs.estVide())
				{
					cout << ">>> La liste des professeurs est deja vide" << endl;
					Pause();
					ClearScreen();	
					return;
				}
				else
				{
					cout << "Liste des professeurs ************************************" << endl;

					for (itp.reset(), i = 1; !itp.end(); itp++, i++)
					{
						p1 = (Professeur) itp;
						cout << "\t" << i << ". " << p1.getNom() << " " << p1.getPrenom() << endl;
					}
				}

			break;
			case 1:
				if(groupes.estVide())
				{
					cout << ">>> La liste des groupes est deja vide" << endl;
					Pause();
					ClearScreen();	
					return;
				}
				else
				{
					cout << "Liste des groupes ************************************" << endl;

					for (itg.reset(), i = 1; !itg.end(); itg++, i++)
					{
						g1 = (Groupe) itg;
						cout << "\t" << i << ". " << g1.getIdentifiant() << endl;
					}
				}
			break;
			case 2:
				if(locaux.estVide())
				{
					cout << ">>> La liste des locaux est deja vide" << endl;
					Pause();
					ClearScreen();	
					return;
				}
				else
				{
					cout << "Liste des locaux ************************************" << endl;

					for (itl.reset(), i = 1; !itl.end(); itl++, i++)
					{
						l1 = (Local) itl;
						cout << "\t" << i << ". " << l1.getIdentifiant() << endl;
					}
				}
			break;
			default:
				return;
			break;
		}

		cout << endl;

		do
		{
			cout << "Indiquez le numero : ";
			cin >> elem;
		}while(elem < 1 || elem > i);

		--elem;

		ListeTriee<SmartPointer<Cours> > courses2;

		if(choice == 0)
		{
			for (itp.reset(), i = 0; !itp.end() && i != elem; itp++, i++){}

			Professeur* p2 = (Professeur*) &itp; 
			courses2 = p2->getCours();
			Iterateur<SmartPointer<Cours> > itc2(courses2);

			for(itc2.reset() ; !itc2.end() ; itc2++)
			{
				SmartPointer<Cours> sp1 = (SmartPointer<Cours>) itc2;
				Cours* c2 = sp1.getValeur();
				removeCourse(c2);
			}

			itp.remove();	
		}
		else if(choice == 1)
		{
			for (itg.reset(), i = 0; !itg.end() && i != elem; itg++, i++){}
			
			Groupe* g2 = (Groupe*) &itg; 
			courses2 = g2->getCours();
			
			Iterateur<SmartPointer<Cours> > itc2(courses2);
			
			for(itc2.reset() ; !itc2.end() ; itc2++)
			{
				SmartPointer<Cours> sp1 = (SmartPointer<Cours>) itc2;
				Cours* c2 = sp1.getValeur();
				removeCourse(c2);
			}

			itg.remove();
		}
		else
		{
			for (itl.reset(), i = 0; !itl.end() && i != elem; itl++, i++){}
				
			Local* l2 = (Local*) &itl; 
			courses2 = l2->getCours();
			
			Iterateur<SmartPointer<Cours> > itc2(courses2);
			
			for(itc2.reset() ; !itc2.end() ; itc2++)
			{
				SmartPointer<Cours> sp1 = (SmartPointer<Cours>) itc2;
				Cours* c2 = sp1.getValeur();
				removeCourse(c2);
			}

			itl.remove();
		}


		ClearScreen();

		cout << ">>> Element supprime" << endl;
		Pause();
		ClearScreen();	
	}
}

void Horaire::showCours(const Cours& c1)
{
	Professeur p1;
	Local l1;
	Groupe g1;
	Iterateur<Professeur> itp(professeurs);
	Iterateur<Local> itl(locaux);
	Iterateur<Groupe> itg(groupes);

	if(horaire == NULL)
	{
		cout << ">>> Veuillez d'abord ouvrir ou creer un horaire" << endl;
		Pause();
		ClearScreen();	
		return;
	}

	for (itp.reset(); !itp.end(); itp++)
	{
		p1 = (Professeur) itp;

		if(strcmp(p1.getIdentifiant(), c1.getProfesseur()) == 0)
			break;
	}

	for(itl.reset() ; !itl.end() ; itl++)
	{
		l1 = (Local) itl;

		if(strcmp(l1.getIdentifiant(), c1.getLieu()) == 0)
			break;
	}

	cout << "Intitule : " << c1.getIntitule() << endl;
	cout << "Jour : " << c1.getTiming().getJour() << endl;
	cout << "Heure : " << c1.getTiming().getHeure() << endl;
	cout << "Duree : " << c1.getTiming().getDuree() << endl;
	cout << "Professeur : " << p1.getNom() << " " << p1.getPrenom();
	cout << endl << "Local : " << l1.getNom();
	

	ListeTriee<char*> lt1(c1.getGroupes());
	Iterateur<char*> itcc(lt1);
	itcc.reset();

	cout << endl << "Groupes : ";

	if(!itcc.end())
	{
		cout << (char*) itcc;
		itcc++;

		while(!itcc.end())
		{
			cout << " - " << (char*) itcc;
			itcc++;
		}
	}

	cout << endl << endl;
}

// Doit changer les opérateur > en >=

int Horaire::checkTiming(const Cours& c, const ListeTriee<SmartPointer<Cours> >& courses)
{
	ListeTriee<SmartPointer<Cours> > aa(courses);
	int i, j, valid = 1;
	Timing t1, t2;
	Temps h1, h2;

	Iterateur<SmartPointer<Cours> > itsc(aa);
	t1 = c.getTiming();

	for (itsc.reset(), j = 0; !itsc.end(); itsc++, j++)
	{
		SmartPointer<Cours> sc = (SmartPointer<Cours>) itsc.get(j);
		Cours* c2 = sc.getValeur();

		t2 = c2->getTiming();

		if(strcmp(t1.getJour(), t2.getJour()) == 0)
		{
			Temps h2 = t2.getHeure();
			h2 = h2 + t2.getDuree();

			Temps h1 = t1.getHeure();
			h1 = h1 + t1.getDuree();

			if((t1.getHeure() >= t2.getHeure() && t1.getHeure() <= h2) || (h1 >= t2.getHeure() && h1 <= h2))
			{
				valid = 0;
				break;
			}
		}
	}



	return valid;
}

void Horaire::planCourse()
{
	Cours *c1 = NULL;
	int choice, i, j, valid, valid2, selected;
	char choice2, buffer[100];
	Temps h;
	Timing t1, t2;
	Professeur *p2 = NULL;
	Groupe *g2 = NULL;
	Local *l2 = NULL;
	Iterateur<Professeur> itp(professeurs);
	Iterateur<Groupe> itg(groupes);
	Iterateur<Local> itl(locaux);

	ListeTriee<SmartPointer<Groupe> > groupesSelected;
	Iterateur<SmartPointer<Groupe> > itGroupesSelected(groupesSelected);

	if(horaire == NULL)
	{
		cout << ">>> Veuillez d'abord ouvrir ou creer un horaire" << endl;
		Pause();
		ClearScreen();	
		return;
	}

	if(professeurs.estVide() || groupes.estVide() || locaux.estVide())
	{
		cout << ">>> Le logiciel doit au moins avoir un professeur, un local et un groupe pour pouvoir ajouter un cours" << endl;
		Pause();
		ClearScreen();	
		return;
	}

	c1 = new Cours;

	do
	{
		ClearScreen();

		cout << "Informations sur le cours ************************************" << endl;

		cout << "Intitule : ";
		cin >> buffer;

	}while(strlen(buffer) == 0);

	c1->setIntitule(buffer);

	t1 = c1->getTiming();


	ClearScreen();
	cout << "Informations sur le cours ************************************" << endl;

	cout << "Jour du cours : " << endl;

	t1.choisirJour();

	do
	{
		ClearScreen();
		cout << "Informations sur le cours ************************************" << endl;

		cout << "Heure du debut du cours : ";
		cin >> h;

	}while(strlen(buffer) == 0);

	t1.setHeure(h);

	do
	{
		ClearScreen();
		cout << "Informations sur le cours ************************************" << endl;

		cout << "Duree du cours : ";
		cin >> h;

	}while(strlen(buffer) == 0);

	t1.setDuree(h);

	c1->setTiming(t1);

	/* Ajout du professeur */
	valid = 1;

	do
	{
		ClearScreen();
		cout << "Liste des professeurs ************************************" << endl;
	
		for (itp.reset(), i = 0; !itp.end(); itp++, i++)
		{
			Professeur p1 = (Professeur) itp;
			cout << "\t" << i+1 << ". " << p1;

			valid2 = checkTiming(*c1, p1.getCours());

			if(!valid2)
				cout << " (occupe)";

			cout << endl;
		}

		cout << endl << "\t" << i+1 << ". Quitter et revenir au menu" << endl << endl;

		if(!valid)
			cout << "\t>>> Ce professeur est deja occupe !" << endl << endl;

		do
		{
			cout << "Veuillez choisir un professeur : ";
			cin >> choice;
			--choice;
		}while(choice < 0 || choice > i);


		if(i == choice)
		{
			ClearScreen();
			return;
		}

		p2 = (Professeur*) &itp.get(choice);

		valid = 0;

		for (itp.reset(), i = 0; !itp.end(); itp++, i++)
		{
			Professeur p1 = (Professeur) itp;

			if(strcmp(p2->getIdentifiant(), p1.getIdentifiant()) == 0)
			{
				valid = checkTiming(*c1, p1.getCours());
				break;
			}
		}

	}while(!valid);

	c1->setProfesseur(p2->getIdentifiant());	

	/* Ajout du local */
	valid = 1;
	
	do
	{
		ClearScreen();
		cout << "Liste des locaux ************************************" << endl;
	
		for (itl.reset(), i = 0; !itl.end(); itl++, i++)
		{
			Local l1 = (Local) itl;
			cout << "\t" << i+1 << ". " << l1.getIdentifiant();

			valid2 = checkTiming(*c1, l1.getCours());

			if(!valid2)
				cout << " (occupe)";

			cout << endl;
		}

		cout << endl << "\t" << i+1 << ". Quitter et revenir au menu" << endl << endl;

		if(!valid)
			cout << "\t>>> Ce local est deja occupe !" << endl << endl;

		do
		{
			cout << "Veuillez choisir un local : ";
			cin >> choice;
			--choice;
		}while(choice < 0 || choice > i);


		if(i == choice)
		{
			ClearScreen();
			return;
		}

		l2 = (Local*) &itl.get(choice);

		valid = 0;

		for (itl.reset(), i = 0; !itl.end(); itl++, i++)
		{
			Local l1 = (Local) itl;

			if(strcmp(l2->getIdentifiant(), l1.getIdentifiant()) == 0)
			{
				valid = checkTiming(*c1, l1.getCours());
				break;
			}
		}

	}while(!valid);

	c1->setLieu(l2->getIdentifiant());	

	/*Ajout des groupes */
	do
	{
		valid = 1;
		
		do
		{
			ClearScreen();
			cout << "Liste des groupes ************************************" << endl;
		
			for (itg.reset(), i = 0; !itg.end(); itg++, i++)
			{
				Groupe g1 = (Groupe) itg;
				cout << "\t" << i+1 << ". " << g1.getIdentifiant();

				valid2 = checkTiming(*c1, g1.getCours());

				ListeTriee<char*> groupes2(c1->getGroupes());
				Iterateur<char*> itg2(groupes2);

				selected = 0;

				for(itg2.reset() ; !itg2.end() ; itg2++)
				{
					char* temp = (char*) itg2;

					if(strcmp(temp, g1.getIdentifiant()) == 0)
					{
						cout << " (selectionne)";
						selected = 1;
						break;
					}
				}

				if(!valid2 && !selected)
					cout << " (occupe)";

				cout << endl;
			}

			cout << endl << "\t" << i+1 << ". Quitter et revenir au menu" << endl << endl;

			if(!valid)
				cout << "\t>>> Ce groupe est deja occupe ou selectionne !" << endl << endl;

			do
			{
				cout << "Veuillez choisir un groupe : ";
				cin >> choice;
				--choice;
			}while(choice < 0 || choice > i);


			if(i == choice)
			{
				ClearScreen();
				return;
			}

			g2 = (Groupe*) &itg.get(choice);

			valid = 0;

			/* Vérification du timing */
			for (itg.reset(), i = 0; !itg.end(); itg++, i++)
			{
				Groupe g1 = (Groupe) itg;

				if(strcmp(g2->getIdentifiant(), g1.getIdentifiant()) == 0)
				{
					valid = checkTiming(*c1, g1.getCours());
					break;
				}
			}

			ListeTriee<char*> groupes2(c1->getGroupes());
			Iterateur<char*> itg2(groupes2);

			/* Vérification de la présence éventuelle du groupe qui pourrait deja etre sélectionné*/
			for(itg2.reset() ; !itg2.end() ; itg2++)
			{
				char* temp = (char*) itg2;

				if(strcmp(temp, g2->getIdentifiant()) == 0)
				{
					valid = 0;
					break;
				}
			}

		}while(!valid);

		SmartPointer<Groupe> sp(g2);
		groupesSelected.insere(sp);

		if(valid)
			c1->insereGroupe(g2->getIdentifiant());


		ClearScreen();

		cout << "Voulez-vous ajouter un autre groupe (1/0) ? ";
		cin >> choice;
	}while(choice);

	ClearScreen();

	Cours* c2 = NULL;
	c2 = courses.insere(*c1);

	p2->AjouterCours(c2);
	l2->AjouterCours(c2);

	for(itGroupesSelected.reset() ; !itGroupesSelected.end() ; itGroupesSelected++)
	{
		SmartPointer<Groupe> aa = itGroupesSelected;
		g2 = (Groupe*) aa.getValeur();
		g2->AjouterCours(c2);
	}
	
	cout << ">>> Cours ajoute" << endl << endl;
	Pause();
	ClearScreen();
}

void Horaire::removeOneCourse()
{
	int choice, i;
	Iterateur<Cours> itc(courses);

	if(horaire == NULL)
	{
		cout << ">>> Veuillez d'abord ouvrir ou creer un horaire" << endl;
		Pause();
		ClearScreen();	
		return;
	}

	if(professeurs.estVide() || groupes.estVide() || locaux.estVide())
	{
		cout << ">>> Il n'y actuellement aucun cours envisagable" << endl << endl;
		Pause();
		ClearScreen();	
		return;
	}

	for(itc.reset(), i = 0 ; !itc.end() ; itc++, i++)
	{	
		Cours* c = (Cours*) &itc;
		cout << i+1 << ". " << endl;
		showCours(*c);
	}

	cout << i+1 << ". Revenir au menu" << endl << endl;

	do
	{
		cout << "Votre choix : ";
		cin >> choice;
		--choice;
	}while(choice < 0 || choice > i);

	if(choice == i)
	{
		ClearScreen();
		return;
	}

	Cours* c1 = (Cours*) &itc.get(choice);

	removeCourse(c1);

	ClearScreen();

	cout << ">>> Cours supprime" << endl;
	Pause();
	ClearScreen();
}

void Horaire::removeAllCourses()
{
	Iterateur<Professeur> itp(professeurs);
	Iterateur<Local> itl(locaux);
	Iterateur<Groupe> itg(groupes);
	Iterateur<Cours> itc(courses);
	Professeur* p1 = NULL;
	Local* l1 = NULL;
	Groupe* g1 = NULL;
	int choice, i;
	ListeTriee<SmartPointer<Cours> > courses2;

	if(horaire == NULL)
	{
		cout << ">>> Veuillez d'abord ouvrir ou creer un horaire" << endl;
		Pause();
		ClearScreen();	
		return;
	}

	do
	{
		cout << "Deplannifier tous les Cours d'un Professeur/Groupe/Local ************************************" << endl << endl;
		cout << "\t1. Deplannifier tous les cours d'un professeur" << endl;
		cout << "\t2. Deplannifier tous les cours d'un local" << endl;
		cout << "\t2. Deplannifier tous les cours d'un groupe" << endl;
		cout << "\t4. Revenir au menu" << endl << endl;

		cout << "choice : ";
		cin >> choice;
		--choice;
	}while(choice < 0 || choice > 3);

	ClearScreen();

	if(choice == 3)
		return;

	if(choice == 0)
	{
		/* Traitement de la suppression des cours d'un professeur*/
		for(itp.reset(), i = 0 ; !itp.end() ; itp++, i++)
		{
			p1 = (Professeur*) &itp;
			cout << "\t" << i+1 << ". " << p1->getNom() << " " << p1->getPrenom();

			if(!p1->PossedeCours())
				cout << " (aucun cours)";

			cout << endl;
		}

		cout << endl;

		do
		{
			cout << "Votre choix : ";
			cin >> choice;
			--choice;
		}while(choice < 0 || choice > i);

		p1 = (Professeur*) &itp.get(choice);
		courses2 = p1->getCours();
	}
	else if(choice == 1)
	{
		/* Traitement de la suppression des cours d'un local*/
		for(itl.reset(), i = 0 ; !itl.end() ; itl++, i++)
		{
			l1 = (Local*) &itl;
			cout << "\t" << i+1 << ". " << l1->getIdentifiant();

			if(!l1->PossedeCours())
				cout << " (aucun cours)";

			cout << endl;
		}

		cout << endl;

		do
		{
			cout << "Votre choix : ";
			cin >> choice;
			--choice;
		}while(choice < 0 || choice > i);

		l1 = (Local*) &itl.get(choice);
		courses2 = l1->getCours();
	}
	else
	{
		/* Traitement de la suppression des cours d'un groupe*/
		for(itg.reset(), i = 0 ; !itg.end() ; itg++, i++)
		{
			g1 = (Groupe*) &itg;
			cout << "\t" << i+1 << ". " << g1->getIdentifiant();

			if(!g1->PossedeCours())
				cout << " (aucun cours)";

			cout << endl;
		}

		cout << endl;

		do
		{
			cout << "Votre choix : ";
			cin >> choice;
			--choice;
		}while(choice < 0 || choice > i);

		g1 = (Groupe*) &itg.get(choice);
		courses2 = g1->getCours();
	}

	Iterateur<SmartPointer<Cours> > itsp(courses2);


	for(itsp.reset() ; !itsp.end() ; itsp++)
	{	
		SmartPointer<Cours> sp1 = (SmartPointer<Cours>) itsp;	
		Cours* c1 = sp1.getValeur();	
		removeCourse(c1);
	}

	ClearScreen();

	cout << ">>> Cours supprime" << endl;
	Pause();
	ClearScreen();
}

void Horaire::removeCourse(Cours* c1)
{	
	int choice, i;
	Iterateur<Professeur> itp(professeurs);
	Iterateur<Local> itl(locaux);
	Iterateur<Groupe> itg(groupes);
	Iterateur<Cours> itc(courses);
	char pId[100];
	char lId[100];
	ListeTriee<char*> gIds(c1->getGroupes());
	Iterateur<char*> itg2(gIds);

	strcpy(pId, c1->getProfesseur());
	strcpy(lId, c1->getLieu());

	for(itp.reset() ; !itp.end() ; itp++)
	{
		// Ne marche pas avec une reference
		Professeur* p1 = (Professeur*) &itp;

		if(strcmp(pId, p1->getIdentifiant()) == 0)
		{
			ListeTriee<SmartPointer<Cours> > aa(p1->getCours());
			Iterateur<SmartPointer<Cours> > bb(aa);

			for(bb.reset() ; !bb.end() ; bb++)
			{
				SmartPointer<Cours> cc = (SmartPointer<Cours>) bb;
				Cours* dd = cc.getValeur();

				if(dd == c1)
				{
					p1->SupprimerCours(dd);
					break;
				}
			}
		}
	}

	for(itl.reset() ; !itl.end() ; itl++)
	{
		// Ne marche pas avec une reference
		Local* l1 = (Local*) &itl;

		if(strcmp(lId, l1->getIdentifiant()) == 0)
		{
			ListeTriee<SmartPointer<Cours> > aa(l1->getCours());
			Iterateur<SmartPointer<Cours> > bb(aa);
			for(bb.reset() ; !bb.end() ; bb++)
			{
				SmartPointer<Cours> cc = (SmartPointer<Cours>) bb;
				Cours* dd = cc.getValeur();
				if(dd == c1)
				{
					l1->SupprimerCours(dd);
					break;
				}
			}
		}
	}

	char gId[100];

	for(itg.reset() ; !itg.end() ; itg++)
	{
		// Ne marche pas avec une reference
		Groupe* g1 = (Groupe*) &itg;

		for(itg2.reset() ; !itg2.end() ; itg2++)
		{
			strcpy(gId,(char*) itg2);

			if(strcmp(gId, g1->getIdentifiant()) == 0)
			{		
				ListeTriee<SmartPointer<Cours> > aa(g1->getCours());
				Iterateur<SmartPointer<Cours> > bb(aa);

				for(bb.reset() ; !bb.end() ; bb++)
				{
					SmartPointer<Cours> cc = (SmartPointer<Cours>) bb;
					Cours* dd = cc.getValeur();

					if(dd == c1)
					{
						g1->SupprimerCours(dd);
						break;
					}
				}
			}
		}
	}

	for(itc.reset() ; !itc.end() ; itc++)
	{
		Cours* temp = (Cours*) &itc;

		if(temp == c1)
		{		
			itc.remove();
			break;
		}
	}
}

void Horaire::showAllCourses()
{
	Iterateur<Cours> itc2(courses);
	Iterateur<Professeur> itp(professeurs);
	Iterateur<Local> itl(locaux);
	Iterateur<Groupe> itg(groupes);
	Professeur p1, p2;
	Local l1, l2;
	Groupe g1, g2;
	int i, choice1, choice2, valid, max;
	char buffer[100];
	ListeTriee<SmartPointer<Cours> > aa;

	if(horaire == NULL)
	{
		cout << ">>> Veuillez d'abord ouvrir ou creer un horaire" << endl;
		Pause();
		ClearScreen();	
		return;
	}

	do
	{
		cout << "Afficher tous les Cours d'un Professeur/Groupe/Local ************************************" << endl << endl;

		cout << "\t1. Afficher tous les cours d'un professeur" << endl;
		cout << "\t2. Afficher tous les cours d'un groupe" << endl;
		cout << "\t3. Afficher tous les cours d'un local" << endl;
		cout << "\t4. Retourner au menu principal" << endl; 
		cout << endl;

		cout << "Votre choix : ";
		cin >> choice1;
	}while(choice1 < 1 || choice1 > 4);


	if(choice1 == 1)
	{
		do
		{
			ClearScreen();
			cout << "Liste des professeurs ************************************" << endl;
		
			for (itp.reset(), i = 0; !itp.end(); itp++, i++)
			{
				Professeur p = (Professeur) itp;
				cout << "\t" << i+1 << ". " << p.getIdentifiant();

				if(!p.PossedeCours())
					cout << " (aucun cours)";

				cout << endl;
			}

			cout << endl;

			cout << "Veuillez choisir un professeur : ";
			cin >> choice2;
		}while(choice2 < 0 || choice2 > i);

		p2 = (Professeur) itp.get(--choice2);

		aa = p2.getCours();
	}
	else if(choice1 == 2)
	{
		do
		{
			ClearScreen();
			cout << "Liste des groupes ************************************" << endl;
		
			for (itg.reset(), i = 0; !itg.end(); itg++, i++)
			{
				Groupe g = (Groupe) itg;
				cout << "\t" << i+1 << ". " << g.getIdentifiant();

				if(!g.PossedeCours())
					cout << " (aucun cours)";

				cout << endl;
			}

			cout << endl;

			cout << "Veuillez choisir un groupe : ";
			cin >> choice2;
		}while(choice2 < 0 || choice2 > i);

		g2 = (Groupe) itg.get(--choice2);

		aa = g2.getCours();
	}
	else if(choice1 == 3)
	{
		do
		{
			ClearScreen();
			cout << "Liste des locaux ************************************" << endl;
		
			for (itl.reset(), i = 0; !itl.end(); itl++, i++)
			{
				Local l = (Local) itl;
				cout << "\t" << i+1 << ". " << l.getIdentifiant();

				if(!l.PossedeCours())
					cout << " (aucun cours)";

				cout << endl;
			}

			cout << endl;

			cout << "Veuillez choisir un local : ";
			cin >> choice2;
		}while(choice2 < 0 || choice2 > i);

		l2 = (Local) itl.get(--choice2);

		aa = l2.getCours();
	}
	else
		return;


	Iterateur<SmartPointer<Cours> > itsc(aa);

	ClearScreen();

	if(aa.getNombreElements() == 0)
	{
		cout << ">>> Aucun cours existant" << endl;
	}

	for (itsc.reset(), i = 0; !itsc.end(); itsc++, i++)
	{
		SmartPointer<Cours> sc = (SmartPointer<Cours>) itsc.get(i);
		Cours* c1 = sc.getValeur();

		showCours(*c1);
	}

	Pause();
	ClearScreen();
}

void Horaire::showAllCoursesOfDay()
{
	if(horaire == NULL)
	{
		cout << ">>> Veuillez d'abord ouvrir ou creer un horaire" << endl;
		Pause();
		ClearScreen();	
		return;
	}

	cout << "Afficher tous les Cours d'un jour particulier ************************************" << endl;
	Timing t;
	Iterateur<Cours> itc(courses);
	int i;

	t.choisirJour();

	ClearScreen();

	cout << "Liste des cours du " << t.getJour() << " ************************************" << endl;

	for(itc.reset(), i = 1 ; !itc.end() ; itc++)
	{
		Cours* c = (Cours*) &itc;

		if(strcmp(c->getTiming().getJour(), t.getJour()) == 0)
		{
			cout << i << ". " << endl;
			showCours(*c);
			i++;
		}
	}

	Pause();
	ClearScreen();
}

void Horaire::exportElements()
{
	ofstream ofs;
	int choice1, length, choice2, i;
	Iterateur<Professeur> itp(professeurs);
	Iterateur<Local> itl(locaux);
	Iterateur<Groupe> itg(groupes);
	Iterateur<Cours> itc(courses);
	char fileName[100], buffer[100], day[100];
	Professeur p2;
	Local l2;
	Groupe g2;
	ListeTriee<SmartPointer<Cours> > aa;

	if(horaire == NULL)
	{
		cout << ">>> Veuillez d'abord ouvrir ou creer un horaire" << endl;
		Pause();
		ClearScreen();	
		return;
	}
	
	do
	{
		ClearScreen();
		cout << "Exporter l'horaire d'un Professeur/Groupe/Local au format txt ************************************" << endl;

		cout << "\t1. Exporter l'horaire d'un professeur" << endl;
		cout << "\t2. Exporter l'horaire d'un groupe" << endl;
		cout << "\t3. Exporter l'horaire d'un local" << endl;
		cout << "\t4. Revenir au menu" << endl << endl;

		cout << "Votre choix :";
		cin >> choice1;
		--choice1;
	}while(choice1 < 0 || choice1 > 3);


	if(choice1 == 0)
	{
		do
		{
			ClearScreen();
			cout << "Liste des professeurs ************************************" << endl;
		
			for (itp.reset(), i = 0; !itp.end(); itp++, i++)
			{
				Professeur p = (Professeur) itp;
				cout << "\t" << i+1 << ". " << p.getIdentifiant();

				if(!p.PossedeCours())
					cout << " (aucun cours)";

				cout << endl;
			}

			cout << endl;

			cout << "Veuillez choisir un professeur : ";
			cin >> choice2;
		}while(choice2 < 0 || choice2 > i);

		p2 = (Professeur) itp.get(--choice2);

		aa = p2.getCours();
	}
	else if(choice1 == 1)
	{
		do
		{
			ClearScreen();
			cout << "Liste des groupes ************************************" << endl;
		
			for (itg.reset(), i = 0; !itg.end(); itg++, i++)
			{
				Groupe g = (Groupe) itg;
				cout << "\t" << i+1 << ". " << g.getIdentifiant();

				if(!g.PossedeCours())
					cout << " (aucun cours)";

				cout << endl;
			}

			cout << endl;

			cout << "Veuillez choisir un groupe : ";
			cin >> choice2;
		}while(choice2 < 0 || choice2 > i);

		g2 = (Groupe) itg.get(--choice2);

		aa = g2.getCours();
	}
	else if(choice1 == 2)
	{
		do
		{
			ClearScreen();
			cout << "Liste des locaux ************************************" << endl;
		
			for (itl.reset(), i = 0; !itl.end(); itl++, i++)
			{
				Local l = (Local) itl;
				cout << "\t" << i+1 << ". " << l.getIdentifiant();

				if(!l.PossedeCours())
					cout << " (aucun cours)";

				cout << endl;
			}

			cout << endl;

			cout << "Veuillez choisir un local : ";
			cin >> choice2;
		}while(choice2 < 0 || choice2 > i);

		l2 = (Local) itl.get(--choice2);

		aa = l2.getCours();
	}
	else
		return;

	switch(choice1)
	{
		case 0:
			strcpy(fileName, (char*) p2.getIdentifiant());
		break;
		case 1:
			strcpy(fileName, (char*) g2.getIdentifiant());
		break;
		case 2:
			strcpy(fileName, (char*) l2.getIdentifiant());
		break;
	}

	strcat(fileName, ".");
	strcat(fileName, horaire);
	strcat(fileName, ".txt");

	ofs.open(fileName);

	ClearScreen();

	if(!ofs.is_open())
	{
		cout << ">>> Impossible de créer le fichier" << endl << endl;
	}
	else
	{
		Iterateur<SmartPointer<Cours> > bb(aa);

		if(choice1 == 0)
		{
			Professeur p1 = (Professeur) itp.get(choice2);
			sprintf(buffer, "Horaire de %s %s (%s)\n", p1.getPrenom(), p2.getNom(), horaire);
		}
		else if(choice1 == 1)
		{
			Groupe g1 = (Groupe) itg.get(choice2);
			sprintf(buffer, "Horaire de %s (%s)\n", g1.getIdentifiant(), horaire);
		}
		else
		{
			Local l1 = (Local) itl.get(choice2);
			sprintf(buffer, "Horaire du local %s (%s)\n", l1.getNom(), horaire);
		}

		length = strlen(buffer);
		ofs.write((char*) buffer, length * sizeof(char));

		for(bb.reset() ; !bb.end() ; bb++)
		{
			SmartPointer<Cours> cc = (SmartPointer<Cours>) bb;
			Cours* c = cc.getValeur();

			switch(choice1)
			{
				case 0:
					exportProfesseur(ofs, *(c), day);
				break;
				case 1:
					exportGroupe(ofs, *(c), day);
				break;
				case 2:
					exportLocal(ofs, *(c), day);
				break;
			}
		}

		ofs.close();
	}

	Pause();
}

void Horaire::exportProfesseur(ofstream& ofs, const Cours& c, char* day)
{
	char buffer[100];
	Iterateur<Professeur> itp(professeurs);
	Iterateur<Local> itl(locaux);
	Iterateur<Groupe> itg(groupes);
	Iterateur<Cours> itc(courses);
	int length;

	if(horaire == NULL)
	{
		cout << ">>> Veuillez d'abord ouvrir ou creer un horaire" << endl;
		Pause();
		ClearScreen();	
		return;
	}

	if(day == NULL || strcmp(day, c.getTiming().getJour()) != 0)
	{
		strcpy(day, c.getTiming().getJour());

		strcpy(buffer, day);
		strcat(buffer, " : \n");

		length = strlen(buffer);
		ofs.write((char*) buffer, length * sizeof(char));
	}


	Timing t = c.getTiming();
	Temps h = t.getHeure();
	Temps h2 = t.getDuree();
	Local l1;

	sprintf(buffer, "\t%dh%02d (%dh%02d ", h.getHeure(), h.getMinute(), h2.getHeure(), h2.getMinute());

	for(itl.reset() ; !itl.end() ; itl++)
	{
		l1 = (Local) itl;

		if(strcmp(l1.getIdentifiant(), c.getLieu()) == 0)
		{
			strcat(buffer, l1.getNom());
			break;
		}
	}

	strcat(buffer, ") ");
	strcat(buffer, c.getIntitule());
	strcat(buffer, " : ");


	length = strlen(buffer);
	ofs.write((char*) buffer, length * sizeof(char));

	ListeTriee<char*> zz(c.getGroupes());

	Iterateur<char*> itg2(zz);

	for(itg2.reset() ; !itg2.end() ; itg2++)
	{
		strcpy(buffer, (char*) itg2);
		strcat(buffer, " ");

		length = strlen(buffer);
		ofs.write(buffer, sizeof(char) * length);
	}


	ofs.write("\n", sizeof(char));
}

void Horaire::exportGroupe(ofstream& ofs, const Cours& c, char* day)
{
	char buffer[100];
	Iterateur<Professeur> itp(professeurs);
	Iterateur<Local> itl(locaux);
	Iterateur<Groupe> itg(groupes);
	Iterateur<Cours> itc(courses);
	Professeur p1;
	int length;

	if(day == NULL || strcmp(day, c.getTiming().getJour()) != 0)
	{
		strcpy(day, c.getTiming().getJour());

		strcpy(buffer, day);
		strcat(buffer, " : \n");

		length = strlen(buffer);
		ofs.write((char*) buffer, length * sizeof(char));
	}

	Timing t = c.getTiming();
	Temps h = t.getHeure();
	Temps h2 = t.getDuree();
	Local l1;

	sprintf(buffer, "\t%dh%02d (%dh%02d ", h.getHeure(), h.getMinute(), h2.getHeure(), h2.getMinute());

	for(itl.reset() ; !itl.end() ; itl++)
	{
		l1 = (Local) itl;

		if(strcmp(l1.getIdentifiant(), c.getLieu()) == 0)
		{
			strcat(buffer, l1.getNom());
			break;
		}
	}

	strcat(buffer, ") ");
	strcat(buffer, c.getIntitule());
	strcat(buffer, " : ");


	length = strlen(buffer);
	ofs.write((char*) buffer, length * sizeof(char));

	for(itp.reset() ; !itp.end() ; itp++)
	{
		p1 = (Professeur) itp;

		if(strcmp(p1.getIdentifiant(), c.getProfesseur()) == 0)
		{
			strcpy(buffer, p1.getNom());
			strcat(buffer, " ");
			strcat(buffer, p1.getPrenom());
			length = strlen(buffer);
			ofs.write((char*) buffer, length * sizeof(char));			
			break;
		}
	}	

	ofs.write("\n", sizeof(char));
}

void Horaire::exportLocal(ofstream& ofs, const Cours& c, char* day)
{
	char buffer[100];
	Iterateur<Professeur> itp(professeurs);
	Iterateur<Local> itl(locaux);
	Iterateur<Groupe> itg(groupes);
	Iterateur<Cours> itc(courses);
	int length;
	Professeur p1;

	if(day == NULL || strcmp(day, c.getTiming().getJour()) != 0)
	{
		strcpy(day, c.getTiming().getJour());

		strcpy(buffer, day);
		strcat(buffer, " : \n");

		length = strlen(buffer);
		ofs.write((char*) buffer, length * sizeof(char));
	}

	Timing t = c.getTiming();
	Temps h = t.getHeure();
	Temps h2 = t.getDuree();

	for(itp.reset() ; !itp.end() ; itp++)
	{
		p1 = (Professeur) itp;

		if(strcmp(p1.getIdentifiant(), c.getProfesseur()) == 0)
		{		
			break;
		}
	}	

	sprintf(buffer, "\t%dh%02d (%dh%02d %s %s", h.getHeure(), h.getMinute(), h2.getHeure(), h2.getMinute(), p1.getNom(), p1.getPrenom());

	strcat(buffer, ") ");
	strcat(buffer, c.getIntitule());
	strcat(buffer, " : ");

	length = strlen(buffer);
	ofs.write((char*) buffer, length * sizeof(char));

	ListeTriee<char*> zz(c.getGroupes());

	Iterateur<char*> itg2(zz);

	for(itg2.reset() ; !itg2.end() ; itg2++)
	{
		strcpy(buffer, (char*) itg2);
		strcat(buffer, " ");

		length = strlen(buffer);
		ofs.write(buffer, sizeof(char) * length);
	}

	length = strlen(buffer);
	ofs.write((char*) buffer, length * sizeof(char));


    ofs.write("\n", sizeof(char));
}

void Horaire::setHoraire(const char* h)
{
	if(horaire) delete horaire;

	horaire = new char[strlen(h) + 1];

	strcpy(horaire, h);
}

