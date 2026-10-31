import hashlib

a= hashlib.sha1()
a.update("A long sentence broken in two halves".encode ("utf-8"))
print(a.hexdigest())
