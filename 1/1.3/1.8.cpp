// line 1 is legal, it will print
//
// "/*" (excluding the quotation marks)

// line 2 is legal, it will print
//
// "*/" (excluding the quotation marks)

// line 3 is illegal as the
// /* "*/
// part is commented out, so the right operand of the output
// operator becomes
// " */;
// there is no quotation mark to mark the end of the string.

// line 4 is legal as well, the first
// /* "*/
// after the output operator is commented out. then the
// " /* "
// is used as the right operand of the output operator.
// The remaining /*" */ is commented out. It will print
//
// " /* " (excluding the quotation marks)
