# The executable to generate :
EXEC=boardgame

# .o files to generate if necessary
DEP=

all: $(EXEC)

#Variables personnalisées
CC=gcc
CFLAGS=-Wall 
LDFLAGS=

%.o: %.c boardgame.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC): $(EXEC).c $(DEP) boardgame.h
	$(CC) $(CFLAGS) -o $@ $(DEP) $<

###################### REMINDER ###############################
#
#   $@    Name of the target
#   $<    Name of the first dependance for the target
# 	$ˆ 	  List of dependencies for the target
# 	$?    List of dependencies newer than the target File name (without its suffix)
# 	$*    File name (without its suffix)
# 	% 	  Allows to take one element after another in a list of targets
###############################################################

#delete the *.o files 
clean:
	rm -rf *.o $(EXEC)

#delete *.o files and executables
mrproper: clean
	rm -rf $(EXEC) 