#pragma once

#undef strtok

// Implement a strtok equivalent without using any standard library headers
// or globals. Uses a function-local static pointer to keep state between calls.

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
        return 0; // undefined by standard; return null defensively
    }

    // Initialize saved pointer on first call with non-null str
    if (str != 0) {
        saved = str;
    } else {
        if (saved == 0) return 0;
    }

    // Skip leading delimiters
    char *p = saved;
    while (*p && __is_delim_char(*p, delim)) {
        ++p;
    }

    if (*p == '\0') {
        // No more tokens
        saved = 0;
        return 0;
    }

    // Start of the token
    char *token_start = p;

    // Advance until delimiter or end of string
    while (*p && !__is_delim_char(*p, delim)) {
        ++p;
    }

    if (*p == '\0') {
        // Reached end; this is the last token
        saved = 0;
        return token_start;
    } else {
        // Terminate current token and set saved for the next call
        *p = '\0';
        saved = p + 1;
        return token_start;
    }
}

