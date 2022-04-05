# L'exécutable à générer :
EXEC=main

# Les fichiers .o a générer si nécessaire
DEP=boardgame.o

all: main

#Variables personnalisées
CC=gcc
CFLAGS=-Wall 
LDFLAGS=

%.o: %.c 
	$(CC) -c $^ $(CFLAGS)

main: $(DEP)
	$(CC) $(CFLAGS) -o $(EXEC) boardgame.c $(DEP)

#### RAPPEL ################
#
#   $@    Nom de la cible
#   $<     Nom de la première dépendance pour la cible
#   $ˆ      Liste des dépendances pour la cible
#   $?     Liste des dépendances plus récentes que la cible Nom du fichier (sans son suffixe)
#   $*      Nom du fichier (sans son suffixe)
#    % : permet de prendre un élément après l'autre dans une liste de cibles
##################

#supprimer les fichier *.o 
clean:
	rm -rf *.o $(EXEC)

#supprimer les fichiers *.o et les exécutables
mrproper: clean
	rm -rf $(EXEC) 