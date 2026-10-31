def Intersects (a,b,c,d):
    assert a<b
    assert c<d

    if c>a and c<b or a>c and a<d:
        return True
    else:
        return False
    
def main():
    print (Intersects (1,5,3,7))
    print (Intersects (1, 3, 4, 6))
    print (Intersects (1, 5, 0, 2))
    print (Intersects (2, 6, 6, 8))
    print (Intersects (0, 4, 2, 3))
    print (Intersects (3, 5, 1, 4))
    print (Intersects (0, 2, 2, 4))


main()