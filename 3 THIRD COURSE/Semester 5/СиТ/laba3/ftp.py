import socket
import time

from typing import List

from data import *


def _send(cmd):
    time.sleep(0.1)
    server.send(cmd)
    print(cmd[:-2].decode('utf-8'))
    buf = server.recv(1024)
    print(buf.decode('utf-8'))
    if buf[3] == ord("-"):
        res = buf[0:3].decode('utf-8')
        while (True):
            buf = server.recv(1024)
            print(buf.decode('utf-8'))
            if (buf[0:3].decode() == res):
                break
    # Если требуется продолжение действий (читать rfc по кодам ответов ftp)
    if (buf[0] == ord("1")):
        buf = server.recv(1024)
        print(buf.decode('utf-8'))
    return buf[:-2].decode('utf-8')


# def _send(text: bytes) -> bytes:
#     server.send(text)
#     answer = server.recv(1024)
#     if answer[0] == ord("1"):
#         print(answer)
#         return server.recv(1024)
#     return answer


def location(ip: bytes) -> List[str]:

    port = list(map(int, ip.decode().split('(')[1].replace(')', '', 1).split(',')[4:]))
    port = port[0] * 256 + port[1]
    ip = '.'.join(ip.decode().split('(')[1].replace(')', '', 1).split(',')[0:4])
    return [ip, port]


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.connect((URL_SERVER, PORT))
recv = server.recv(1024)
print(recv)

print(_send(CMD_USER))
print(_send(CMD_PASS))
ip = _send(CMD_PASV)
print(ip)
print(server.recv(1024))


# # port = list(map(int, ip.decode().split('(')[1].replace(')', '', 1).split(',')[4:]))
# # port = port[0] * 256 + port[1]
# # ip = '.'.join(ip.decode().split('(')[1].replace(')', '', 1).split(',')[0:4])
# ip, port = location(ip)
# print(f'\nIP: {ip}\nPORT: {port}')
#
# server2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# server2.connect((ip, port))
#
# print(_send(CMD_LIST))
# recv = server2.recv(1024)
# print(recv.decode())

# print(_send(CMD_CWD + b' /pure-ftpd/misc/GEMA/GEMA\r\n'))
# print(_send(CMD_PWD))
#
# ip = _send(CMD_PASV)
# print(ip.decode())
#
# # port = list(map(int, ip.decode().split('(')[1].replace(')', '', 1).split(',')[4:]))
# # port = port[0] * 256 + port[1]
# # ip = '.'.join(ip.decode().split('(')[1].replace(')', '', 1).split(',')[0:4])
# ip, port = location(ip)
# print(f'\nIP: {ip}\nPORT: {port}')
#
# server2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# server2.connect((ip, port))
# print(_send(CMD_LIST))
# recv = server2.recv(1024 * 2)
# print(recv.decode())
#
# ip = _send(CMD_PASV)
# print(ip.decode())
#
# # port = list(map(int, ip.decode().split('(')[1].replace(')', '', 1).split(',')[4:]))
# # port = port[0] * 256 + port[1]
# # ip = '.'.join(ip.decode().split('(')[1].replace(')', '', 1).split(',')[0:4])
# ip, port = location(ip)
# print(f'\nIP: {ip}\nPORT: {port}')
#
# server2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# server2.connect((ip, port))
# print(_send(CMD_RETR).decode())
# open('text.txt', 'wb').write(server2.recv(2048))
#
# # ip = _send(CMD_PASV)
# # print(ip.decode())
# #
# # port = list(map(int, ip.decode().split('(')[1].replace(')', '', 1).split(',')[4:]))
# # port = port[0] * 256 + port[1]
# # ip = '.'.join(ip.decode().split('(')[1].replace(')', '', 1).split(',')[0:4])
# # print(f'\nIP: {ip}\nPORT: {port}')
# #
# # server2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# # server2.connect((ip, port))
# #
# # with open('text.txt', 'rb') as file:
# #     print(file.read())
