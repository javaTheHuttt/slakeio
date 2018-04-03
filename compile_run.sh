# Runterladen vom Code: https://github.com/nsf/termbox/
#git clone https://github.com/nsf/termbox/
# In den Ordner
#cd ./termbox
# Einrichtgen, dass es lokal installiert
#./waf configure --prefix=${HOME}/.local
# Kompilieren
#./waf
# Installieren
#mkdir -p ${HOME}/.local && ./waf install
# Jetzt linken, dafür muss mit -L auch der Suchpfad angegeben werden
gcc -std=c99 -Wall -Wextra -pedantic -I${HOME}/.local/include main.c -o main -ltermbox -L${HOME}/.local/lib

env LD_LIBRARY_PATH=${HOME}/.local/lib ./main
