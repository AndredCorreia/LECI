L1 = [1, 3, 5, 7, 9]
#print ([10+x for x in L1])
L2 = [2, 4, 6]
print([x+y for x in L1 for y in L2])
print({x+y for x in L1 for y in L2})