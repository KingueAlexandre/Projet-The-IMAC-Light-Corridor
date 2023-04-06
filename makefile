CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# Fichiers TD 03

# Fichiers exercice 01
OBJ_TD03_EX01= ex01/td05_ex01.o
EXEC_TD03_EX01= td05_ex01.out

# Regles compilation TD 04

all : ex01 #ex02

ex01 : $(OBJDIR)$(OBJ_TD03_EX01)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD03_EX01) -o $(BINDIR)$(EXEC_TD03_EX01) $(LDFLAGS)

clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)
