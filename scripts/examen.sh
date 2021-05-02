#!/bin/sh
# commande examen.sh
rep=/home/jeremy

n=`ls -l $rep | grep "^-.*" | sed 's/^\([^ ]*\) *\([0-9]\) *\([^ ]*\).*/\3/'`
echo $n
