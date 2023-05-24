#ifndef MODE_HPP
#define MODE_HPP

#include "imethod.hpp"
#include "../../server/includes/server.hpp"

class Mode : public IMethod
{
    private:
        Server& _server;
    public:
        Mode(Server& server);
        ~Mode();
        void execute(std::vector<std::string> &args, int fd);
};

#endif