#!/usr/bin/env python
# accept-myo-data.py
# Author: William Woodruff

import socket
import struct
import sys

# smartin015/MYO-python
POSES = {
0 : "rest",
1 : "fist",
2 : "waveIn",
3 : "waveOut",
4 : "fingersSpread",
5 : "reserved1",
6 : "thumbToPinky",
}

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('', int(sys.argv[1])))
sock.listen(1)
conn, addr = sock.accept()

try:
	while 1:
	    data = struct.unpack("fffffffBB", conn.recv(30))
	    motion = POSES.get(data[7], 'unknown')
	    if not data: break
	    print motion
except Exception, e:
	pass
finally:
	conn.close()
	sock.close()



