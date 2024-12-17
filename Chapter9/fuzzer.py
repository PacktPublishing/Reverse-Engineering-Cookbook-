#!/usr/bin/env python3

import subprocess
import sys
import os
import shutil

# List of payloads to test for format string vulnerabilities
payloads = [
    "%s", "%x", "%p", "%n",
    "%s%s%s%s", "%x%x%x%x", "%p%p%p%p", "%n%n%n%n",
    "%.100x", "%.100s", "%#100x", "%100n",
    "%10s", "%-10s", "%10x", "%-10x",  # Width and alignment
    "%.5s", "%.5x", "%.10p", "%.10n",  # Precision control
    "%s%x%n%p", "%x%s%x%n",  # Mixed types
    "%0x", "%.-10x", "%-10n",  # Edge cases
    "%4000x", "%s%4000x",  # Memory fill
    "%q", "%z",  # Invalid format specifiers
    "%s%s%s%s%s%s", "%x%x%x%x%x%x",  # Nested and extended sequences
    "%s\x00%s", "%n\x00%n",  # Embedded null bytes
    "%s%s%s%p%x%x%x%n%n%n%n",  # Combination with potential crashers
    "%9999999n",  # Large payloads to test for crashes
]


def get_crash_dump_directory():
    try:
        with open("/proc/sys/kernel/core_pattern", "r") as f:
            pattern = f.read().strip()
            directory = os.path.dirname(pattern)
        return directory
    except Exception as e:
        print(f"Error: {e}")
        return None


def copy_crashed_file(program_path, core_dump_dir, payload):
    core_files = sorted(os.listdir(core_dump_dir), key=lambda f: os.path.getmtime(
        os.path.join(core_dump_dir, f)))
    if core_files:
        core_file = core_files[-1]
        old_path = os.path.join(core_dump_dir, core_file)
        new_name = "paylod-" + payload.replace('%', '_') + ".core"
        print(old_path, new_name)
        new_path = os.path.join(core_dump_dir, new_name)

        shutil.move(old_path, new_path)
        print(f"Core dump saved as: {new_path}")


def fuzz_program(program_path, crash_dump_folder):
    try:
        for payload in payloads:
            print(
                "\n--------------------------------------------------------------------")
            print(f"Testing payload: {payload}")

            # Start the target program as a subprocess
            process = subprocess.Popen(
                [program_path],
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE
            )

            # Send the payload to the program
            stdout, stderr = process.communicate(input=payload.encode())

            # Capture the program's output
            output = stdout.decode(errors="ignore") + \
                stderr.decode(errors="ignore")

            output = output.lower()
            output = output.strip()
            print(output)

            return_code = process.returncode
            if return_code < 0:
                signal = -return_code
                print(f"Program crashed with signal {signal}"
                      " (e.g., SIGSEGV or SIGABRT)")
                print(f"Program crashed with exit code {return_code}, " +
                      "indicating a potential DoS attack")
                copy_crashed_file(program_path, crash_dump_folder, payload)
                continue

            # Check for signs of a vulnerability
            if "segmentation fault" in output or "core dumped" in output:
                print(f"Vulnerability found with payload: {payload}")
                continue

            elif any(marker in output for marker in ["0x", "(null)", "(nil)", "0"]):
                print(f"Potential leak detected with payload: {payload}")
    except Exception as e:
        print(f"Error during fuzzing: {e}")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python fuzzer.py <program_path>")
        sys.exit(1)

    crash_dump_folder = get_crash_dump_directory()
    print("Crash Dump Directory:", crash_dump_folder)

    program_path = sys.argv[1]
    fuzz_program(program_path, crash_dump_folder)
