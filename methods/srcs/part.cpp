#include "../includes/part.hpp"

Part::Part(std::map<std::string, Channel>& channels) : _channels(channels){

}

Part::~Part(){}

void Part::execute(std::vector<std::string> &args, int fd){
	std::map<std::string, Channel>::iterator it = this->_channels.find(args[1]);
	if (it != this->_channels.end() && it->second.get_fds().size() == 1)
		this->_channels.erase(it);
}