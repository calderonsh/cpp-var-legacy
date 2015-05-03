GPPINCS=
GPPFLAGS=-std=c++11 -Wall -Werror -pedantic -O2

MAJOR=1
MINOR=4
PATCH=0

#General purpouse
all: main

clean:
	rm -rf dist dylib obj main 

.PHONY: all deb dylib clean

EXTENSION=so
ifeq ($(shell uname -s), Darwin)
EXTENSION=dylib
endif

install: $(EXTENSION)/libvar.$(EXTENSION)
	cp $(EXTENSION)/libvar.$(EXTENSION) /usr/lib
	mkdir -p /usr/include/var && cp include/var/var.hpp /usr/include/var

main: main.cpp obj/var.o
	g++ obj/var.o main.cpp -I include/var $(GPPINCS) $(GPPFLAGS) -o main

$(EXTENSION): $(EXTENSION)/libvar.$(EXTENSION)

$(EXTENSION)/libvar.$(EXTENSION): obj/var.o
	mkdir -p $(EXTENSION) && g++ obj/var.o -shared -fPIC -o $(EXTENSION)/libvar.$(EXTENSION)

obj/var.o: src/var.cpp include/var/var.hpp
	mkdir -p obj
	g++ src/var.cpp -I include/var -c $(GPPFLAGS) -o obj/var.o


#Linux directives
deb: obj/var.o
	mkdir -p deb/DEBIAN

	cat unix/control.in | sed \
	 -e s/@MAJOR/${MAJOR}/g \
	 -e s/@MINOR/${MINOR}/g \
	 -e s/@PATCH/${PATCH}/g > deb/DEBIAN/control

	mkdir -p deb/usr/include
	cp -r include/* deb/usr/include

	mkdir -p deb/usr/lib/
	cp obj/var.o deb/usr/lib/libvar.a
	mkdir -p dist && dpkg -b deb/ dist
	rm -rf deb


#Windows directives
main.exe: main.cpp lib/var.lib
	i586-mingw32msvc-g++ lib/var.lib main.cpp -I include/var $(GPPFLAGS) -o main.exe

lib/var.lib: src/var.cpp
	mkdir -p lib
	i586-mingw32msvc-g++ src/var.cpp -I include/var -c $(GPPFLAGS) -o lib/var.lib
