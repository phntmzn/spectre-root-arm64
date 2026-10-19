// main.cpp
#include "macho_parser.hpp"
#include "persistence_audit.hpp"
#include "process_inspector.hpp"
#include "system_security.hpp"

#include <iostream>
#include <string>

static void usage(const char* exe) {
    std::cout
        << "SpectreRoot ARM64 - read-only macOS research tools\n\n"
        << "Usage:\n"
        << "  " << exe << " help\n"
        << "  " << exe << " processes\n"
        << "  " << exe << " macho <path>\n"
        << "  " << exe << " persistence\n"
        << "  " << exe << " security\n";
}

int main(int argc, char** argv) {
    if (argc < 2 || std::string(argv[1]) == "help") {
        usage(argv[0]);
        return 0;
    }

    const std::string command = argv[1];

    if (command == "processes") {
        for (const auto& process : list_processes()) {
            std::cout << process.pid << "\t" << process.name << '\n';
        }
        return 0;
    }

    if (command == "macho") {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " macho <path>\n";
            return 2;
        }
        const auto info = inspect_macho(argv[2]);
        if (!info.valid) {
            std::cerr << "Mach-O inspection failed: " << info.error << '\n';
            return 1;
        }
        std::cout << "Valid 64-bit Mach-O: yes\n"
                  << "ARM64: " << (info.is_arm64 ? "yes" : "no") << '\n'
                  << "File type: " << info.file_type << '\n'
                  << "Load commands: " << info.command_count << '\n';
        return 0;
    }

    if (command == "persistence") {
        for (const auto& entry : audit_persistence_locations()) {
            std::cout << (entry.exists ? "[present] " : "[missing] ")
                      << entry.path << " — " << entry.note << '\n';
        }
        return 0;
    }

    if (command == "security") {
        for (const auto& line : system_security_summary()) {
            std::cout << line << '\n';
        }
        return 0;
    }

    usage(argv[0]);
    return 2;
}
