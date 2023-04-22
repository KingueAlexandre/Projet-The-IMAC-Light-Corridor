CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

BINDIR	= bin/
INCDIR	= inc/
SRCDIR	= src/
OBJDIR	= obj/

# Fichiers TD 04
GLOB_OBJ_TD= $(OBJDIR)3D_tools.o

# Fichiers exercice 01

OBJ_TD04_EX04= $(GLOB_OBJ_TD) $(OBJDIR)ex04/draw_scene.o $(OBJDIR)ex04/td04_ex04.o
EXEC_TD04_EX04= td04_ex04.out
OBJ_MAIN= $(GLOB_OBJ_TD) $(OBJDIR)game/draw_scene.o $(OBJDIR)game/Mur.o $(OBJDIR)game/Balle.o $(OBJDIR)game/main.o
EXEC_main= main.out

# Regles compilation TD 04

all : main

ex04 : $(OBJ_TD04_EX04)
	$(CC) $(CFLAGS) $(OBJ_TD04_EX04) -o $(BINDIR)$(EXEC_TD04_EX04) $(LDFLAGS)

main : $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ_MAIN) -o $(BINDIR)$(EXEC_main) $(LDFLAGS)

draw_scene.o : draw_scene.c draw_scene.h Mur.h Balle.h
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