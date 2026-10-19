// persistence_audit.hpp
#pragma once

#include <string>
#include <vector>

struct PersistenceEntry {
    std::string path;
    bool exists{};
    std::string note;
};

std::vector<PersistenceEntry> audit_persistence_locations();
