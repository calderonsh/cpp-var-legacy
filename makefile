PROJECT=libvar
GPPINCS=
GPPFLAGS=-std=c++11 -Wall -Werror -pedantic -O2
GPPLIBS=

MAJOR=0
MINOR=4
PATCH=1

OBJS= \
obj/var.o \

EXTENSION=so
ifeq ($(shell uname -s), Darwin)
EXTENSION=dylib
endif

.PHONY: all deb $(EXTENSION) clean

#General purpouse
all: dist

clean:
	rm -rf dist $(EXTENSION) obj

install: $(EXTENSION)/$(PROJECT).$(EXTENSION)
	cp $(EXTENSION)/$(PROJECT).$(EXTENSION) /usr/lib
	mkdir -p /usr/include/var && cp include/var/* /usr/include/var

$(EXTENSION): $(EXTENSION)/$(PROJECT).$(EXTENSION)

$(EXTENSION)/$(PROJECT).$(EXTENSION): obj/var.o
	mkdir -p $(EXTENSION)
	g++ obj/var.o -shared -o $(EXTENSION)/$(PROJECT).$(EXTENSION)

obj/%.o: src/%.cpp
	mkdir -p obj
	g++ $< -I include $(GPPINCS) $(GPPFLAGS) -c -fPIC -o $@


#Linux directives
dist: deb

deb: $(EXTENSION)/$(PROJECT).$(EXTENSION)
	mkdir -p deb/DEBIAN

	cat unix/control.in | sed \
	 -e s/@MAJOR/${MAJOR}/g \
	 -e s/@MINOR/${MINOR}/g \
	 -e s/@PATCH/${PATCH}/g > deb/DEBIAN/control

	mkdir -p deb/usr/include
	cp -r include/* deb/usr/include

	mkdir -p deb/usr/lib/
	cp $(EXTENSION)/$(PROJECT).$(EXTENSION) deb/usr/lib/

	mkdir -p dist
	dpkg -b deb/ dist

	rm -rf deb

