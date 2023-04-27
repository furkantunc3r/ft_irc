include Path.mk
NAME		= ircserver
CC			= c++
CFLAGS		= -Wall -Werror -Wextra -std=c++98
SRC			= $(shell find $(SRC_DIRS) -name '*.cpp')
OBJ_DIR		= obj/
OBJ			= $(patsubst %, $(OBJ_DIR)%, $(notdir $(SRC:%.cpp=%.o)))
INC			= $(shell find $(INC_DIRS) -name '*.hpp')

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:%.cpp %.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME) $(OBJ_DIR)

re : fclean all

print: 
	@echo $(OBJ)
	@echo "\n-------------\n"
	@echo $(SRC)
	@echo "\n-------------\n"
	@echo $(INC)

.PHONY : all clean re
