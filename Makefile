CC=g++
FLAGS=-Wall -Werror -Wextra -std=c++20 -pedantic -ggdb

%/main: %/main.cpp xe
	$(CC) $(FLAGS) -o $@ $< 

%/main2: %/main2.cpp xe
	$(CC) $(FLAGS) -o $@ $<

.PHONY: clean xe %/test

clean:
	rm -f */main */main2 */output.txt */output2.txt

xe:
	set -xe

%/output.txt: %/main %/sample.txt
	./$^ > $@

%/test: %/output.txt %/expected.txt
	./test.sh $^

%/output2.txt: %/main2 %/sample.txt
	./$^ > $@

%/test2: %/output2.txt %/expected2.txt
	./test.sh $^
