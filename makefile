GPPINCS=
GPPFLAGS=-std=c++11 -Wall -Werror -pedantic -O2
GPPLINKS=

MAJOR=1
MINOR=4
PATCH=0

.PHONY: all deb so dylib clean

EXTENSION=so
ifeq ($(shell uname -s), Darwin)
EXTENSION=dylib
endif

#General purpouse
all: dist

clean:
	rm -rf dist $(EXTENSION) obj

main: main.cpp obj/var.o
	g++ obj/var.o main.cpp -I include/var $(GPPINCS) $(GPPFLAGS) -lphp -o main

install: $(EXTENSION)/libvar.$(EXTENSION)
	cp $(EXTENSION)/libvar.$(EXTENSION) /usr/lib
	mkdir -p /usr/include/var && cp include/var/var.hpp /usr/include/var

$(EXTENSION): $(EXTENSION)/libvar.$(EXTENSION)

$(EXTENSION)/libvar.$(EXTENSION): obj/var.o
	mkdir -p $(EXTENSION)
	g++ obj/var.o -shared -o $(EXTENSION)/libvar.$(EXTENSION)

obj/var.o: src/var.cpp include/var/var.hpp
	mkdir -p obj
	g++ src/var.cpp -I include/var -c $(GPPFLAGS) -fPIC -o obj/var.o


#Linux directives
dist: deb

deb: $(EXTENSION)/libvar.$(EXTENSION)
	mkdir -p deb/DEBIAN

	cat unix/control.in | sed \
	 -e s/@MAJOR/${MAJOR}/g \
	 -e s/@MINOR/${MINOR}/g \
	 -e s/@PATCH/${PATCH}/g > deb/DEBIAN/control

	mkdir -p deb/usr/include
	cp -r include/* deb/usr/include

	mkdir -p deb/usr/lib/
	cp so/libvar.so deb/usr/lib/libvar.so

	mkdir -p dist
	dpkg -b deb/ dist

	rm -rf deb

