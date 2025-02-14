import os
import sys


def process_input(data):
    """
    if "guzzing" in data.lower():
        raise ValueError("Fuzzing found a bug!")
    """

    print(f"Received: {data}")
    sys.stdout.flush()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 fuzz-1.py <filename>")
        sys.exit(1)

    filename = sys.argv[1]
    with open(filename, "r") as f:
        line = f.read()
        process_input(line)
