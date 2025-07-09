```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 4, b = 5;
    int s;
    s = a + b;
    return 0;
}
```

EBNF:

```
program = incl ns fct.
incl = "#" "include" "<" "iostream" ">".
ns = "using" "namespace" "std".
fct = tipf ID ([tip ID{,tip ID}]) ic.
tip = "int" | "char".
tipf = tip | "void".
ic = "{" li "}".
li = instr | instr li.
instr = adecl | decl | atr | return.
adecl = tip la";".
la - ID "=" expr {"," ID "=" expr}.
decl = tip ID ";".
atr = ID "=" expr ";".
expr = ID | CONST | expr "+" expr.
return = "return" expr ";".
```