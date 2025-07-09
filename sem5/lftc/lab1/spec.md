Elemente lexicale:

-   Operatori: `+`, `-`, `*`, `/`, `%`,
    `<`, `>`, `=`, `==`, `!=`, `<=`, `>=`,
    `<<`, `>>`
-   Delimitatori & separatori: `,`, `;`, `:`, `{`, `}`, `(`, `)`
-   Cuvinte rezervate: `#`, `include`, `<iostream>`, `using`, `namespace`, `std`, `int`, `double`, `if`, `while`, `return`, `cin`, `cout`, `struct`, `switch`, `case`, `break`

Identificatori:

```
ID = caracter | caracter {caracter} {cifra}
CONST = int | double
caracter =  'a' | 'b' | ... | 'z' |
            'A' | 'B' | ...  | 'Z'
cifra_nenula = '1' | '2' | ... | '9'
cifra = '0' | cifra_nenula
int = cifra_nenula {cifra} | '0'
double = int ['.' {cifra}]
```

Specificare limbaj (EBNF):

```
program = incl ns fct.
incl = "#" "include" "<iostream>".
ns = "using" "namespace" "std".
fct = tipf ID ([tip ID]) ic.
tip = "int" | "double" | "char".
tipf = tip | "double" | "void".
ic = "{" li "}".
li = instr | instr li.
instr = atr | decl | op | instr_cond | instr_cicl | instr_switch | decl_struct | return.
decl = tip ID ";".
op = atr | intrare | iesire;
atr = ID "=" expr ";".
intrare = "cin" ">>" ID ";".
iesire = "cout" "<<" expr ";".
expr = ID | CONST |
                expr ("+"|"-"|"*"|"/"|"%") expr |
                "+" expr | "-" expr.
instr_cond = "if" "(" cond ")" ic.
instr_cicl = "while" "(" cond ")" ic.
cond = expr ("<" | "<=" | "==" | ">=" | ">" | "!=")  expr.
decl_struct = "struct" ID "{" {decl} "}" ";".
instr_switch = "switch" "(" + expr + ")" "{"
 {"case" expr ":" li "break" ";"}
"}".
return = "return" expr ";".
```
