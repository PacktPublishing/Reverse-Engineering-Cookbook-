from fuzzingbook.Fuzzer import RandomFuzzer
from fuzzingbook.GrammarFuzzer import GrammarFuzzer
import requests
import logging

logging.basicConfig(filename='fuzzing.log', level=logging.INFO)


def log_fuzz_results(data, response):
    logging.info(
        f"Sent: {data}, Received: {response.status_code}, Response: {response.text}")


def fuzz_target(url):
    fuzzer = RandomFuzzer(min_length=5, max_length=20,
                          char_start=32, char_range=94)
    for _ in range(100):
        fuzz_input = fuzzer.fuzz()
        response = requests.post(url, data={'input': fuzz_input})
        log_fuzz_results(fuzz_input, response)
        print(f"Sent: {fuzz_input}, Received: {response.status_code}")


grammar = {
    "<start>": ["<username>:<password>"],
    "<username>": ["admin", "guest", "user", "test"],
    "<password>": ["password", "1234", "letmein", "secret", "<special_char><digits>"],
    "<special_char>": ["!", "@", "#", "$", "%", "^", "&", "*"],
    "<digits>": ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]
}


def grammar_fuzz_target(url):
    """
    This function performs fuzzing using a structured grammar-based approach.
    Instead of generating completely random inputs, it ensures that the inputs follow a predefined format.

    The grammar used here models a username-password input pair, which allows the fuzzer to test how the target application handles structured data.

    This approach is particularly useful for testing applications that require specific input formats, such as command parsers, web APIs, and protocols.
    """
    fuzzer = GrammarFuzzer(grammar)
    for _ in range(50):
        fuzz_input = fuzzer.fuzz()
        response = requests.post(url, data={'input': fuzz_input})
        log_fuzz_results(fuzz_input, response)
        print(f"Sent: {fuzz_input}, Received: {response.status_code}")


def edge_case_fuzz_target(url):
    edge_cases = [
        "",  # Empty input
        "A" * 5000,  # Long input
        "!@#$%^&*()",  # Special characters
        "\n\r\t",  # Whitespace characters
    ]

    for fuzz_input in edge_cases:
        response = requests.post(url, data={'input': fuzz_input})
        log_fuzz_results(fuzz_input, response)
        print(f"Sent: {fuzz_input}, Received: {response.status_code}")


url = 'http://127.0.0.1:5000/api/test'
fuzz_target(url)
grammar_fuzz_target(url)
edge_case_fuzz_target(url)
