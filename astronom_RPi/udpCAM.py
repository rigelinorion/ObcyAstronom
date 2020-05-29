# Web streaming example
# Source code from the official PiCamera package
# http://picamera.readthedocs.io/en/latest/recipes2.html#web-streaming

import io
import picamera
import logging
import socketserver
from threading import Condition
from http import server
import threading
import time
import socket
# import libc
from ctypes import cdll
libc = cdll.LoadLibrary("libc.so.6")
sscanf = libc.sscanf
#libc = CDLL("libc.so.6")  # alternative

# allocate vars
#i = c_int()
#f = c_float()
#s = create_string_buffer(b'\000' * 32)
# parse with sscanf
#libc.sscanf(b"1 3.14 Hello", "%d %f %s", byref(i), byref(f), s)
# read the parsed values
#i.value  # 1
#f.value  # 3.14
#s.value # b'Hello'

PAGE="""\
<html>
<body>
<center><img src="stream.mjpg" width="800" height="600"></center>
</body>
</html>
"""

class StreamingOutput(object):
    def __init__(self):
        self.frame = None
        self.buffer = io.BytesIO()
        self.condition = Condition()

    def write(self, buf):
        if buf.startswith(b'\xff\xd8'):
            # New frame, copy the existing buffer's content and notify all
            # clients it's available
            self.buffer.truncate()
            with self.condition:
                self.frame = self.buffer.getvalue()
                self.condition.notify_all()
            self.buffer.seek(0)
        return self.buffer.write(buf)

class StreamingHandler(server.BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            self.send_response(301)
            self.send_header('Location', '/index.html')
            self.end_headers()
        elif self.path == '/index.html':
            content = PAGE.encode('utf-8')
            self.send_response(200)
            self.send_header('Content-Type', 'text/html')
            self.send_header('Content-Length', len(content))
            self.end_headers()
            self.wfile.write(content)
        elif self.path == '/stream.mjpg':
            self.send_response(200)
            self.send_header('Age', 0)
            self.send_header('Cache-Control', 'no-cache, private')
            self.send_header('Pragma', 'no-cache')
            self.send_header('Content-Type', 'multipart/x-mixed-replace; boundary=FRAME')
            self.end_headers()
            try:
                while True:
                    with output.condition:
                        output.condition.wait()
                        frame = output.frame
                    self.wfile.write(b'--FRAME\r\n')
                    self.send_header('Content-Type', 'image/jpeg')
                    self.send_header('Content-Length', len(frame))
                    self.end_headers()
                    self.wfile.write(frame)
                    self.wfile.write(b'\r\n')
            except Exception as e:
                logging.warning(
                    'Removed streaming client %s: %s',
                    self.client_address, str(e))
        else:
            self.send_error(404)
            self.end_headers()

class StreamingServer(socketserver.ThreadingMixIn, server.HTTPServer):
    allow_reuse_address = True
    daemon_threads = True


def previev():
    with picamera.PiCamera(resolution='800x600', framerate=24) as camera:
        output = StreamingOutput()
        #Uncomment the next line to change your Pi's Camera rotation (in degrees)
        #camera.rotation = 90
        camera.start_recording(output, format='mjpeg')
        try:
            address = ('', 8000)
            server = StreamingServer(address, StreamingHandler)
            server.serve_forever()
        finally:
            camera.stop_recording()


def onmessage(msg):
    if char(msg[0]) == "P":
        global tpreview
        tpreview = threading.Thread(target=previev).start()
    if char(msg[0]) == "p":
        tpreview.kill()

UDP_IP_ADDRESS = "127.0.0.1"
UDP_PORT_NO = 11111
tpreview = 0

def main():
    serverSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)   
    serverSock.bind((UDP_IP_ADDRESS, UDP_PORT_NO))
    while True:
        data, addr = serverSock.recvfrom(1024)
        print ("Message: ", data)
        onmessage(data)

if __name__ == '__main__':
    main()