include Path.mk
NAME		= ircserver
CC			= c++
CFLAGS		= -Wall -Werror -Wextra -std=c++98
SRC			= $(shell find $(SRC_DIRS) -name '*.cpp')
OBJ_DIR		= obj/
OBJ			= $(patsubst %, $(OBJ_DIR)%, $(notdir $(SRC:%.cpp=%.o)))

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)main.o: main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME) $(OBJ_DIR)

re : fclean all

print: 
	@echo "\n------OBJ-------\n"
	@echo $(OBJ)
	@echo "\n------SRC-------\n"
	@echo $(SRC)
	@echo "\n------INC-------\n"
	@echo $(INC)

.PHONY : all clean re
