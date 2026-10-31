L = ["Mario", "Carla","anabela", "Maria", "nuno"]
print(sorted(L))
print(sorted(L, reverse=True))
print(sorted(L, key=len))

L[0].casefold()
print(str.casefold(L[0]))
print(sorted(L, key=str.casefold))
def lenFold(s):
    return (len(s), s.casefold())
print(lenFold(L[0]))