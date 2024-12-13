# écrire la commande de compression simplifié
- écrire un script qui génère une archive depuis DIR ou FILE, en prenant en compte un .ignore (s'il existe)

Commandes déjà utilisées :
```sh
tar -czvf NOMARCHIVE.tar.gz FICHIER...
tar --exclude-from=CHEMINVERS.ignore -czvf NOMARCHIVE.tar.gz DIR
```
Décompression
```sh
unzip nom_du_fichier.zip
tar -xzvf nom_du_fichier.tar.gz
```

# migration sous C
- voir si une migration sous C change quelque chose

# ajout fichier de compression simplifié dans le dossier resultat

# merge des needs et functions
- vérifier les doublons needs
- vérifier les doublons functions
