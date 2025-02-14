from boofuzz import *

target_ip = "127.0.0.1"
target_port = 21

# Create Boofuzz Session
session = Session(
    target=Target(
        connection=SocketConnection(target_ip, target_port, proto="tcp")
    )
)

# FTP authentication phase (Fuzzing is optional)
s_initialize("FTP USER")
s_string("USER", fuzzable=False)
s_delim(" ", fuzzable=False)
s_string("anonymous")  # Fuzzing can be performed here
s_static("\r\n")

s_initialize("FTP PASS")
s_string("PASS", fuzzable=False)
s_delim(" ", fuzzable=False)
s_string("password")  # Fuzzing can be performed here
s_static("\r\n")

# FTP command fuzzing (Fuzzing the LIST command)
s_initialize("FTP LIST")
s_string("LIST", fuzzable=False)
s_delim(" ", fuzzable=False)
# Fuzzing is performed here, which may lead to a directory traversal vulnerability.
s_string("/AAA")
s_static("\r\n")

# Connecting the FTP session
session.connect(s_get("FTP USER"))  # Connect first command
session.connect(s_get("FTP PASS"), s_get("FTP USER"))  # Authenticate
session.connect(s_get("FTP LIST"), s_get("FTP PASS"))  # Execute LIST command

# Start Fuzzing
session.fuzz()
