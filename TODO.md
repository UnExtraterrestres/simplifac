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
