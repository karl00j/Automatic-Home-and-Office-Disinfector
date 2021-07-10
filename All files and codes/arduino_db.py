import mysql.connector
import datetime
import time
import serial


def passedVal(c,pop):
    currentTime = datetime.datetime.now()
    dyt = '{}/{}/{}'.format(currentTime.month, currentTime.day, currentTime.year)
    tym = '{}:{}:{}'.format(currentTime.hour, currentTime.minute, currentTime.second)
    mycursor.execute('INSERT INTO disinfection_info'
                     '(number, number_of_visitors, date, time) '
                     'VALUES(%s, %s, %s, %s)', (c, pop, dyt, tym))
    mydb.commit()
    print('number: ', c)
    print('number_of_visitors: ', pop)
    print('date: ', dyt)
    print('time: ', tym)


mydb = mysql.connector.connect(
    host='localhost',
    user='root',
    passwd='passwd123',
    database='automatichomeandofficedisinfector'
)

mycursor = mydb.cursor()

mycursor.execute('CREATE TABLE IF NOT EXISTS disinfection_info'
                 '(number INT(10), number_of_visitors INT(10), '
                 'date VARCHAR(255), time VARCHAR(255))')

read = serial.Serial('COM1',9600,timeout=0.1)
time.sleep(2)
c = 0
while True:
    arduino = read.readline()
    if arduino:
        val = arduino.decode()
        pop = int(val)
        c += 1
        passedVal(c, pop)

read.close()
