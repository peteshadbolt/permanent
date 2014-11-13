
// Count the number of set bits in a binary string
int countbits(unsigned int n) 
{
    int q=n;
    q = (q & 0x5555555555555555) + ((q & 0xAAAAAAAAAAAAAAAA) >> 1);
    q = (q & 0x3333333333333333) + ((q & 0xCCCCCCCCCCCCCCCC) >> 2);
    q = (q & 0x0F0F0F0F0F0F0F0F) + ((q & 0xF0F0F0F0F0F0F0F0) >> 4);
    q = (q & 0x00FF00FF00FF00FF) + ((q & 0xFF00FF00FF00FF00) >> 8);
    q = (q & 0x0000FFFF0000FFFF) + ((q & 0xFFFF0000FFFF0000) >> 16);
    q = (q & 0x00000000FFFFFFFF) + ((q & 0xFFFFFFFF00000000) >> 32); // This last & isn't strictly qecessary.
    return q;
}

int bitparity (unsigned int n) { return 1 - (countbits(n) & 1)*2; }

