import socket
import numpy as np

http_server = 'localhost'
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.connect((http_server, 5000))

server.send(b"GET / HTTP/1.1\r\n")
server.send(b"HOST: localhost\r\n")
server.send(b"\r\n")

from http_parser.http import HttpStream
from http_parser.reader import SocketReader

r = SocketReader(server)
p = HttpStream(r)
# print(p.headers())
body = p.body_file().read()
print(body)

open('page.html', 'wb').write(body)

from html.parser import HTMLParser


class Tags(HTMLParser):
    def handle_starttag(self, tag, attrs):
        print("Start tag:", tag)
        for attr in attrs:
            print(" attr:", attr)

    def handle_endtag(self, tag):
        print("End tag  :", tag)


class Data(HTMLParser):

    def handle_data(self, data):
        print("Data     :", data.replace('>', '', 1))


print('\n\nAll tags: ')
Tags().feed(body.decode())

print('\n\nTitle named:')

index = np.where(np.array(list(body.decode())) == '>')[0]
start = 0
for i in index:

    if 'title' in body.decode()[start:i]:
        Tags().feed(body.decode()[start:i + 1])
        Data().feed(body.decode()[start:i + 1])
    start = i
