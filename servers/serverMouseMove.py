#----------------------------------------------------------------------
# VMouse - OpenCV Virtual Mouse (HCI)
# Copyright (C) 2014  Kunal Dawn <kunal.dawn@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#----------------------------------------------------------------------
#!/usr/bin/python
from socket import *
import subprocess

localAddr = ('localhost', 8888)
sock = socket(AF_INET, SOCK_STREAM)
sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
sock.bind(localAddr)
sock.listen(5)
data = ""
while 1:
    (client, address) =  sock.accept()
    print 'CONNECTED TO : ', address
    while 1:
        data = client.recv(1024)
        if not len(data):
            break
        values = data.split(",")
        print 'MOVE X[',values[0],'], Y[',values[1],']'
	subprocess.call(["xdotool", "mousemove", values[0], values[1]])

