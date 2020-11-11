#!/bin/bash

i=1

while (true);
do
    i=i+1
    sleep 0.1
done

# Program po uruchomieniu wlaczal sie i byl na pierwszej pozycji listy htop.
# Po dodaniu sleepa i zwiekszeniu czasu odswiezania htop / top komenda:
# "htop -d ss.tt / top -d ss.tt" program przez krotka chwile byl u gory, a
# potem przesuwal sie nizej
#
# wywolano program "htop -d 00.5"
