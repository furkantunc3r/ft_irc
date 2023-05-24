#ifndef IMETHOD_HPP
#define IMETHOD_HPP

#include <iostream>
#include <cstring>
#include <vector>
#include "../../utils/utils.hpp"

class IMethod
{
	public:
		virtual ~IMethod(){};
		virtual void execute(std::vector<std::string> &arg, int fd) = 0;
};

#endif