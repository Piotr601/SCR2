#!/bin/bash

sciezka="~/Downloads"

for mail in $(cat $sciezka/adresy.txt)
do
cat $sciezka/tresc.txt | mutt -s "Okna z PCV" $mail -a $sciezka/spec*.pdf
done
