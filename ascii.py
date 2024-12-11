import pyfiglet
from time import sleep

for i in range(0,11):
    istr = str(i)
    fig = pyfiglet.figlet_format(istr,font="basic")
    sleep(0.5)
    print(fig)
