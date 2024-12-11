import pyfiglet

herbert = 10 ##int (ganzzahl)
sascha = 7.6969420 ## float (was eine kommazahl ist)
jeremias = "Jeremias"

print(f"int: {herbert}, float: {sascha}, str: {jeremias}")
print("addition")
elias = herbert+sascha ## int+float
print(f"float + int = {elias}")
eliasstr = str(elias)
print(eliasstr + jeremias)
ln = "-"*20
print(ln)
f=pyfiglet.figlet_format(eliasstr)
print(f)
