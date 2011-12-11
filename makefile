
MAJOR=0
MINOR=3
PATCH=0

all: clean var.o main

deb: var.o
	mkdir -p deb/DEBIAN

	echo Package: cpp-var > deb/DEBIAN/control
	echo Priority: extra >> deb/DEBIAN/control
	echo Version: $(MAJOR).$(MINOR).$(PATCH) >> deb/DEBIAN/control
	echo Architecture: i386 >> deb/DEBIAN/control
	echo Maintainer: Miguel Passos Calderon \<pcmiguel85@gmail.com\> >> deb/DEBIAN/control
	echo Depends: g++ >> deb/DEBIAN/control
	echo Description: CPP-VAR is a library that implements dynamically typed variables for C++. >> deb/DEBIAN/control
	echo \ CPP-VAR is intended to facilitate the portability of scripts and programs from >> deb/DEBIAN/control
	echo \ other languages ​​to C++, and accelerate the development of other facilities >> deb/DEBIAN/control
	echo \ deploying languages ​​and frameworks for the syntax and robustness of C++ and STL. >> deb/DEBIAN/control

	mkdir -p deb/usr/include
	cp include/* deb/usr/include

	mkdir -p deb/usr/lib/
	cp lib/var.o deb/usr/lib/libvar.a
	dpkg -b deb/ .
	rm -rf deb

main:
	g++ lib/var.o main.cpp -O2 -s -I include -o main

var.o:
	mkdir -p lib
	g++ src/* -O2 -s -I include -c -Wall -o lib/var.o

clean:
	rm -rf lib main *.deb
