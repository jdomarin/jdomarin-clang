#!/bin/sh
if [ ! -e ~/Archives ]; then
    mkdir ~/Archives
fi
if [ ! -e $1 ]; then 
echo " $0 : $1 n'existe pas"
exit 1
fi
for fich in $1/*; do
if [ ! -d $fich ]; then if [ -x $fich ];then
	cp $fich ~/Archives
fi;fi
done
