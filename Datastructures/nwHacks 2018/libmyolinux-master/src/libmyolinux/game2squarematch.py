#!/usr/bin/env python

#Example game using input from Thalmic Myo

import pygame
import random
import sys
import os
import tempfile
import subprocess
import thread
import socket
import struct

from random import randrange
from sys import stdin

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GREEN = ( 0, 255, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)

PI = 3.1415

#---Main Program Loop---
def game():
    POSES = {
    0 : "rest",
    1 : "fist",
    2 : "waveIn",
    3 : "waveOut",
    4 : "fingersSpread",
    5 : "reserved1",
    6 : "thumbToPinky",
    }

    # initialize socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('', 6970))
    sock.listen(1)
    conn, addr = sock.accept()

    global last_pose
    pygame.init()

    size = (350, 250)
    screen = pygame.display.set_mode(size)
    pygame.display.set_caption("Myo Linux Driver Demo")

    x_coord = 0
    y_coord = 0
    height = 50
    width = 50

    r_hw = randrange(50, 100)
    r_x_coord = randrange(0, 250)
    r_y_coord = randrange(0, 350)
    r_height = r_hw
    r_width = r_hw
    
    x_speed = 0
    y_speed = 0
    out_speed = 0
    
    done = False
    pressed = False
    correct = False

    clock = pygame.time.Clock()

    while not done:
        try:
            while 1:
                data = struct.unpack("fffffffBB", conn.recv(30))
                motion = POSES.get(data[7], 'unknown')
                if not data: break
                print motion
                if motion == "waveOut": # right
                    x_speed = 10
                if motion == "waveIn": # down
                    y_speed = 10
                if motion == "rest": # stop
                    x_speed = 0
                    out_speed = 0
                if motion == "thumbToPinky": #reset
                    x_coord = 0
                    y_coord = 0
                    height = 50
                    width = 50
                if motion == "fingersSpread": # grow
                    out_speed = 10

                #Clear Screen
                screen.fill(WHITE)
                
                # random rect
                pygame.draw.rect(screen, GREEN, [r_x_coord, r_y_coord, r_width, r_height])
               
                # check for match
                if x_coord == r_x_coord and y_coord == r_y_coord and height == r_height and width == r_width:
                    r_hw = randrange(50, 100)
                    r_x_coord = randrange(0, 250)
                    r_y_coord = randrange(0, 350)
                    r_height = r_hw
                    r_width = r_hw

                # Move the object according to the speed vector
                x_coord += x_speed
                y_coord += y_speed

                height += out_speed
                width += out_speed
                              

                pygame.draw.rect(screen, BLUE, [x_coord, y_coord, width, height])
                #update screen
                pygame.display.flip()

                #limit to 60 frames per second
                clock.tick(60)
        except Exception, e:
            pass
        finally:
            conn.close()
            sock.close()
    pygame.quit()

def main():
    game() 

if __name__ == "__main__":
    main()
