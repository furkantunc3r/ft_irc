#ifndef WHOIS_HPP
#define WHOIS_HPP

#include "imethod.hpp"

class Whois : public IMethod{

	public:
		Whois();
		~Whois();
		void do_method(std::vector<std::string> &arg, int _role);
};

#endif