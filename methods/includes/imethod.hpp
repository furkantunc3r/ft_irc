#ifndef IMETHOD_HPP
#define IMETHOD_HPP

#include <iostream>
#include <cstring>
#include <vector>

class IMethod
{
	public:
		virtual ~IMethod(){};
		virtual void do_method(std::vector<std::string> arg, int _role) = 0;
};

#endif