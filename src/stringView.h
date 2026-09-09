#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    char* characters;
    size_t length;
} StringView;

void svSetStr(StringView* sv, const char* cStr);
void svSetStrAndFree(StringView* sv, char* cStr);
bool svStartsWith(StringView* sv, const char* with);
bool svMatchesCStr(StringView* sv, const char* cStr);
void svFree(StringView* sv);