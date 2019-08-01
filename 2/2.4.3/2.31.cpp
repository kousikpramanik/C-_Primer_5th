// r1 = v2;
// legal. top-level const of v2 is ignored.

// p1 = p2;
// illegal. low-level const of p2 prevents the copy.

// p2 = p1;
// legal. low-level const of p2 causes further changes
// by dereferencing p2 illegal. however, p1 may still be
// dereferenced to change the value pointed to by it.

// p1 = p3;
// illegal. low-level const of p3 prevents the copy.
// top-level const of p3 is ignored.

// p2 = p3;
// legal. same low-level const qualified type. top-level
// const of p3 is ignored.
