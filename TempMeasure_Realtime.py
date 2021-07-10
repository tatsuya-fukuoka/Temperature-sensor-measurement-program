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
import numpy as np
import matplotlib.pyplot as plt
import pygame
from pygame.locals import *
import sys
import datetime

ser = serial.Serial("COM14",9600)  # Arduinoが接続されているコムポートを指定
temps = [0]*100
t = np.arange(0,100,1)
plt.ion()
pygame.init()
screen = pygame.display.set_mode((200,200))
pygame.display.set_caption("Temp")
font = pygame.font.Font(None, 50)
i=0

while True:
    screen.fill((0,0,0))
    temp = ser.readline().decode().rstrip()
    print(temp)
    text = font.render(temp + "[C°]", False, (255,255,255))
    screen.blit(text, (10,10))
    pygame.display.flip()
    t = i

    temps.pop(99)
    temps.insert(0,float(temp))

    line, = plt.plot(t, temps, 'r-',label="Temperature[C]") # Y軸更新
    line.set_ydata(temps)
    plt.title("Real-time temperature")
    plt.xlabel("Time [s]")
    plt.ylabel("Temperature [Celsius]")
    plt.legend()
    plt.grid()
    plt.xlim([1,100])
    plt.ylim([0,5])
    plt.draw()
    plt.clf()
    for event in pygame.event.get():
            # 終了ボタンが押されたら終了処理
            if event.type == QUIT:
                pygame.quit()
                ser.close()
                plt.close()
                sys.exit()
    #print(todaydetail.strftime("%Y/%m/%d %H:%M:%S") + " > " + line + "[C]")
    i=i+1

print("End")