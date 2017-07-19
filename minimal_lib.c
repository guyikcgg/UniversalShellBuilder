#include <minimal_lib.h>

/* strcmp: compares two strings (returns something like 'str1 > str2') */
int strcmp(const char *str1, const char *str2) {
    int d;

    // Exception: NULL
    if (str1==NULL && str2==NULL) {
        return 0;
    } else if (str1 == NULL) {
        return +1;
    } else if (str2 == NULL) {
        return -1;
    }

    // Normal case
    for (d=*str1-*str2; d==0; d=*str1-*str2) {
        if (*str1 == '\0') return 0;
        str1++; str2++;
    }

    return d;
}
