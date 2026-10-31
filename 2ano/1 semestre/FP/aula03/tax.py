def tax(r):
    if r<=1000:
        imposto= r*0.1
        
    elif 1000<r<=2000:
        imposto= r*0.2 -100
    else:
        imposto= r*0.3 -300
    return imposto

def main():

    r= int(input("Insira o valor do produto "))
    print("A taxa que terá de pagar é de: ", tax(r))

if __name__ == '__main__':
    main()

