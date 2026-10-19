// persistence_audit.cpp
#include "persistence_audit.hpp"

#include <filesystem>
#include <cstdlib>
#include <utility>
#include <vector>

std::vector<PersistenceEntry> audit_persistence_locations() {
    namespace fs = std::filesystem;
    const std::vector<std::pair<fs::path, std::string>> locations = {
        {fs::path(std::getenv("HOME") ? std::getenv("HOME") : "") /
             "Library/LaunchAgents", "user LaunchAgents directory"},
        {fs::path("/Library/LaunchAgents"), "system-wide LaunchAgents directory"},
        {fs::path("/Library/LaunchDaemons"), "system-wide LaunchDaemons directory"}
    };

    std::vector<PersistenceEntry> result;
    for (const auto& item : locations) {
        std::error_code ec;
        const bool exists = fs::exists(item.first, ec);
        result.push_back({item.first.string(), exists, item.second});
    }
    return result;
}
