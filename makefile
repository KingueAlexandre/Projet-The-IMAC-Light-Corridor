CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

BINDIR	= bin/
INCDIR	= inc/
SRCDIR	= src/
OBJDIR	= obj/

# Fichiers MAIN
GLOB_OBJ_TD= $(OBJDIR)3D_tools.o

# Fichiers Projets

OBJ_MAIN= $(GLOB_OBJ_TD) $(OBJDIR)game/draw_scene.o $(OBJDIR)game/Mur.o $(OBJDIR)game/Balle.o $(OBJDIR)game/Joueur.o $(OBJDIR)game/Event.o $(OBJDIR)game/main.o
EXEC_main= main

# Regles compilation TD 04

all : main

main : $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ_MAIN) -o $(BINDIR)$(EXEC_main) $(LDFLAGS)

draw_scene.o : draw_scene.c draw_scene.h Mur.h Balle.h Joueur.h stb_image.h
	mkdir -p `dirname $@`
	$(CC) -o  $@ -I $(INCDIR) -c $< $(CFLAGS)

Balle.o : Balle.c Balle.h Mur.h Joueur.h
	mkdir -p `dirname $@`
	$(CC) -o  $@ -I $(INCDIR) -c $< $(CFLAGS)

Event.o : Event.c Event.h 3D_tools.h Mur.h Joueur.h
	mkdir -p `dirname $@`
	$(CC) -o  $@ -I $(INCDIR) -c $< $(CFLAGS)

clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCDIR)*.h
	mkdir -p `dirname $@`
	$(CC) -o $@ -I $(INCDIR) -c $< $(CFLAGS)