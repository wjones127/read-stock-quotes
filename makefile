CFLAGS = -O3 -std=c99 -march=native -Werror -Wall -Wextra -pedantic -fopenmp

build/test: src/converter.c
	gcc-5 $(CFLAGS) -o build/test src/converter.c src/driver.c

test: build/test
	build/test quotes.txt 1000
