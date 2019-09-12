#ifndef scanner_hpp
#define scanner_hpp

typedef enum { _id, _nat, _real, _eof, _err } token;

extern void open(const char *fname);
extern void cose();
extern token next();

void close();
void success();
void fallback();
void fail();

#endif