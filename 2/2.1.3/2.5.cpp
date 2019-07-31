// a) char, wchar_t, char[2]. wchar_t[2]
// the former two are single characters. the latter two are arrays
// containing two characters ('a'/L'a' and the null character).
//
// the first and the third use narrow characters, each 1 byte long.
// the second and fourth use wide characters, these are typically longer.

// b) int, unsigned int, long int, unsigned long int, int, int
// the first is a normal integer.
// the second one has the u suffix indicating unsigned int.
// the third one has the L suffix indicating long int.
// the fourth one has the uL suffix indicating unsigned long int.
// the fifth one starts with a 0, indicating an octal integer literal.
// the sixth one starts with 0x, indicating a hexadecimal integer literal.

// c) double, float, long double
// the first one is a normal floating point literal.
// in the second one, the f suffix indicates float.
// in the third one, the L suffix indicates long double

// d) int, unsigned int, double, double
// the first one is a normal integer literal
// in the second one, the u suffix indicates unsigned int.
// in the third one, the decimal point causes the literal to be a double
// in the fourth one, usage of scientific notation causes this
