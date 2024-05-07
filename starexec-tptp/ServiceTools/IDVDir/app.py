from flask import Flask, render_template, request
import json
app = Flask(__name__)

import requests


@app.route('/')
def form():
    return render_template("index.html")



@app.route('/idv', methods=["POST"])
def idv():
    try:
        proof = request.files["proof"].read().decode("utf-8")
    except Exception as e:
        proof = request.form["proof"]

    try:
        interpretation = request.form['interpretation']
    except Exception as e:
        interpretation = "false"

    return render_template("idv.html", proof_string=proof, interpretation=interpretation)


@app.route('/interestingness', methods=["POST"])
def interestingness():
    data = json.loads(request.data.decode("utf-8"))
    proof = data["proof"]

    # Ask TSTP for interestingness...
    args = {
        "ProblemSource": "FORMULAE",
        "FORMULAEProblem": proof,
        "SolutionFormat": "TPTP",
        
        "QuietFlag": "-q01",
        "SubmitButton": "ProcessSolution",
        
        "System___AGInTRater---0.0": "AGInTRater---0.0",
        "TimeLimit___AGInTRater---0.0": "60",
        "Transform___AGInTRater---0.0": "none",
        "Format___AGInTRater---0.0": "tptp:raw",
        "Command___AGInTRater---0.0": "AGInTRater -c %s"
    }
    response = requests.post("http://localhost/cgi-bin/SystemOnTPTPFormReply", args)
    text = response.text
    begin = text.index("<PRE>") + 5
    end = text.index("</PRE>")
    text = text[begin:end]

    # send back the response to be parsed on the client side.
    return text
    




if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
