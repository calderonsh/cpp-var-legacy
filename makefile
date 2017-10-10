PROJECT=var
DESCRIPTION="Dynamically typed variables for C++"
DEPENDS="g++"

MAJOR=0
MINOR=4
PATCH=3

GPPINCS=
GPPLIBS=
GPPFLAGS=-std=c++11 -Wall -Werror -pedantic -O2

OBJS= \
obj/var.o \

BINARY=lib$(PROJECT)

EXTENSION=so
ifeq ($(shell uname -s), Darwin)
EXTENSION=dylib
endif

PACKAGE=lib$(PROJECT)
OUTPUT=$(EXTENSION)/$(PACKAGE).$(EXTENSION)

.PHONY: all deb $(EXTENSION) clean

#General purpouse
all: dist

clean:
	rm -rf dist $(EXTENSION) obj

install: $(OUTPUT)
	cp $(OUTPUT) /usr/lib
	mkdir -p /usr/include/$(PROJECT) && cp include/$(PROJECT)/* /usr/include/$(PROJECT)

$(EXTENSION): $(OUTPUT)

$(OUTPUT): $(OBJS)
	mkdir -p $(EXTENSION)
	g++ $(OBJS) -shared -o $(OUTPUT)

obj/%.o: src/%.cpp
	mkdir -p obj
	g++ $< -I include $(GPPINCS) $(GPPFLAGS) -c -fPIC -o $@


#Linux directives

PACKAGEDEV=$(PACKAGE)-dev
DEPENDSDEV=$(PACKAGE)

dev:
	mkdir -p deb/usr/include
	cp -r include/* deb/usr/include

	mkdir -p deb/DEBIAN

	cat unix/control.in | sed \
	 -e s/@PACKAGE/${PACKAGEDEV}/g \
	 -e s/@DESCRIPTION/${DESCRIPTION}/g \
	 -e s/@MAJOR/${MAJOR}/g \
	 -e s/@MINOR/${MINOR}/g \
	 -e s/@PATCH/${PATCH}/g \
	 -e s/@DEPENDS/${DEPENDSDEV}/g \
	 -e s/@SIZE/$(shell du -c --apparent-size include/* --exclude=DEBIAN | grep total | sed 's/[ \t]*total//')/g > deb/DEBIAN/control

	mkdir -p dist
	dpkg -b deb/ dist

	rm -rf deb

dist: deb

deb: $(OUTPUT)
	mkdir -p deb/usr/lib/
	cp $(OUTPUT) deb/usr/lib/

	mkdir -p deb/DEBIAN
	
	touch deb/DEBIAN/control
	cat unix/control.in | sed \
	 -e s/@PACKAGE/${PACKAGE}/g \
	 -e s/@DESCRIPTION/${DESCRIPTION}/g \
	 -e s/@MAJOR/${MAJOR}/g \
	 -e s/@MINOR/${MINOR}/g \
	 -e s/@PATCH/${PATCH}/g \
	 -e s/@DEPENDS/${DEPENDS}/g \
	 -e s/@SIZE/$(shell du -c  --exclude=DEBIAN $(EXTENSION)/* | grep total | sed 's/[ \t]*total//')/g > deb/DEBIAN/control

	mkdir -p dist
	dpkg -b deb/ dist

	rm -rf deb
