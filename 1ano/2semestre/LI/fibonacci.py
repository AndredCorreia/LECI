def fibonacci(n):
    n= int(n)
    res=[]
    if n<0:
        return res
    
    elif n==0 :
        res=[0]
        return res
    else :
        res=[0,1]
        for i in range (2,n+1):
            res.append(res[i-2]+res[i-1])
        return res

n='a'
n= input ("Insira um número!   ")

while n.isdigit()==False or (int (n)<0):
    n= input ("Resposta inválida! Insira um número!   ")

print(fibonacci(n))

            
            