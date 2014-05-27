#ifndef SX_MAIN_HPP
#define SX_MAIN_HPP

// main return codes
const int main_success = 0;
const int main_failure = -1;

// TODO: consider template or pure virtual base (interface).
namespace wallet {
bool invoke(const int argc, const char* argv[]);
bool display_usage();
}

#endif