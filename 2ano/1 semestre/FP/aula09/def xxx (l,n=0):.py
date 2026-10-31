def xxx (l,n=0):
    if n==0:
        return [""]
    return [a+p for a in l for p in xxx(l,n-1)]

print (xxx(["a","b","c"],2))