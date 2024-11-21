import socket

client = socket.socket()
client.connect(('127.0.0.1', 12345))

while True:

    msg = input('Enter message for server: ')
    client.send(msg.encode())
    if msg == 'exit':
        print('You disconnect of the server...')
        break

    size = input('Enter size message which return: ')
    client.send(size.encode())

    msg = client.recv(1024).decode()
    print(f'\n\nServer return your:\n{msg}\n\n')