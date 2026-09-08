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

void svFree(StringView* sv) {
    if (sv->characters != NULL) {
        free(sv->characters);
    } else {
        printf("[WARNING] String view cleared with no allocated string");
    }
}