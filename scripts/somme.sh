#!/bin/sh
n=$1
somme=$1
while [ $n -gt 1 ]
do
n=`expr $n-1`
somme=`expr $somme+$n`
done
echo "Somme = $somme."