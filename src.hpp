// No standard headers allowed; implement strtok under namespace sjtu

#undef strtok

namespace sjtu {

static int __is_delim_char(char c, const char * __restrict delim) {
    const char *p = delim;
    while (*p) {
        if (*p == c) return 1;
        ++p;
    }
    return 0;
}

char *strtok(char * __restrict str, const char * __restrict delim) {
    static char *saved = 0;

    if (!delim) {
        return 0; // defensively return null if delim is null
    }

    if (str != 0) {
        saved = str;
    } else {
        if (saved == 0) return 0;
    }

    char *p = saved;
    while (*p && __is_delim_char(*p, delim)) {
        ++p;
    }

    if (*p == '\0') {
        saved = 0;
        return 0;
    }

    char *token_start = p;

    while (*p && !__is_delim_char(*p, delim)) {
        ++p;
    }

    if (*p == '\0') {
        saved = 0;
        return token_start;
    } else {
        *p = '\0';
        saved = p + 1;
        return token_start;
    }
}

} // namespace sjtu
