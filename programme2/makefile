all: main.c avl.c elt.c dict.c 
	gcc main.c avl.c elt.c dict.c -o indexation.exe -lm
	@echo "Le programme indexation.exe a été produit dans le répertoire programme2/"

clean :
	rm -rf indexation.exe

# supprime les contenus des sous-repertoires output
mrproper:
	@echo "Suppression des fichiers output/"
	rm -rf output/*/*