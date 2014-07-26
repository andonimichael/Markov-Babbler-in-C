# Andoni Garcia's Markov Babbler. 2014.

.PHONY: clean

SRC = messages.c debug.c infastructure.c insert.c babble.c main.c

markov: markov.h $(SRC)
	gcc -Wall -o markov $(SRC) -lm

text: test.c
	gcc -Wall -o textconv test.c

clean:
	rm -rf markov
