#pragma once

#include <stddef.h>

typedef struct {
    char* characters;
    size_t length;
} StringView;

void svSetStr(StringView* sv, const char* cStr);
void svSetStrAndFree(StringView* sv, char* cStr);
void svFree(StringView* sv);