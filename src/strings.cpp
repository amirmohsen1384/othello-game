#include "../include/strings.h"
#include <cstring>
#include <iostream>

void Initialize(String &value, const char *buffer) {
    value.size = std::strlen(buffer);
    value.data = static_cast<char*>(std::calloc(value.size + 1, sizeof(char)));
    if(value.data == nullptr) {
        return;
    }
    std::strcpy(value.data, buffer);
}

String Construct(const char *buffer) {
    String value;
    Initialize(value, buffer);
    return value;
}

String GetLine() {
    size_t size = 1;
    char *input = NULL;
    char temporary = '\0';
    String result = {NULL, 0};
    while((temporary = getc(stdin)) != EOF) {
        if(temporary == '\n') {
            break;
        }
        input = static_cast<char*>(realloc(input, ++size * sizeof(char)));
        if(input == NULL) {
            return result;
        }
        *(input + size - 2) = temporary;
        *(input + size - 1) = '\0';
    }
    result.size = size - 1;
    result.data = input;
    return result;
}

void Destroy(String &value) {
    if(value.data != NULL) {
        free(value.data);
        value.data = NULL;
        value.size = 0;
    }
}

int Remove(String &value, size_t pos) {
    if(pos >= 0 && pos < value.size) {
        for(int j = pos; j < value.size; ++j) {
            value.data[j] = value.data[j + 1];
        }
        value.data = static_cast<char*>(realloc(value.data, value.size-- * sizeof(char)));
        return 1;

    } else {
        return 0;
        
    }
}

bool IsEmpty(const String &string) {
    return string.size == 0 || string.data == NULL;
}

// Compares two characters in a case-insensitive way.
int CompareCharacter(char one, char two) {
    if(one >= 'A' && one <= 'Z') {
        one += 32;
    }
    if(two >= 'A' && two <= 'Z') {
        two += 32;
    }
    if(one < two) {
        return -1;    
    }
    return one > two;
}

int Compare(const String &one , const String &two, bool sensitive) {
    int length = (one.size < two.size) ? one.size : two.size;
    for(int i = 0; i < length; ++i) {
        const char a = one.data[i];
        const char b = two.data[i];
        if(!sensitive) {
            int result = CompareCharacter(a, b);
            if(result != 0) {
                return result;
            }

        } else {
            if(a > b) {
                return 1;
            
            } else if(a < b) {
                return -1;

            }
        }
    }
    return 0;
}

void Print(const String &string) {
    std::cout << string.data;
}