#!/bin/bash

i=1241421412414214141

while true;
do
  k=$[i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i*i]
done

# Napisano powyzszy zasobozerny skrypt, a nastepnie odpalono 5 skryptow.
# Ustawiono im wartosc nice na rozne tj: (-19, -5, 0, 6, 19). Po wpisaniu
# komendy htop lub top (osobiscie korzystalem z tej pierwszej) mozna bylo
# zauwazyc, ze zuzycie procesora jest proporcjonalne do wartosci nice. Dla
# tych skryptow bylo to kolejno: (100.0%, 97.4%, 76.2%, 26.5%, 2.0%). Komende
# nice wywoluje sie [ nice -n priorytet ], zas renice [renice -n priorytet -p
# PID]. Nalezy jednak pamietac ze mozemy zwiekszac i zmniejszac priorytety
# dowolnie i je ustawiac przed uruchomieniem programu. Po uruchomieniu
# mozna juz tylko zmniejszac priorytet - zwiekszenie jest dozwolone, ale
# tylko za zgoda super-usera ( sudo ), a wiec trzeba zwiekszac priorytet
# poprzez dodanie sudo przez resize ( na wiekszy np. z +5 -> -9 )
#
# POLECENIE: sudo renice -n (Wartosc Priorytetu) -p (ID procesu)
