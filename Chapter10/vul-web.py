from flask import Flask, request, render_template_string

app = Flask(__name__)

# Homepage


@app.route("/")
def home():
    return "<h1>Welcome to the Vulnerable App</h1>"

# Search function (used for fuzzing)


@app.route("/search")
def search():
    query = request.args.get("q", "")
    return f"<p>Search results for: {query}</p>"

# Login form (for SQL Injection testing)


@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form.get("username", "")
        password = request.form.get("password", "")
        # Simulating SQL Injection vulnerability
        if username == "admin" and password == "' OR 1=1 --":
            return "<h2>Login Successful</h2>"
        return "<h2>Invalid Credentials</h2>"

    return render_template_string('''
        <form method="POST">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

# CSRF Protection Test


@app.route("/transfer", methods=["POST"])
def transfer():
    csrf_token = request.form.get("csrf_token", "")
    if csrf_token != "securetoken":
        return "<h2>CSRF Protection Triggered</h2>"
    return "<h2>Money Transferred!</h2>"

# File Upload (for bypass testing)


@app.route("/upload", methods=["POST"])
def upload():
    file = request.files.get("file")
    if file:
        return f"<h2>Uploaded file: {file.filename}</h2>"
    return "<h2>No file uploaded</h2>"


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=9090)
