#include <stdio.h>
#include <unistd.h>

int main()
{
  int i=0;
  
  while(1)
  {
    i++;
    sleep(0.1);
  }
}

/*
 Program po uruchomieniu znalazl sie na pierwszej pozycji listy htop, podobnie
 jak w programie napisanym w bashu. Po dodaniu powyzszego sleepa nieco zmienilo
 sie to. Program zaczal najpierw u gory, a nastepnie przesuwal sie ku dolowi.
 Tak sie to powtarzalo, gdy program realizowal sleepa.

 Aby to zaobserwowac konieczne bylo zmienienie czestotliwosci wyswietlania
 programu htop (albo alternatywnie top). Robi sie to ponizsza komenda:

                    "htop -d ss.tt / top -d ss.tt"

 gdzie -d oznacza parametr delay (czyli czestosc pomiedzy odswiezaniem htopa)
 ss - sekundy, tt - dziesiatki sekund (seconds.tenths).

 Program htop wywolano:
    "htop -d 00.5"
 */
