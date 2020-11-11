#!/bin/sh

#__________________________________________________________________________________

# 10 SIGUSR1 - pierwszy sygnal definiowany przez uzytkownika

# 12 SIGUSR2 - drugi sygnal definiowany przez uzytkownika

# 14 SIGALRM - sygnal budzika, uzywajac funkcji systemowej alarm() okresla,
#              kiedy dany proces ma zostac obudzony

# 15 SIGTERM - standardowy sygnal generowany przez oprogramowanie (domyslny KILL)
#__________________________________________________________________________________

# ------------------------------------------------------------------------#
# a) wyswietlenie komunikatu i zakonczenie pracy programu
# ------------------------------------------------------------------------#

# Lapanie sygnalu i zakonczenie pracy programu
trap "echo Zlapany SIGUSR1; kill -9 0" 10

#-------------------------------------------------------------------------#
# b) wyswietlenie komunikatu i powrot do wykonywania programu
#-------------------------------------------------------------------------#

# Lapanie sygnalu i powrot do wykonywania programu
trap "echo Zlapany SIGUSR2" 12
#-------------------------------------------------------------------------#
# c) wstrzymywanie odbierania sygnalu i nastepnie wznowienie odbierania
#-------------------------------------------------------------------------#

trap "echo Lapanie SIGALRM; zlapany()" 13

#-------------------------------------------------------------------------#
# d) calkowite ignorowanie sygnalow
#-------------------------------------------------------------------------#

trap "echo Ignorowanie sygnalow; ignorowanie()" 15

zlapany(){
    trap "Lapanie sygnalu SIGALRM" 14
    for i in $(seq 1 1000);
    do
	i=i+1
	sleep 1
    done
}

ignorowanie(){
  trap "ignorowanie" 1 2 3 4 5 6 7 8 10 11 12 13 14 15
}


# PROGRAM
i=1

while (true);
do
    i=i+1
    sleep 0.1
    
done
