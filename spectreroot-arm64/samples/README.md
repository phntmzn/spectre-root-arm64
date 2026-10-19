# Samples

Place only files you own or are authorized to analyze here. Prefer small, non-sensitive test fixtures.

The Mach-O parser currently handles thin 64-bit Mach-O files and reports whether the CPU type is ARM64. It does not parse universal/fat binaries, execute samples, or determine whether a file is malicious.

For a harmless local test on macOS, try:

```bash
./build/spectreroot macho /usr/bin/true
```
