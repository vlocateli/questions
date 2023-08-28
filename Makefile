.PHONY: all
FILES =  src/main.c src/vector.c include/vector.h include/types.h 
C_FLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -O2 -march=native -fsanitize=address,undefined -ggdb
all: exercicio1

exercicio1: $(FILES)
	$(CC) $(C_FLAGS) src/*.c -o $@


.PHONY: clean

clean:
	$(RM) exercicio1 *.out 

