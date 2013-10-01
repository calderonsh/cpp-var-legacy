MAJOR=1
MINOR=3
PATCH=1

#General purpouse
all: main

clean:
	rm -rf dist lib main

.PHONY: all deb clean


#Linux directives
deb: lib/var.o
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

main: main.cpp lib/var.o
	g++ lib/var.o main.cpp -I include -Wall -Werror -o main

lib/var.o: src/var.cpp include/var.hpp
	mkdir -p lib
	g++ src/var.cpp -I include -c -Wall -Werror -o lib/var.o

