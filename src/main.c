#include "stringView.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t lineCount;
    size_t charCount;
} FileInfo;

char* readEntireFile(const char* path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char *source = malloc(size + 1);

    fread(source, 1, size, file);
    source[size] = '\0';

    fclose(file);

    return source;
}

bool processFile(const char* filePath, FileInfo* info) {
    char* sourceCString = readEntireFile(filePath);
    if (sourceCString == NULL) { return false; }

    StringView sv = {0};
    svSetStrAndFree(&sv, sourceCString);

    for (size_t i = 0; i < sv.length; ++i) {
        char c = sv.characters[i];
        switch (c) {
            case '\n':
                info->lineCount++;
                /* fall through */
            default: info->charCount++; break;
        }
    }

    info->lineCount++;

    svFree(&sv);
    return true;
}

int main(int argc, const char** argv) {
    const char* programName = argv[0];

    if (argc < 2) {
        fprintf(stderr, "USAGE: %s <FILES...>\n", programName);
        return 1;
    }

    for (size_t i = 1; i < argc; ++i) {
        const char* filePath = argv[i];
        FileInfo info = {0};
        bool didProcess = processFile(filePath, &info);
        if (!didProcess) {
            fprintf(stderr, "Failed to parse file");
            return 1;
        }

        printf("[%s]\n    Lines: %zu\n    Characters: %zu\n", filePath, info.lineCount, info.charCount);
    }
    return 0;
}