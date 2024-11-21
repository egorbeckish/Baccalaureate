import socket, string


def _split(string: str, delim: int) -> str:

    if delim is not None and len(string) <= delim:
        print('Return full string')
        return string + f' (hash: {hash(string)}'

    if delim is None:
        print('Return full string')
        return string

    return '\n'.join([f'message - {i} (hash: ' + str({string[i:i + delim]: hash(string[i:i + delim]) for i in range(0, len(string), delim)}[i]) + ')' for i in {string[i:i + delim]: hash(string[i:i + delim]) for i in range(0, len(string), delim)}])


server = socket.socket()
server.bind(('127.0.0.1', 12345))
server.listen()

connect, addr = server.accept()
print(connect, addr)
while True:

    print('Wait enter to the client...\n\n')
    msg = ''.join([i for i in connect.recv(1024).decode() if i in string.printable])
    print(f'Client send: {msg}')

    if msg == 'exit':
        print('Client disconnect of the server...')

    size_split = int(''.join([i for i in connect.recv(3).decode() if i in string.digits]))
    print(f'Client asked to return the offers in size: {size_split}\n')

    answer = _split(msg, size_split)
    print(f'Return client his:\n{answer}\n\n')
    connect.send(answer.encode())

server.close()

