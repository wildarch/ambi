from SimpleWebSocketServer import SimpleWebSocketServer, WebSocket

class Data():
    def __init__(self):
        alerts = {
            'temperature': False,
            'oxygen': True,
            'humidity': False,
            'light': False,
            'noise': False
        }
        progress = 50
        expression = 'happy' # or sad, tired, stressed, drinking

    def to_json(self):
        return json.dumps({
            'alerts': self.alerts,
            'progress': self.progress,
            'expression': self.expression
        })


class AmbiServer(WebSocket):

    def __init__(self):
        self.store = Data()

    def handleMessage(self):
        # echo message back to client
        self.sendMessage(self.data)

    def handleConnected(self):
        print(self.address, 'connected')
        self.sendMessage(self.store)

    def handleClose(self):
        print(self.address, 'closed')

server = SimpleWebSocketServer('localhost', 8888, AmbiServer)
server.serveforever()
