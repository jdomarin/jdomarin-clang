#!/bin/sh
cd Espace\ C/TP1
mkdir Sources
mv *.c Sources
mkdir Divers
mv * Divers
mv Divers/Sources .
echo "le répertoire TP1/Sources contient"
ls Sources
echo "le répertoire TP1/Divers contient"
ls Divers