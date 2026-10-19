// test_macho_parser.cpp
#include "macho_parser.hpp"

#include <cassert>
#include <fstream>
#include <string>

int main() {
    const std::string missing = "spectreroot_test_file_that_does_not_exist";
    const auto result = inspect_macho(missing);
    assert(!result.valid);
    assert(!result.error.empty());

    const std::string tiny = "spectreroot_test_tiny.bin";
    {
        std::ofstream file(tiny, std::ios::binary);
        file << "abc";
    }
    const auto tiny_result = inspect_macho(tiny);
    assert(!tiny_result.valid);
    std::remove(tiny.c_str());
    return 0;
}
