.SILENT:
COMPIL = g++ -I $(LIB)

LIB = Lib
ALL = $(LIB)/SmartPointer.o $(LIB)/Event.o $(LIB)/Cours.o $(LIB)/Groupe.o $(LIB)/InvalidTempsException.o $(LIB)/InvalidTimingException.o $(LIB)/Iterateur.o $(LIB)/Liste.o $(LIB)/ListeBase.o $(LIB)/ListeTriee.o $(LIB)/Local.o $(LIB)/Planifiable.o $(LIB)/Professeur.o $(LIB)/Temps.o $(LIB)/Timing.o $(LIB)/Horaire.o

Applic:	$(ALL) main.cxx
		echo Compilation de l application...
		$(COMPIL) $(ALL) main.cxx -o Applic
		clear
		./Applic

$(LIB)/SmartPointer.o:	$(LIB)/SmartPointer.h $(LIB)/SmartPointer.cxx
		echo Compilation de SmartPointer...
		$(COMPIL) $(LIB)/SmartPointer.cxx -c
		mv SmartPointer.o $(LIB)


$(LIB)/Event.o:	$(LIB)/Event.h $(LIB)/Event.cxx
		echo Compilation de Event...
		$(COMPIL) $(LIB)/Event.cxx -c
		mv Event.o $(LIB)

$(LIB)/Cours.o:	$(LIB)/Event.h $(LIB)/Cours.cxx $(LIB)/Cours.h
		echo Compilation de Cours...
		$(COMPIL) $(LIB)/Cours.cxx -c
		mv Cours.o $(LIB)

$(LIB)/Groupe.o:	$(LIB)/Groupe.h $(LIB)/Groupe.cxx
		echo Compilation de Groupe...
		$(COMPIL) $(LIB)/Groupe.cxx -c
		mv Groupe.o $(LIB)

$(LIB)/Horaire.o:	$(LIB)/Horaire.h $(LIB)/Horaire.cxx
		echo Compilation de Horaire...
		$(COMPIL) $(LIB)/Horaire.cxx -c
		mv Horaire.o $(LIB)

$(LIB)/InvalidTempsException.o:	$(LIB)/InvalidTempsException.h $(LIB)/InvalidTempsException.cxx
		echo Compilation de InvalidTempsException...
		$(COMPIL) $(LIB)/InvalidTempsException.cxx -c
		mv InvalidTempsException.o $(LIB)

$(LIB)/InvalidTimingException.o:	$(LIB)/InvalidTimingException.h $(LIB)/InvalidTimingException.cxx
		echo Compilation de InvalidTimingException...
		$(COMPIL) $(LIB)/InvalidTimingException.cxx -c
		mv InvalidTimingException.o $(LIB)

$(LIB)/Iterateur.o:	$(LIB)/Iterateur.h $(LIB)/Iterateur.cxx
		echo Compilation de Iterateur...
		$(COMPIL) $(LIB)/Iterateur.cxx  -c
		mv Iterateur.o $(LIB)

$(LIB)/Liste.o:	$(LIB)/Liste.h $(LIB)/Liste.cxx
		echo Compilation de Liste...
		$(COMPIL) $(LIB)/Liste.cxx -c
		mv Liste.o $(LIB)

$(LIB)/ListeBase.o:	$(LIB)/ListeBase.h $(LIB)/ListeBase.cxx
		echo Compilation de ListeBase...
		$(COMPIL) $(LIB)/ListeBase.cxx -c
		mv ListeBase.o $(LIB)

$(LIB)/ListeTriee.o:	$(LIB)/ListeTriee.h $(LIB)/ListeTriee.cxx
		echo Compilation de ListeTriee...
		$(COMPIL) $(LIB)/ListeTriee.cxx  -c
		mv ListeTriee.o $(LIB)

$(LIB)/Local.o:	$(LIB)/Local.h $(LIB)/Local.cxx
		echo Compilation de Local...
		$(COMPIL) $(LIB)/Local.cxx -c
		mv Local.o $(LIB)

$(LIB)/Planifiable.o:	$(LIB)/Planifiable.h $(LIB)/Planifiable.cxx
		echo Compilation de Planifiable...
		$(COMPIL) $(LIB)/Planifiable.cxx -c
		mv Planifiable.o $(LIB)

$(LIB)/Professeur.o:	$(LIB)/Professeur.h $(LIB)/Professeur.cxx
		echo Compilation de Professeur...
		$(COMPIL) $(LIB)/Professeur.cxx -c
		mv Professeur.o $(LIB)

$(LIB)/Temps.o:	$(LIB)/Temps.h $(LIB)/Temps.cxx
		echo Compilation de Temps...
		$(COMPIL) $(LIB)/Temps.cxx -c
		mv Temps.o $(LIB)

$(LIB)/Timing.o:	$(LIB)/Timing.h $(LIB)/Timing.cxx
		echo Compilation de Timing...
		$(COMPIL) $(LIB)/Timing.cxx  -c
		mv Timing.o $(LIB)
clean:	
		rm -f $(LIB)/*.o 
		rm Applic
