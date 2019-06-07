PROJECT=var
DESCRIPTION="Dynamically typed variables for C++"
DEPENDS=g++

MAJOR=0
MINOR=8
PATCH=1

GPPINCS=
GPPLIBS=
GPPFLAGS=-std=c++11 -Wall -Werror -pedantic -g
CC=g++

OBJS= \
obj/var.o \

BINARY=lib$(PROJECT)

TARGET=so
ifeq ($(TARGET), dll)
CC=i686-w64-mingw32-g++
endif

PACKAGE=lib$(PROJECT)
OUTPUT=$(TARGET)/$(PACKAGE).$(TARGET)

.PHONY: all deb so dll clean

#General purpouse
all: $(OUTPUT)

clean:
	rm -rf dist so dll obj

$(TARGET): $(OUTPUT)

$(OUTPUT): $(OBJS)
	mkdir -p $(TARGET)
	$(CC) $(OBJS) -shared -o $(OUTPUT)

obj/%.o: src/%.cpp include/$(PROJECT)/%.hpp
	mkdir -p obj
	$(CC) $< -I include $(GPPINCS) $(GPPFLAGS) -c -fPIC -o $@


#Linux directives

PACKAGEDEV=$(PACKAGE)-dev
DEPENDSDEV="$(PACKAGEDEV), $(DEPENDS)"

dist: deb dev

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
	 -e s/@SIZE/$(shell du -c --apparent-size so/* --exclude=DEBIAN | grep total | sed 's/[ \t]*total//')/g > deb/DEBIAN/control

	mkdir -p dist
	dpkg -b deb/ dist

	rm -rf deb
