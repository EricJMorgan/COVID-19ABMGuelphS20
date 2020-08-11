#
import random
from collections import deque

def start_X():
    X = deque()
    X.append(1)
    return X

def start_Y():
    Y = deque()
    Y.append(1)
    return Y

def get_X(value):
    return value + 1

def get_Y(value):
    return value + 0.1

def get_randomY(value):
    return value + (value * random.uniform(-0.1,0.1))
    