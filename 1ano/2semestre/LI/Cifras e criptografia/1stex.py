import hashlib

d= hashlib.sha1()
d.update ("Hello World!".encode("utf-8"))
print(d.hexdigest())
