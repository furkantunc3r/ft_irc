#ifndef PART_HPP
#define PART_HPP

#include "imethod.hpp"
#include "../../channel/includes/channel.hpp"

class Part : public IMethod{
	private:
		std::map<std::string, Channel>&	_channels;
	public:
		Part(std::map<std::string, Channel>& channels);
		~Part();
		void execute(std::vector<std::string> &arg, int fd);
};

#endif