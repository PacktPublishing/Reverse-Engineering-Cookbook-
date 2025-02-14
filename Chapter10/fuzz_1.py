import os
import sys


def process_input(data):
    if "crash" in data:
        raise ValueError("Fuzzing found a bug!")

    print("Received:", data)


if __name__ == "__main__":
    with open("fuzzed.txt", "r") as f:
        data = f.read().strip()
        process_input(data)
