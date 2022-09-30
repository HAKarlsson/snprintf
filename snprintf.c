#include <stdarg.h>
// Max #characters in string repr. of 64-bit int (excl. '\0').
#define INT_MAX_CHAR_SIZE  20

static int _from_int(char *buf, unsigned long int size, unsigned long val, int neg, int base) {
    // Buffer for writing intermediate result
    char str[INT_MAX_CHAR_SIZE];
    // index into str
    int i = INT_MAX_CHAR_SIZE;
    // index into buf
    int j = 0;
    
    // Build the string while val != 0
    do {
        if (val % base < 10) {
            // For base 10 and 16
            str[--i] = '0' + (val % base);
        } else {
            // Only base 16
            str[--i] = 'A' + (val % base) - 10;
        }
        val /= base;
    } while (val != 0);
    // Add '-' if val was negative
    if (neg) 
        str[--i] = '-'; 

    // Copy the result to target buffer.
    while (i < INT_MAX_CHAR_SIZE && j < size)
        buf[j++] = str[i++];
    // Return characters written to buffer.
    return j;
}

static int _from_str(char *buf, unsigned long int size, char *val) {
    int i = 0;
    while (val[i] != '\0' && i < size) {
        buf[i] = val[i];
        i++;
    }
    return i;
}

int snprintf(char *buf, unsigned long int size, const char *format, ...) {
    // argument pointer
    va_list ap;
    // i: buf index, j: format index
    int i = 0, j = 0;
    // ebuf: end of buf
    // ap points after 'format'
    va_start(ap, format);
    while (format[j] != '\0' && i >= 0 && i < size - 1) {
        char c = format[j++];
        if (c != '%') {
            buf[i++] = c;
            continue;
        }
        c = format[j++];
        if (c == 'c') {
            // char gets promoted to int
            char val = va_arg(ap, int);
            buf[i++] = val;
        } else if (c == 's') {
            char *val = va_arg(ap, char*);
            i += _from_str(buf + i, size - i, val);
        } else if (c == 'd') {
            int val = va_arg(ap, int);
            int neg = val < 0;
            i += _from_int(buf + i, size - i, (neg ? -val : val), neg, 10);
        } else if (c == 'x') {
            int val = va_arg(ap, int);
            i += _from_int(buf + i, size - i, val, 0, 16);
        }
    }
    va_end(ap);
    buf[i++] = '\0';
    // Returns #chars written to buf
    // Does this work???
    return i;
}
