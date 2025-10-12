#ifndef GENERAL_DEFINES_H
#define GENERAL_DEFINES_H

void PUT32 ( unsigned int, unsigned int ); // defined in assembly code
unsigned int GET32 ( unsigned int ); // defined in assembly code

void write_masked(unsigned int reg, unsigned int value, unsigned int mask);

#endif // !GENERAL_DEFINES_H
