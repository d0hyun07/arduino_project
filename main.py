from flask import * # flask 프레임워크 import (웹서버)
import websocket # websocket 모듈 import (아두이노 서버와 통신을 위해서..)

app = Flask(__name__)
onOff = "on" # 웹사이트에 보여지는 상태값 on off
num_state = '1' # 실제 아두이노 서버에 보내지는 상태값 1 = on 0 = off

@app.route("/",methods=["GET"]) # root 경로 접속
def index():
  if request.method == "GET": # get 메소드로 접속
    return render_template("index.html",state = onOff) # index.html로 state값 출력
  
@app.route("/state",methods=["POST"])
def state():
  if request.method == "POST": # post로 보냈을 때
    global num_state
    ws = websocket.WebSocket() 
    ws.connect ("ws://10.150.151.142/") # 아두이노 서버 연결

    onOff = request.form["onOff"] # 사용자가 입력한 버튼 값 (state)
<<<<<<< HEAD
    ws.send(num_state) # state 값 전송
=======
    ws.send(num_state) state 값 전송
>>>>>>> 04a4daf4846f20f4975202702ae0bb1871711df0
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
<<<<<<< HEAD
  app.run(port=3000,debug=True) # port 번호 3000
=======
  app.run(port=3000,debug=True) # port 번호 3000
>>>>>>> 04a4daf4846f20f4975202702ae0bb1871711df0
