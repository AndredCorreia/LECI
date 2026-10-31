# Complete the code to make the HiLo game.

import random

def playHiLo():
    # Pick a random number between 1 and 100, inclusive
    secret = random.randrange(1, 101);

    guess= int (input("I picked a number between 1 and 100. Can you guess it? "))
    # put your code here
    tentativas=1
    if secret==guess:
        print("Congrats! You got it right at the first attempt! ")
    
    else:
        while guess!=secret:
            tentativas+=1
            if guess>secret:
                print("Your number is too high!")
                guess=  int(input("Try again! " ))
            else:
                print("Your guess is too low!")
                guess= int(input("Try again! "))

        print ("Congrats! You got it right at the ", tentativas,"º attempt!")
    


playHiLo()

