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

# ajout fichier de compression simplifié dans le dossier resultat

# merge des needs et functions
- vérifier les doublons needs
- vérifier les doublons functions

# Fichier compilation
- ajouter une option, pour ajouter le nom du fichier par defaut à la compilation
Par exemple :
```
./simplifac.sh -d myprogram process pipe
```
Va permettre de directement pouvoir lancer :
```
./compilC.sh
```
(Celui se trouvant dans le dossier myprogram.result)
