from subprocess import Popen
from subprocess import PIPE

proc = Popen ("comando a executar ",stdout=PIPE, shell=True)


return_code =proc.wait()
output = proc.stdout.read().decode("utf-8")