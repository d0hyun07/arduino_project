from flask import *
import websocket
import time

app = Flask(__name__)
onOff = "on"
num_state = '1'

@app.route("/",methods=["GET"])
def index():
  if request.method == "GET":
    print(onOff)
    return render_template("index.html",state = onOff)
  
@app.route("/state",methods=["POST"])
def state():
  if request.method == "POST":
    global num_state
    ws = websocket.WebSocket()
    ws.connect ("ws://10.150.151.142/")

    onOff = request.form["onOff"]
    ws.send(num_state)
    result = ws.recv()
    print (result)

    ws.close()
  if onOff == "on":
    onOff = "off"
    num_state = '0'
  elif onOff == "off":
    onOff = "on"
    num_state = '1'

  return render_template("index.html",state = onOff)
if __name__ == '__main__':
  app.run(port=3000,debug=True)
