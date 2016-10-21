#include "Lib/Horaire.h"

using namespace std;

int main ()
{
	Horaire horaire;
	int choice;
	do
	{
		choice = horaire.selectMenu();
		horaire.executeAction(choice);
	}while(choice != 0);
}