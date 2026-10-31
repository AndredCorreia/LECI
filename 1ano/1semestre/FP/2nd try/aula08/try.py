L1 = [1, 3, 5, 7, 9]
#print ([10+x for x in L1])
L2 = [2, 4, 6]
#print([x+y for x in L1 for y in L2])
#print({x+y for x in L1 for y in L2})
#print([(x,y) for x in L1 for y in L2])
#print([(x,y) for y in L2 for x in L1])
#print([x*c for c in "abc" for x in L1])
#print([x%3==0 for x in L1])
#print([(x,x//3) for x in L1 if x%3==0])
#print({x:x//3 for x in L1 if x%3==0})
#print([(x,y) for x in L1 for y in L2 if x<y])
#print({ x:[y for y in L2 if x<y] for x in L1 })
print(any(x%2==0 for x in L1))