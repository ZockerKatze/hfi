from time import sleep
import pyfiglet

## while

affe = True
ct=0
while affe == True:
    try:
        ct+=1 ## der zähler welcher inc. wird um1 jeden durchlauf
        ctst = str(ct)  # convertiert int in str
        f=pyfiglet.figlet_format("Leck meine Eier: "+ctst) #legt f fest
        print(f) #printet f
        sleep(0.5)  # halbe sek pause
    except KeyboardInterrupt: ## bei strg c aus dem programm geht
        print("\nwird verlassen")
        break
