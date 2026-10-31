# Complete the code to make the HiLo game.

import random

def playHiLo():
    # Pick a random number between 1 and 100, inclusive
    secret = random.randrange(1, 101);

    guess= int(input("I picked a number between 1 and 100. Can you guess it? "))
    # put your code here
    ...
    
    while guess != secret:
        if guess>secret:
            print ("High! ")
        else: 
            print ("Low")
        guess= (int (input("Try again! ")))

    print ("Congratulations, you have made it! ")


playHiLo()

