// macho_parser.hpp
#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct MachOInfo {
    bool valid{false};
    bool is_64_bit{false};
    bool is_arm64{false};
    std::uint32_t file_type{};
    std::uint32_t command_count{};
    std::string error;
};

MachOInfo inspect_macho(const std::string& path);
