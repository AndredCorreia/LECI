import pytest
import random
from fibonacci import fibonacci

def test_inferior_1():
    print ("Testa comportamento com n < 1")
    assert fibonacci(-1)== []
    assert fibonacci(0)==[0]

def test_2():
    assert fibonacci (2)== [0,1,1]
    assert fibonacci (5)==[0,1,1,2,3,5]