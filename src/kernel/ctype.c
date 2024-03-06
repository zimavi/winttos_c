#include "ctype.h"

bool islower(char chr)
{
    return chr >= 'a' && chr <= 'z';
}

char toupper(char chr)
{
    return islower(chr) ? (chr - 'a' + 'A') : chr;
}

char tolower(char chr)
{
    return islower(chr) ? chr : (chr - 'A' + 'a');
}
