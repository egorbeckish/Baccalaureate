from socket import *
import base64
import ssl
from data import *

server = socket(AF_INET, SOCK_STREAM)
server.connect((MAIL_SERVER, MAIL_PORT))


server.send(b'EHLO host\r\n')
recv = server.recv(1024)
print(recv)


server.send(b'STARTTLS\r\n')
recv = server.recv(1024)
print(recv)

recv = server.recv(1024)
print(recv)

server_ssl = ssl.SSLContext(ssl.PROTOCOL_TLS).wrap_socket(server)
server_ssl.send(b'EHLO host\r\n')
recv = server_ssl.recv(1024)
print(recv)

account = base64.b64encode(LOGIN_USER.encode())
password = base64.b64encode(PASSWORD_USER.encode())


server_ssl.send(b'AUTH LOGIN\r\n')
recv = server_ssl.recv(1024)
print(recv)

server_ssl.send(account + '\r\n'.encode())
recv = server_ssl.recv(1024)
print(recv)

server_ssl.send(password + '\r\n'.encode())
recv = server_ssl.recv(1024)
print(recv)


server_ssl.send(f"MAIL FROM: <{LOGIN_USER}>\r\n".encode())
recv = server_ssl.recv(1024)
print(recv)

server_ssl.send(f"RCPT TO: <{MAIL_TO}>\r\n".encode())
recv = server_ssl.recv(1024)
print(recv)

server_ssl.send(b'DATA\r\n')
recv = server_ssl.recv(1024)
print(recv)

topic = input('Введитие заголовок: ')
msg = input('Введите сообщение: ') + '.\r\n'
# topic = '123'
# msg = open('f.txt', encoding='utf-8').read() + '.\r\n'
# msg = '123'
server_ssl.send(f'Subject:{topic}\n\n{msg}'.encode())

msg_end = b'\r\n.\r\n'
server_ssl.send(msg_end)
recv = server_ssl.recv(1024)
print(recv)

server_ssl.send(b'QUIT\r\n')
recv = server_ssl.recv(1024)
print(recv)

server_ssl.close()
server.close()
print('Завершено.')