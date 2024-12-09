# écrire la commande de compilation simplifié
La compilation C demandé :
```sh
gcc -Wall -Wextra -std=c99 -o FILE FILE.c
```

# écrire la commande de compression simplifié
- écrire un script qui génère une archive depuis DIR ou FILE, en prenant en compte un .ignore (s'il existe)

Commandes déjà utilisées :
```sh
tar -czvf NOMARCHIVE.tar.gz FICHIER...
tar --exclude-from=CHEMINVERS.ignore -czvf NOMARCHIVE.tar.gz DIR
```
Décompression
```sh
tar -zxvf NOMARCHIVE.tar.gz
```

# écrire la commande principale : simplifac

voir : simpliTODO.md
