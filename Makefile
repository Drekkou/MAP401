#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2024/2025
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = test_image test_geometrie2d test_bezier2 tache3 tache4 tache5 tache6 tache7-1 tache7-2 tache8


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
geometrie2d.o : geometrie2d.c geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geometrie2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

image.o : image.c image.h geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_image.o : test_image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

 
test_geometrie2d.o : test_geometrie2d.c geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_geometrie2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
 
 
contour.o : contour.c contour.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
 
export_eps.o : export_eps.c export_eps.h simplification.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module export_eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
 
simplification.o : simplification.c simplification.h bezier.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

bezier.o : bezier.c bezier.h contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module bezier2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_bezier2.o : test_bezier2.c simplification.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_bezier2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

tache3.o : tache3.c contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tache3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

tache4.o : tache4.c export_eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tache4"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

tache5.o : tache4.c export_eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tache4"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

tache6.o : tache4.c export_eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tache4"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

tache7-1.o : tache7-1.c export_eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tache7-1"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

tache7-2.o : tache7-2.c export_eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tache7-2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

tache_pre.o : tache_pre.c tache_pre.h export_eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tache7-2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
	
tache8.o : tache8.c tache_pre.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tache8"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
########################################################
# regles explicites de creation des executables

test_image : test_image.o image.o geometrie2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@
 
test_geometrie2d : test_geometrie2d.o geometrie2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_bezier2 : test_bezier2.o simplification.o bezier.o contour.o image.o geometrie2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

tache3: tache3.o image.o geometrie2d.o contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

tache4: tache4.o export_eps.o simplification.o bezier.o image.o geometrie2d.o contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@


tache5: tache4.o export_eps.o simplification.o bezier.o image.o geometrie2d.o contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

tache6: tache4.o export_eps.o simplification.o bezier.o image.o geometrie2d.o contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

tache7-1: tache7-1.o export_eps.o simplification.o bezier.o image.o geometrie2d.o contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@
 
tache7-2 : tache7-2.o export_eps.o simplification.o bezier.o image.o geometrie2d.o contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

tache8 : tache8.o tache_pre.o export_eps.o simplification.o bezier.o image.o geometrie2d.o contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "----------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
