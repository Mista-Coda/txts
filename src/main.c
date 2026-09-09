#include "stringView.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t lineCount;
    size_t charCount;
    size_t wordCount;
} FileInfo;

typedef struct {
    bool totalOnly;
} ProcessingOptions;

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

bool isWhitespace(char c) {
    char whitespaceChars[] = {
        ' ', '\n', '\0', '\t',
    };

    return strchr(whitespaceChars, c) != NULL;
}

bool processFile(const char* filePath, FileInfo* info) {
    char* sourceCString = readEntireFile(filePath);
    if (sourceCString == NULL) { return false; }

    StringView sv = {0};
    svSetStrAndFree(&sv, sourceCString);

    for (size_t i = 0; i < sv.length; ++i) {
        char c = sv.characters[i];
        info->charCount++;

        if (c == '\n') {
            info->lineCount++;
        }

        if (isWhitespace(c)) {
            if (i > 0 && !isWhitespace(sv.characters[i - 1])) {
                info->wordCount++;
            }
        }
    }

    info->lineCount++;
    info->wordCount++;

    svFree(&sv);
    return true;
}

int main(int argc, const char** argv) {
    const char* programName = argv[0];

    if (argc < 2) {
        fprintf(stderr, "USAGE: %s <FILES...>\n", programName);
        return 1;
    }

    ProcessingOptions opts = {0};
    
    for (int i = 1; i < argc; ++i) {
        StringView sv = {0};
        svSetStr(&sv, argv[i]);

        if (!svStartsWith(&sv, "-")) {
            svFree(&sv);
            continue;
        };

        if (svMatchesCStr(&sv, "--total") || svMatchesCStr(&sv, "-t")) {
            opts.totalOnly = true;
            svFree(&sv);
            continue;
        }

        svFree(&sv);
    }

    FileInfo total = {0};

    for (int i = 1; i < argc; ++i) {
        const char* filePath = argv[i];
        // Ignore all flags
        if (filePath[0] == '-') continue;

        FileInfo info = {0};
        bool didProcess = processFile(filePath, &info);
        if (!didProcess) {
            fprintf(stderr, "Failed to parse file: %s", filePath);
            return 1;
        }

        if (!opts.totalOnly) {
            printf("[%s]\n    Lines: %zu\n    Characters: %zu\n    Words: %zu\n", filePath, info.lineCount, info.charCount, info.wordCount);
        } else {
            total.charCount += info.charCount;
            total.lineCount += info.lineCount;
            total.wordCount += info.wordCount;
        }
    }

    if (opts.totalOnly) {
        printf("[%s]\n    Lines: %zu\n    Characters: %zu\n    Words: %zu\n", "TOTAL", total.lineCount, total.charCount, total.wordCount);
    }
    return 0;
}