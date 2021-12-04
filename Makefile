CC=g++
FLAGS=-Wall -Werror -Wextra -std=c++20 -pedantic -ggdb

%/main: %/main.cpp xe
	$(CC) $(FLAGS) -o $@ $< 

%/main2: %/main2.cpp xe
	$(CC) $(FLAGS) -o $@ $<

.PHONY: clean xe

clean:
	rm -f */main */main2

xe:
	set -xe
