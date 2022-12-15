TARGET = my_mastermind
OBJ = $(SRC: .c = .o)
SRC = my_mastermind.c

all : $(TARGET)

$(TARGET) : $(OBJ)
	gcc $(CFLAGS) -o $(TARGET) $(OBJ) 

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)
	
re: fclean all
