# Projet de Traverse
## Par Clément Bertails, Maxime Longuet et Pierrick Maurer
 
Contient le Projet de Traverse.

## Dépendances

 - Librairie SDL2
 - Langage C (win : mingw)

## Compilation :

    - Windows:    
    ```bash
    gcc src/*.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
    ```
    - GNU/Linux MacOS :
    ```bash
    gcc *.c $(sdl2-config --cflags --libs) -o prog -lSDl2_image
    ```
    - Makefile
    ```bash
    make
    ```

## Utilisation :
Pour que l'affichage se fasse correctement, il faut un terminal en utf-8 
```bash 
chcp 65001
```
Pour lancer le programme, utiliser prog (se trouvant dans bin\).
```bash
cd /bin
./prog
```
Un terminal devrait s'ouvrir, avec un premier menu.
Entrer le mode que vous souhaitez lancer :

 - JcJ avec affichage terminal
 - JcJ avec affichage graphique
 - JcOrdi facile, graphique (NE FONCTIONNE PAS : TODO IA)
 - JcOrdi difficile,  graphique (NE FONCTIONNE PAS : TODO IA)
