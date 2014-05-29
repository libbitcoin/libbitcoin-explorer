#include "command_line.hpp"

int main(int argc, char* argv[])
{
    return invoke(argc, const_cast<const char**>(argv));
}