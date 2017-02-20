EXES = solar_system test_offreader ppmtest
CC = gcc
CFLAGS=-O3 -std=c99
GLLDFLAGS =-lGL -lglut -lGLU
LDFLAGS =-lm

all: $(EXES)

solar_system: solar_system.c utils.c ppm.o offreader.o jmesh.o rotater.o
	$(CC) $(CFLAGS) -I/usr/include -o $@ $^ $(LDFLAGS) $(GLLDFLAGS)

test_offreader: test_offreader.c jmesh.o offreader.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

jmesh.o: jmesh.c jmesh.h
	$(CC) $(CFLAGS) -c $<

offreader.o: offreader.c offreader.h
	$(CC) $(CFLAGS) -c $< 

ppmtest: ppm_test.c ppm.o
	$(CC) $(CFLAGS) -o $@ $^

ppm.o: ppm.c ppm.h
	$(CC) $(CFLAGS) -c $<

rotater.o: rotater.c rotater.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o *.gch $(EXES)
