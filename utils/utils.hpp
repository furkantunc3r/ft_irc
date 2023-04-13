#ifndef UTILS_HPP
#define UTILS_HPP

static std::vector<std::string> parse(std::string str, std::string delimeter)
{
	std::vector<std::string>	ret;
	std::string					buffer;
	ssize_t index;
	for (size_t i = 0; i < str.size(); i++)
	{
		buffer = str.substr(i, str.find_first_of(delimeter, i) - i + 1);
		(buffer.size() == 1 && buffer.find_first_of("\r\n\t ") != buffer.npos) ? (!buffer.erase(buffer.find_first_of("\r\n\t ")).empty()) : (i = i);
		(buffer.size() > 1 && buffer.find_first_of(delimeter) != buffer.npos) ? (!buffer.erase(buffer.find_first_of(delimeter)).empty()) : (i = i);
		if (!buffer.empty())
		{
			ret.push_back(buffer);
			i += buffer.size() - 1;
		}
	}
	
	return ret;
}


#endif
