#!/bin/sh
while true;
do
if who|grep $1; then
echo $1 est arrivé!
exit 0
fi
sleep 10
done
