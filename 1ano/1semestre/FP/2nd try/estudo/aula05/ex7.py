numero=input("Introduza um numero: ")


def isPalindrome(numero):
    j=len(numero)-1
    for i in range (0, len(numero)):
        if numero[i]!=numero[j]:
            return False
        else:
            if j==0:
                return True
            
            else:
                j-=1










print(isPalindrome(numero))