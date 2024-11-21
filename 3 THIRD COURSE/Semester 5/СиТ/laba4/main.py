import socket
import struct


def sniff_icmp_packets():
    icmp = socket.getprotobyname('icmp')
    sniffer = socket.socket(socket.AF_INET, socket.SOCK_RAW, icmp)
    sniffer.bind(('0.0.0.0', 0))
    sniffer.setsockopt(socket.IPPROTO_IP, socket.IP_HDRINCL, 1)
    sniffer.ioctl(socket.SIO_RCVALL, socket.RCVALL_ON)
    try:
        while True:
            raw_data, addr = sniffer.recvfrom(65535)
            ip_header = raw_data[:20]
            iph = struct.unpack('!BBHHHBBH4s4s', ip_header)
            version_ihl = iph[0]
            version = version_ihl >> 4
            ihl = version_ihl & 0xF
            iph_length = ihl * 4
            ttl = iph[5]
            protocol = iph[6]
            s_addr = socket.inet_ntoa(iph[8])
            d_addr = socket.inet_ntoa(iph[9])
            if protocol == 1:
                icmp_header = raw_data[iph_length:iph_length + 8]
                icmph = struct.unpack('!BBH', icmp_header)
                icmp_type = icmph[0]
                icmp_code = icmph[1]
                print(f"ICMP Type: {icmp_type}, ICMP Code: {icmp_code}")
    except KeyboardInterrupt:
        sniffer.ioctl(socket.SIO_RCVALL, socket.RCVALL_OFF)


sniff_icmp_packets()