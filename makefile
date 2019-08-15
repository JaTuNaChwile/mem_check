CC := gcc
RM := rm -rf 

SRC  := ./src
INC  := ./include
TEST := ./test
BIN  := ./bin

debug:
	$(CC) -ggdb $(SRC)/*.c $(TEST)/*.c -I$(INC) -o $(BIN)/test.out

all:
	$(CC) $(SRC)/*.c $(TEST)/*.c -I$(INC) -o $(BIN)/test.out


clean:
	$(RM) *.o
	$(RM) $(BIN)/*.out	
	$(RM) $(BIN)/*.o	
