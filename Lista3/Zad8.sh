#!/bin/bash

while true;
do
   ./Zad8.sh
done

# Ustawiono limit na 1 000 procesow i nastepnie uruchomiono skrypt w
# terminalu. Po zapelnieniu sie wszystkich miejsc przez procesy, zaczely
# wystepowac bledy w terminalu mowiace o braku miejsca dla kolejnych procesow.
# Komunikat "fork: retry: Resource temporarily unavailable" wystepowal podczas
# dzialania programu i zapelnieniu sie ograniczonego miejsca.
#
# Procesy zostaly pozabijane poprzez otwarcie nowego terminala i wpisaniu
# komendy kill all, ktora zabila istniejace procesy, w tym procesy utworzeone
# przez powyzszy skrypt.
# Mozna rowniez sprobowac zabic terminal / basha, a wraz z nim wszystkie 
# uruchomione w nim aplikacje / programy / skrypty rowniez sie zamkna.
# Ostateczna opcja wylaczenia i opanowania sytuacji jest odlaczenie komputera
# od zrodla zasilania, badz zrestartowanie go.
