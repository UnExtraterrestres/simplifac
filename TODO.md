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

# migration sous C
- voir si une migration sous C change quelque chose

# sysfunc
- execvp, exec* ...
- ouverture de fichier en descripteur
- exemples de scripts : utilisation d'un processus fils, tube, fichier, ...

# ajout fichier de compression simplifié dans le dossier resultat
