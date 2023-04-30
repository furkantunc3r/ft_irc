#include "../includes/usercmd.hpp"
Usercmd::Usercmd(std::map<int, User> &users) : _users(users) {}

Usercmd::~Usercmd() {}

void Usercmd::execute(std::vector<std::string> &args, int fd)
{
  std::cout << ">USER TEST<\n";
  for (size_t i = 0; i < args.size(); i++)
    std::cout << "---->ARG " << i << " " << args[i] << "<----\n";

  std::map<int, User>::iterator it = this->_users.find(fd);
  std::string msg;

  if (it != this->_users.end() && this->_users.find(fd)->second._joinable != -1)
  {
    if (args.size() < 5)
    {
      it = this->_users.find(fd);
      msg.append(it->second._prefix + " 461 " + it->second._nickname + "Insufficent parameters\r\n");
      send(fd, msg.c_str(), msg.size(), 0);
      return;
    }

    if (it->second._is_regis == 1)
    {
      msg.append(it->second._prefix + " 462 " + it->second._nickname + " :You are already registered2\r\n");
      send(fd, msg.c_str(), msg.size(), 0);
      return;
    }
    it->second._fd = fd;
    it->second._username = args[1];
    it->second._realname = args[4];
    it->second._is_regis = 1;
    it->second._prefix = ":" + it->second._nickname + "!" + it->second._username + "@localhost ";
    std::cout << "------------------------ " << it->second._prefix << std::endl;
  }
}