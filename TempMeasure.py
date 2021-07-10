#-------------------------------------------------------------------------------
# Name:        module1
# Purpose:
#
# Author:      uytat
#
# Created:     06/06/2021
# Copyright:   (c) uytat 2021
# Licence:     <your licence>
#-------------------------------------------------------------------------------

# -*- coding: utf-8 -*-
import serial
import datetime


i = 0
ser = serial.Serial("COM14",9600)  # Arduinoが接続されているコムポートを指定
while(i != 10):
    todaydetail = datetime.datetime.today()
    line = ser.readline()
    line =line.decode()  # 行終端まで読み込む
    line = line.rstrip()    # 行終端コード削除
    print(line)
    #print(todaydetail.strftime("%Y/%m/%d %H:%M:%S") + " > " + line + "[C]")
    i+=1

ser.close()

print("End")