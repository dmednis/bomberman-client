
#include <string.h>

/* Prepends t into s. Assumes s has enough space allocated
** for the combined string.
*/
void prepend_char(unsigned char *s, unsigned char t) {
    s[0] = t;
}