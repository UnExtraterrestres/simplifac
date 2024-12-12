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

# BUGFIX
=> dans la génération du chemin de resultats
Exemple : 
```sh
[user]$ ./simplifac.sh ../coursL2/sys/TP10/seq_pi process tube

touch: impossible de faire un touch '../coursL2/sys/TP10/seq_pi.result/../coursL2/sys/TP10/seq_pi.c': Aucun fichier ou dossier de ce nom
Error : touch '../coursL2/sys/TP10/seq_pi.result/../coursL2/sys/TP10/seq_pi.c' failed
For more information, please use : ./simplifac.sh --help
```
