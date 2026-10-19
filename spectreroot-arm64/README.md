# SpectreRoot ARM64

A macOS security-research and forensics toolkit scaffold for Apple Silicon. It focuses on read-only process inspection, Mach-O file analysis, LaunchAgent/LaunchDaemon auditing, and reporting.

> **Compatibility note:** This project is a research scaffold, not a kernel rootkit. It does not implement stealth, persistence installation, privilege escalation, code injection, or kernel-memory modification. Compatibility with any future macOS release (including a release referred to as macOS 27) must be verified on the actual target OS.

## Features

- List running processes using `libproc`.
- Parse basic 64-bit Mach-O headers and load commands from files.
- Audit common LaunchAgent and LaunchDaemon directories without modifying them.
- Print a basic system security overview.
- Optional Python helper for analyzing JSON reports.

## Requirements

- macOS with Xcode Command Line Tools.
- CMake 3.20 or newer.
- A C++17 compiler.
- Python 3.10+ for the Python helper and Python tests.

Install or verify command-line tools:

```bash
xcode-select --install
clang++ --version
cmake --version
python3 --version
```

Install CMake separately if it is not available, for example through the official installer at https://cmake.org/download/.

## Build

Run these commands from the repository root:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The executable will be at `build/spectreroot`.

## Run

```bash
# Show available commands
./build/spectreroot help

# List visible processes
./build/spectreroot processes

# Inspect a Mach-O executable
./build/spectreroot macho /usr/bin/true

# Audit common persistence locations (read-only)
./build/spectreroot persistence

# Display a basic system security overview
./build/spectreroot security
```

Some process details and system settings may be restricted by macOS permissions. The tool intentionally does not attempt to bypass those restrictions.

## Python helper

Run the analyzer against a JSON file containing an array of report objects:

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -e .
python -m spectreroot.analyzer report.json
```

The helper can also be run directly from the source tree:

```bash
PYTHONPATH=python python3 -m spectreroot.analyzer report.json
```

## Tests

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure

python3 -m unittest discover -s tests -p 'test_*.py'
```

## Scope and safety

This project is intended for defensive inspection of systems you own or are authorized to assess. Auditing is read-only. It does not disable SIP, change system security settings, load kernel extensions, inject code, or modify persistence entries.

## License

MIT. See `LICENSE`.
