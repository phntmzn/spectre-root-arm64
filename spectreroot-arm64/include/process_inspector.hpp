// process_inspector.hpp
#pragma once

#include <string>
#include <vector>

struct ProcessInfo {
    int pid{};
    std::string name;
};

std::vector<ProcessInfo> list_processes();
