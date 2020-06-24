

 'b': unsigned byte (char)
 'B': byte sized bitfield - both signed and unsigned values allowed (char)
 'h': signed short int (short)
 'H': short int sized bitfield, both signed and unsigned allowed (unsigned short) !!!
 'i': signed int (int)
 'I': int sized bitfield, both signed and unsigned allowed (unsigned int)
 'n': /* Py_ssize_t */
 'l': /* long int */
 'k': /* long sized bitfield */ (unsigned long)
 'L': /* long long */
 'K': /* long long sized bitfield */ (unsigned long long)
 'f': /* float */
 'd': /* double */
 'D': /* complex double */ (Py_complex)
 'c': /* char */ (char) 
 'C': /* unicode char */ (int)
 'p': /* boolean *p*redicate */ (int)
 'y': /* any bytes-like object */ (void*)
 's': * text string or bytes-like object */ (const char *)
 'z': * text string, bytes-like object or None */ 
 'u': * raw unicode buffer (Py_UNICODE *) */(Py_UNICODE *)
 'Z': * raw unicode buffer or None */
 'e': /* encoded string */ (const char)
case 'S': { /* PyBytes object */
case 'Y': { /* PyByteArray object */
case 'U': { /* PyUnicode object */
case 'O': { /* object */
