// macho_parser.cpp
#include "macho_parser.hpp"

#include <fstream>
#include <cstring>
#include <iterator>
#include <vector>

#ifdef __APPLE__
#include <mach-o/loader.h>
#include <mach/machine.h>
#endif

MachOInfo inspect_macho(const std::string& path) {
    MachOInfo result;
    std::ifstream input(path, std::ios::binary);
    if (!input) {
        result.error = "cannot open file";
        return result;
    }

    std::vector<unsigned char> bytes((std::istreambuf_iterator<char>(input)),
                                     std::istreambuf_iterator<char>());
    if (bytes.size() < 4) {
        result.error = "file is too small";
        return result;
    }

#ifdef __APPLE__
    if (bytes.size() < sizeof(mach_header_64)) {
        result.error = "file is too small for a 64-bit Mach-O header";
        return result;
    }

    std::uint32_t magic = 0;
    for (int i = 0; i < 4; ++i) magic |= static_cast<std::uint32_t>(bytes[i]) << (8 * i);

    if (magic != MH_MAGIC_64 && magic != MH_CIGAM_64) {
        result.error = "not a supported thin 64-bit Mach-O file (fat binaries are not parsed)";
        return result;
    }

    mach_header_64 header{};
    std::memcpy(&header, bytes.data(), sizeof(header));
    const std::uint64_t commands_end =
        static_cast<std::uint64_t>(sizeof(mach_header_64)) + header.sizeofcmds;
    if (commands_end > bytes.size()) {
        result.error = "load-command region extends beyond end of file";
        return result;
    }

    result.valid = true;
    result.is_64_bit = true;
    result.is_arm64 = (header.cputype == CPU_TYPE_ARM64);
    result.file_type = header.filetype;
    result.command_count = header.ncmds;
#else
    result.error = "Mach-O inspection is supported only on macOS";
#endif
    return result;
}
