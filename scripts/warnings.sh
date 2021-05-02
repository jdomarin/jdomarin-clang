#!/bin/sh

# tester si le bon nombre d'arguments a été donné

if [ $# -ne 1 ]
then
 echo "donner le nom de l'executable en argument"
 exit 1
fi

# récupérer la liste des fichiers sources, et créer un fichier pour
# stocker les résultats

note=0
fichiers=`ls warnings`
rm -f $1.rapport
touch $1.rapport

# pour chaque fichier...
for f in $fichiers
do

# exécuter l'exécutable dessus et récupère la sortie

./$1 warnings/$f > output

# si la sortie affiche un WARNING incrémenter la note

grep -q "WARNING" output
if [$? -eq 0 ]
then
 note=`expr $note + 1`
else

 # si erreur, indiquer le nom du fichier et recopier
 # la sortie du programme dans le rapport

 echo "Erreur avec le fichier $f" >> $1.rapport
 echo output > $1.rapport 
fi
done

# si le rapport ne contient pas d'erreurs, afficher "parfait"

grep -q "^Erreurs$" $1.rapport 
if [ $? -eq 1 ]
then
 echo "Parfait !" >> $1.rapport
fi

#ajouter la note de l'exécutable dans le rapport

echo note > $1.rapport 

# nettoyage

rm output
