// process_inspector.cpp
#include "process_inspector.hpp"

#include <algorithm>
#include <cstring>

#ifdef __APPLE__
#include <libproc.h>
#include <sys/proc.h>
#include <unistd.h>
#endif

std::vector<ProcessInfo> list_processes() {
    std::vector<ProcessInfo> result;
#ifdef __APPLE__
    const int count = proc_listpids(PROC_ALL_PIDS, 0, nullptr, 0);
    if (count <= 0) return result;

    std::vector<pid_t> pids(static_cast<std::size_t>(count) / sizeof(pid_t) + 16);
    const int bytes = proc_listpids(PROC_ALL_PIDS, 0, pids.data(),
                                    static_cast<int>(pids.size() * sizeof(pid_t)));
    if (bytes <= 0) return result;

    const std::size_t used = static_cast<std::size_t>(bytes) / sizeof(pid_t);
    for (std::size_t i = 0; i < used; ++i) {
        if (pids[i] <= 0) continue;
        char name[PROC_PIDPATHINFO_MAXSIZE] = {};
        const int name_bytes = proc_name(pids[i], name, sizeof(name));
        std::string process_name = name_bytes > 0 ? name : "(name unavailable)";
        result.push_back({static_cast<int>(pids[i]), process_name});
    }
    std::sort(result.begin(), result.end(),
              [](const ProcessInfo& a, const ProcessInfo& b) {
                  return a.pid < b.pid;
              });
#endif
    return result;
}
