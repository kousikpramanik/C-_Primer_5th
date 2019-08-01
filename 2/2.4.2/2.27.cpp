// a) &r = 0 is illegal. to point to the literal 0, r must be of type
//    reference to const int.
// b) legal.
// c) legal.
// d) legal.
// e) legal.
// f) illegal. & doesn't need a const beside it. a reference cannot be
//    used to access a different object after initialization.
// g) legal.
