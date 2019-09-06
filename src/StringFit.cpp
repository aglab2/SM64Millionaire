#include "StringFit.hpp"
#include "GfxTable.h"

static float symlen(const char *text)
{
    float symlen = 0;
    for (; *text != '\0' && *text != '\n'; text++)
    {
        int sym = *text;
        symlen += LetterSizes[sym];
    }
    return symlen;
}

static void clear(char *str)
{
    for (; *str != '\0'; str++)
    {
        if (*str == '\n')
            *str = ' ';
    }
}

static char *symchrClosest(char *str, int chr, float len)
{
    float curLen = 0;
    char *prev = nullptr;
    float prevLen = -1;
    for (; *str != '\0'; str++)
    {
        int sym = *str;
        curLen += LetterSizes[sym];
        if (*str == chr)
        {
            if (curLen >= len)
                break;

            prev = str;
            prevLen = len;
        }
    }

    if (*str == '\0')
        return prev;

    if (!prev)
        return str;

    if (len - prevLen <= curLen - len)
        return prev;
    else
        return str;
}

// pretty unoptimal but whatever
static bool split(char *str, int maxSplits)
{
    clear(str);
    if (maxSplits == 0)
        return false;

    if (maxSplits == 1)
        return true;

    float partSize = (symlen(str) - (maxSplits - 1) * LetterSizes[' ']) / maxSplits;

    int i;
    for (i = 1; i < maxSplits; i++)
    {
        char* cand = symchrClosest(str, ' ', partSize * i);
        if (!cand)
            break;
        
        *cand = '\n';
    }

    if (i != maxSplits)
        return false;

    return true;
}

static float findmax(float* arr, int size, int* idx = nullptr)
{
    float curopt = arr[0];
    if (idx) *idx = 0;

    for (int i = 1; i < size; i++)
    {
        if (curopt < arr[i])
        {
            if (idx) *idx = i;
            curopt = arr[i];
        }
    }

    return curopt;
}

constexpr int MaxLineCount = 4;

float StringFit::Fit(char *str)
{
    // scales are shifted by 1, so line1 correspond to idx 0
    float scales[MaxLineCount];

    float splitLens[MaxLineCount];
    for (int i = 1; i <= MaxLineCount; i++)
    {
        if (!split(str, i))
        {
            scales[i - 1] = -1;
            continue;
        }
        // Fill in splitLens
        {
            float* curlen = splitLens;

            *curlen = 0;
            for (char* cursym = str; *cursym != '\0'; cursym++)
            {
                if (*cursym != '\n')
                {
                    int sym = *cursym;
                    *curlen += LetterSizes[sym];
                }
                else
                {
                    curlen++;
                    *curlen = 0;
                }
            }
        }

        float scaleX = BoxWidth  / findmax(splitLens, i);
        float scaleY = BoxHeight / (i * SymbolHeight);
        scales[i - 1] = scaleX < scaleY ? scaleX : scaleY;
    }
    int lines = 0;
    float scale = findmax(scales, MaxLineCount, &lines);
    split(str, lines + 1);
    return scale;
}

float StringFit::GetOptScale(char* str)
{
    int lines = 0;
    for (char* cursym = str; *cursym != '\0'; cursym++)
    {
        if (*cursym == '\n')
        {
            lines++;
        }
    }
    
    float maxLen = 0;
    {
        float curlen = 0;
        for (char* cursym = str; *cursym != '\0'; cursym++)
        {
            if (*cursym != '\n')
            {
                int sym = *cursym;
                curlen += LetterSizes[sym];
            }
            else
            {
                if (curlen > maxLen)
                    maxLen = curlen;

                curlen = 0;
            }
        }
        if (curlen > maxLen)
            maxLen = curlen;
    }

    float scaleX = BoxWidth  / maxLen;
    float scaleY = BoxHeight / (lines * SymbolHeight);
    return scaleX < scaleY ? scaleX : scaleY; 
}