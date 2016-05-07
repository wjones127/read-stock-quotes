CFLAGS = -O3 -std=c99 -march=native -Werror -Wall -Wextra -pedantic -fopenmp -g
VECFLAGS = -ftree-vectorizer-verbose=2 -fopt-info-vec-missed

build/test: src/converter.c
	gcc-5 $(CFLAGS) -o build/test src/converter.c src/driver.c

test: build/test
	build/test quotes.txt 1000
