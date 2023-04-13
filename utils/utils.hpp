#ifndef UTILS_HPP
#define UTILS_HPP

#include <sys/socket.h>
#include "../channel/includes/channel.hpp"

static std::vector<std::string> parse(std::string str, std::string delimeter)
{
	std::vector<std::string>	ret;
	std::string					buffer;
	ssize_t index;
	for (size_t i = 0; i < str.size(); i++)
	{
		buffer = str.substr(i, str.find_first_of(delimeter, i) - i + 1);
		(buffer.size() == 1 && buffer.find_first_of("\r\n") != buffer.npos) ? (!buffer.erase(buffer.find_first_of("\r\n\t ")).empty()) : (i = i);
		(buffer.size() > 1 && buffer.find_first_of(delimeter) != buffer.npos) ? (!buffer.erase(buffer.find_first_of(delimeter)).empty()) : (i = i);
		if (!buffer.empty())
		{
			ret.push_back(buffer);
			i += buffer.size() - 1;
		}
	}
	
	return ret;
}

static bool does_exist_channel(std::vector<Channel> channels, std::string channel_name, int fd){

	if (channel_name[0] != '#')
	{
		std::cerr << "Channel name has to start with #" << std::endl;
		send(fd, "Channel name has to start with #\r\n", 34, 0);
		return false;
	}
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (!strncmp(channels[i].get_name().c_str(), channel_name.c_str(), channels[i].get_name().size()))
			return false;
	}
	return true;
}

static inline std::string trim(std::string& str, char delimeter)
{
    str.erase(str.find_last_not_of(delimeter)+1);
    str.erase(0, str.find_first_not_of(delimeter));
    return str;
}
#endif
