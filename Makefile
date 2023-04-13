APP		= ft_irc
CC		= c++
CFLAGS	= -std=c++98
MFILES	= $(wildcard ./*.cpp ./user/srcs/*.cpp ./channel/srcs/*.cpp ./server/srcs/*.cpp)

all		:  run

run		:
	$(CC) -o $(APP) $(CFLAGS) $(MFILES)

clean	:
	@rm -rf $(APP)

re : fclean all

.PHONY: all run clean fclean re