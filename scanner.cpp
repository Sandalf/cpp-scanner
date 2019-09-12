#include <cstdio>
#include <ctype.h>
#include "scanner.hpp"

FILE *file;
long q;
const int udef = -1;

void open(const char *fname) {
    file = fopen(fname, "r");
    q = 0;
}

void close() {
    fclose(file);
}

char read() {
    return fgetc(file);
}

void success() {
    q = ftell(file);
}

void fallback() {
    fseek(file, -1, SEEK_CUR);
}

void fail() {
    fseek(file, q, SEEK_SET);
}

bool isnatural(char c) {
    switch (c) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        return true;
        break;
    }

    return false;
}

bool id() {
    int actual = 0;
    int prior = 0;

    while(actual != udef) {
        prior = actual;
        char c = read();

        switch (actual) {
            case 0:
                if(isalpha(c)) actual = 2;
                else if (c == '_') actual = 1;
                else actual = udef;
                break;
            case 1:
                if(isdigit(c) || c == '_');
                else if(isalpha(c)) actual = 2;
                else actual = udef;
            case 2:
                if(isalnum(c) || c == '_');
                else actual = udef;
            default:
                break;
        }
    }

    if (prior == 2) {
        fallback();
        success();
        return true;
    }

    fail();
    return false;
}

token num() {
    int actual = 0;
    int prior = 0;

    while(actual != udef) {
        if (actual == udef) {
        }

        prior = actual;
        char c = read();

        switch (actual) {
            case 0:
                if(isnatural(c)) actual = 1;
                else if (c == '0') actual = 2;
                else actual = udef;
                break;
            case 1:
                if(isdigit(c));
                else if (c == '.') actual = 3;
                else actual = udef;
                break;
            case 2:
                if(isdigit(c) || c == '_') actual = 4;
                else if (c == '.') actual = 3;
                else actual = udef;
                break;
            case 3:
                if(isdigit(c)) actual = 5;
                else actual = udef;
                break;
            case 4:
                if(isdigit(c));
                else if (c == '.') actual = 3;
                else actual = udef;
                break;
            case 5:
                if(isdigit(5));
                else actual = udef;
                break;
        }
    }

    if (prior == 1 || prior == 2 || prior == 5) {        
        fallback();
        success();
        return prior == 1 || prior == 2 ? _nat : _real;
    }

    fail();
    return _err;
}

bool wsp() {
    while(isspace(read()));

    fallback();
    success();

    return true;
}

bool eof() {
    if (read() == EOF) {
        fallback();
        return true;
    }

    fallback();
    return false;
}

token next() {
    wsp();

    if (id()) return _id;

    token tnum = num();
    if (tnum != _err) return tnum;

    if (eof()) return _eof;
    
    return _err;
}
