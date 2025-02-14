from flask import Flask, request, jsonify

app = Flask(__name__)


@app.route('/api/test', methods=['POST'])
def test_endpoint():
    data = request.form.get('input', '')
    print(f"Received input: {data}")

    if len(data) > 1000:
        return jsonify({"error": "Input too long"}), 400
    if any(c in data for c in ['<', '>', '"', "'"]):
        return jsonify({"error": "Potential XSS detected"}), 400

    return jsonify({"status": "success", "received": data}), 200


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5000, debug=True)
