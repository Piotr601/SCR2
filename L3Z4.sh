#!/bin/bash

plik=~/Documents/Lab3/Zad4/FIFO

# Nie dziala :/
bash cat < $plik &
bash cat < $plik &
bash cat > $plik &
bash cat > $plik &
