
#include <string.h>

/* Prepends t into s. Assumes s has enough space allocated
** for the combined string.
*/
void prepend(char *s, const char *t) {
    size_t len = strlen(t);
    size_t i;

    memmove(s + len, s, strlen(s) + 1);

    for (i = 0; i < len; ++i) {
        s[i] = t[i];
    }
}