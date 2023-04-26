NAME	= ircserver
CC		= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++98
SRC		= $(shell find . -type f -name "*.cpp")
OBJ		= $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) -g -O0 $(CFLAGS) $(OBJ) -o $(NAME)
clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean re
