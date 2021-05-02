#!/bin/sh
cd $1
for d in *; 
do
    if [ -d $ d ]; then
	if [ ls -l $1|grep $d|grep '^d.......w.'>/dev/null ]; then
	    echo "Danger ! Tout le monde peut écrire dans $1/$d"
	fi
    fi
done
