#include "stringView.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void svSetStr(StringView* sv, const char* cStr) {
    size_t stringLength = strlen(cStr);
    size_t stringLengthBytes = stringLength * sizeof(char);
    sv->length = stringLength;
    sv->characters = malloc(stringLengthBytes);
    memcpy(sv->characters, cStr, stringLengthBytes);
}

void svSetStrAndFree(StringView* sv, char* cStr) {
    svSetStr(sv, cStr);
    free(cStr);
}

bool svStartsWith(StringView* sv, const char* with) {
    size_t withLength = strlen(with);
    if (sv->length < withLength) return false;
    
    for (size_t i = 0; i < withLength; ++i) {
        char svLetter = sv->characters[i];
        char withLetter = with[i];
        if (svLetter != withLetter) return false;
    }

    return true;
}

bool svMatchesCStr(StringView* sv, const char* cStr) {
    size_t cstrLength = strlen(cStr);
    if (sv->length != cstrLength) return false;
    for (size_t i = 0; i < cstrLength; ++i) {
        char svChar = sv->characters[i];
        char cStrChar = cStr[i];
        if (svChar != cStrChar) return false;
    }
    return true;
}

void svFree(StringView* sv) {
    if (sv->characters != NULL) {
        free(sv->characters);
    } else {
        printf("[WARNING] String view cleared with no allocated string");
    }
}