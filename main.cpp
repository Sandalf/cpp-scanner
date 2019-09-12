#include <cstdio>
#include <ctype.h>
#include "scanner.hpp"

using namespace std;

int main()
{
    open("test.txt");
    token t;

    do {
        t = next();

        switch (t) {
            case _id: printf("Identificador\n"); break;
            case _nat: printf("Natural\n"); break;
            case _real: printf("Real\n"); break;
            case _eof: printf("EOF\n"); break;
            case _err: printf("Error in position\n"); break;
            default: break;
        }
    } while(t != _eof && t != _err);

    close();
    return 0;
}
