MAJOR=1
MINOR=3
PATCH=0

#General purpouse
all: main

clean:
	rm -rf dist lib main

.PHONY: all deb clean


#Linux directives
deb: var.o
	mkdir -p deb/DEBIAN

	cat unix/control.in | sed \
	 -e s/@MAJOR/${MAJOR}/g \
	 -e s/@MINOR/${MINOR}/g \
	 -e s/@PATCH/${PATCH}/g > deb/DEBIAN/control

	mkdir -p deb/usr/include
	cp include/* deb/usr/include

	mkdir -p deb/usr/lib/
	cp lib/var.o deb/usr/lib/libvar.a
	mkdir -p dist && dpkg -b deb/ dist/
	rm -rf deb

main: main.cpp var.o
	g++ lib/var.o main.cpp -I include -o main

var.o:
	mkdir -p lib
	g++ src/* -I include -c -Wall -o lib/var.o

