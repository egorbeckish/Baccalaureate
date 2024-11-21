import math
import pprint
from socket import *
import base64
from data import *
import ssl

server = socket(AF_INET, SOCK_STREAM)

server_ssl = ssl.SSLContext(ssl.PROTOCOL_TLS).wrap_socket(server, do_handshake_on_connect=False)
server_ssl.connect((POP3_SERVER, POP3_PORT))
recv = server_ssl.recv(1024)
print(recv)

server_ssl.send(f'USER {MAIL_TO}\r\n'.encode())
recv = server_ssl.recv(1024)
print(recv)

server_ssl.send(f'PASS {PASSWORD_TO}\r\n'.encode())
recv = server_ssl.recv(1024)
print(recv)

server_ssl.send(b'STAT\r\n')
all_data = server_ssl.recv(1024)
print(f'Общее кол-во данных - {all_data}')

server_ssl.send(b'LIST\r\n')
recv = server_ssl.recv(1024)
print(f'Кол-во сообщений на почте - {recv}')

data = server_ssl.recv(1024)
print(f'Данные собщений - {data}\n\n')
data = [i for i in data.decode().split('\r\n')][:4]

for i in range(1, int(all_data.decode().split(" ")[1]) + 1):

    size = data[i - 1][data[i - 1].index(' ') + 1:]
    value = data[i - 1][:data[i - 1].index(' ')]
    print(f'Данные собщения №{i} - №{value}   Размер: {size}')
    memory = round(math.log2(int(size)))
    server_ssl.send(f'RETR {i}\r\n'.encode())

    counter = 0
    while '\r\n.\r\n' != recv:

        recv = server_ssl.recv(1024).decode()
        if counter == 2:
            recv = recv.split('\n')
            index = [i for i in range(len(recv)) if 'Subject' in recv[i]]
            topic = recv[index[0]][recv[index[0]].index(':') + 1:recv[index[0]].index('\r')]
            if topic != '':
                print(f'Заголовок: {topic}')
            else:
                print(f'Заголовок: <Без темы>')

        counter += 1
        if '\r\n.\r\n' in recv: break


for i in range(1, int(all_data.decode().split(" ")[1]) + 1):
    server_ssl.send(f'DELE {i}\r\n'.encode())
    recv = server_ssl.recv(1024)
    print(recv)

server_ssl.send(b'QUIT\r\n')
recv = server_ssl.recv(1024)
print(recv)
