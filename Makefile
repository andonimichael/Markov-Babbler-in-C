# Andoni Garcia's Markov Babbler. 2014.

.PHONY: clean

SRC = infastructure.c insert.c babble.c main.c

markov: markov.h $(SRC)
	gcc -Wall -o markov $(SRC) -lm

text: convert_text.c
	gcc -Wall -o convert_text convert_text.c

clean:
	rm -rf markov
