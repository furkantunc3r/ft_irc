SRC_DIRS	:= channel/srcs irc_bots/srcs methods/srcs server/srcs user/srcs utils
INC_DIRS	:= channel/includes irc_bots/includes methods/includes server/includes user/includes utils
SRC_DIRS	+= main.cpp

vpath %.hpp $(INC_DIRS)
vpath %.cpp .:channel/srcs:irc_bots/srcs:methods/srcs:server/srcs:user/srcs:utils