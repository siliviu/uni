#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int _fin, _in_loc;
char _in_buff[4096];


void read_init(const char* nume) {
    _fin = open(nume, O_RDONLY);
    _in_loc = 4095;
}

char read_ch() {
    ++_in_loc;
    if (_in_loc == 4096) {
        _in_loc = 0;
        read(_fin, _in_buff, 4096 * sizeof(char));
    }
    return _in_buff[_in_loc];
}

int read_u32() {
    int u32 = 0; char c;
    while (!isdigit(c = read_ch()));
    u32 = c - '0';
    while (isdigit(c = read_ch()))
        u32 = u32 * 10 + c - '0';
    return u32;
}

int _fout, _out_loc; char _out_buff[50000];

void write_init(const char* name) {
    _fout = open(name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    _out_loc = 0;
}

void write_ch(char ch) {
    if (_out_loc == 50000) {
        write(_fout, _out_buff, 50000 * sizeof(char));
        _out_loc = 0;
        _out_buff[_out_loc++] = ch;
    }
    else {
        _out_buff[_out_loc++] = ch;
    }
}

void write_u32(unsigned int vu32) {
    if (vu32 <= 9) {
        write_ch(vu32 + '0');
    }
    else {
        write_u32(vu32 / 10);
        write_ch(vu32 % 10 + '0');
    }
}

void write_close() {
    write(_fout, _out_buff, _out_loc * sizeof(char));
    close(_fout);
}

int sort(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int main() {
    read_init("sortare.in");
    int n = read_u32();
    int* a = (int*)malloc(n * sizeof(int));
    for (int i = 0;i < n;++i)
        a[i] = read_u32();
    close(_fin);
    qsort(a, n, sizeof(int), sort);
    write_init("sortare.out");
    for (int i = 0;i < n;++i) {
        write_u32(a[i]);
        write_ch(' ');
    }
    free(a);
    write_close();
}