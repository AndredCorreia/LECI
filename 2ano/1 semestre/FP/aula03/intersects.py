def intersects(a,b,c,d):
    if a<=d and b>=c:
        return True
    else:
        return False
    
def main():
    a= int(input("Insira um número: "))
    b= int(input("Insira um número: "))
    c= int(input("Insira um número: "))
    d= int(input("Insira um número: "))
    print (intersects(a,b,c,d))


if __name__ == '__main__':
    main()