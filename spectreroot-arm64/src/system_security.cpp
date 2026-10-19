// system_security.cpp
#include "system_security.hpp"

#include <string>
#include <vector>

#ifdef __APPLE__
#include <sys/utsname.h>
#endif

std::vector<std::string> system_security_summary() {
    std::vector<std::string> lines;
#ifdef __APPLE__
    struct utsname info {};
    if (uname(&info) == 0) {
        lines.push_back(std::string("System: ") + info.sysname);
        lines.push_back(std::string("Kernel release: ") + info.release);
        lines.push_back(std::string("Machine architecture: ") + info.machine);
    } else {
        lines.push_back("System information unavailable.");
    }
    lines.push_back("SIP status: not queried by this tool; check with: csrutil status");
    lines.push_back("Gatekeeper status: not queried by this tool; check with: spctl --status");
#else
    lines.push_back("This system summary is designed for macOS.");
#endif
    return lines;
}
