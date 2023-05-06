import time
import serial
import serial.tools.list_ports as qw

#mostrar timepo en formato mm/dd/yy hh:mm:ss

#getting all arduin connected via serial ports
ports=[]
for a in qw.comports():
    print(a.description)
    # if 'ttyUSB' in a.device or 'ttyACM' in a.device: #para sistemas UNIX/LINUX
    if 'USB Serial Device' in a.description:# para sistemas windows
        ports.append(a.device)

print(ports)

ard=[] #arduino com ports
for a in ports:
    ard.append(serial.Serial(a))

with open('logging.csv','a') as file:
    file.writelines(['COM arduino',',','tiempo',',','data','\n'])
    while True: #cambiar condicion si necesario, ahorita corre infinitamente
        t=time.strftime("%D %H:%M:%S",time.localtime())
        for a in ard:
            print([t,a.readline().decode('utf-8')])
            file.writelines([a.name,',',t,',',a.readline().decode('utf-8'),'\n'])
file.close()