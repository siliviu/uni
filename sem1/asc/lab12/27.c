// #pragma comment(lib, "legacy_stdio_definitions.lib")
// #pragma comment(lib, "legacy_stdio_wide_specifiers.lib")
// #pragma comment(linker, "/INCLUDE:_printf,_fopen,_fscanf,_fclose")
#include <stdio.h>

int* read(int* s);
int* construct(int* s, int l, int* n, int* p);
void print(int* a, int l);

int s[100], n[100], p[100], ls, ln, lp;
void* imports[] = {printf,fscanf,fopen,fclose };

int main() {
    ls = read(s) - s;
    lp = construct(s, ls, n, p) - p;
    ln = ls - lp;
    print(p, lp);
    print(n, ln);
    exit(0);
}
