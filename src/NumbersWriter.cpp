#include "NumbersWriter.h"

void NumbersWriter::Step()
{
    for (int i = 0; i < 4; i++)
    {
        char str[] = "A %d";
        str[0] += i;
        PrintInt(20, 80 - 20 * i, str, Vars[i]);
    }
}

int NumbersWriter::Behavior[] = {
    0x08000000,
    0x0C000000, (int) sStep,
    0x09000000,    
};