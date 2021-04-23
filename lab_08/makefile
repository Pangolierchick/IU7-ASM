CC = clang
CF = -Wall

SRC_DIR = ./src
OBJ_DIR = ./obj

main.out: $(OBJ_DIR)/main.o $(OBJ_DIR)/__memmove.o
	$(CC) $^ -o $@

$(OBJ_DIR)/__memmove.o: $(SRC_DIR)/__memmove.asm
	nasm -f macho64 $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CF) $< -c -o $@

clean:
	rm -rf obj
	rm -rf main.out
