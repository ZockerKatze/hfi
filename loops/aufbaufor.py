import pyfiglet
from time import sleep

for i in range(1,11):
    istr = str(i)
    f = pyfiglet.figlet_format(istr)
    sleep(1) ## schläft zwischen jeden print
    print(f)
