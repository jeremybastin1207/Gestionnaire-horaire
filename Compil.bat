del *.o
g++ Lib/Event.cxx -c
g++ Lib/Timing.cxx -c
g++ Lib/Temps.cxx -c
g++ Lib/InvalidTimingException.cxx -c
g++ Lib/InvalidTempsException.cxx -c
g++ Lib/Planifiable.cxx -c
g++ Lib/Professeur.cxx -c
g++ Lib/Groupe.cxx -c
g++ Lib/Local.cxx -c
g++ Lib/Cours.cxx -c
g++ Lib/SmartPointer.cxx -c
g++ Lib/ListeBase.cxx -c
g++ Lib/Liste.cxx -c
g++ Lib/ListeTriee.cxx -c
g++ Lib/Iterateur.cxx -c
g++ Lib/Horaire.cxx -c
g++ Event.o Timing.o Temps.o InvalidTimingException.o InvalidTempsException.o Planifiable.o Professeur.o Groupe.o Local.o Cours.o SmartPointer.o ListeBase.o Liste.o ListeTriee.o Iterateur.o Horaire.o main.cxx -o Application.exe
pause
del *.o
start Application.exe