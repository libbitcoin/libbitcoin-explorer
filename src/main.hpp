#ifndef SX_MAIN_HPP
#define SX_MAIN_HPP

// main return codes
const int main_success = 0;
const int main_failure = -1;

namespace wallet {
bool invoke(const int argc, const char* argv[]);
bool display_usage();
}

#endif