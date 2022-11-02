from datetime import *

a = input()

a = datetime.strptime(a, "%d/%m/%Y").date()
b = date.today()
print((b - a).days)
