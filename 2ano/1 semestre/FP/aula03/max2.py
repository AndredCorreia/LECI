def max2(num1,num2):
    max_value = num1
    if max_value<num2:
        max_value=num2
    return max_value

def max3(max_value,num3):
    if int(max_value)<num3:
        max_value=num3

    return max_value

def main():
    num1= (int(input ("Introduza o primeiro número: ")))
    num2= (int(input ("Introduza o segundo número: ")))
    

    print("O número maior é o número ", max2(num1,num2),"!")

    num3= int(input("Insira agora um terceiro número: "))
    print("O número maior dos três números dados (", num1,",",num2,",",num3,") é o número", max3(max2(num1,num2),num3),"!")

if __name__=='__main__':
    main()

