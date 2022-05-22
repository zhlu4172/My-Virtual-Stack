CC=gcc
CFLAGS=-lm -fsanitize=address -Wvla -Wall -Werror -g -std=gnu11 -lasan


vm_x2017: vm_x2017.c
	$(CC) $(CFLAGS) $^ -o $@

objdump_x2017: objdump_x2017.c
	$(CC) $(CFLAGS) $^ -o $@
	

tests: objdump_x2017
	bash test.sh

run_tests:
	echo "run_tests"

clean:
	rm objdump_x2017




