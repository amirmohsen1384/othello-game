#include <iostream>
#include <cstring>
#include "text.h"

void Initialize(Text &value, const char *buffer) {
    // Deletes everything that already exists in the value
    Destroy(value);

    // Initializes the new text
    value._size = std::strlen(buffer);
    value._data = static_cast<char*>(std::calloc(value._size + 1, sizeof(char)));
    if(value._data == nullptr) {
        return;
    }
    std::strcpy(value._data, buffer);
}

Text Create(const char *buffer) {
    Text value = {NULL, 0};
    Initialize(value, buffer);
    return value;
}

void Destroy(Text &value) {
    free(value._data);
    value._data = NULL;
    value._size = 0;
}

bool Remove(Text &value, int pos) {
    if(pos >= 0 && pos < value._size) {
        for(int j = pos; j < value._size; ++j) {
            value._data[j] = value._data[j + 1];
        }
        value._data = static_cast<char*>(realloc(value._data, value._size-- * sizeof(char)));
        return true;

    } else {
        return false;
        
    }
}

bool IsEmpty(const Text &string) {
    return string._size == 0 || string._data == NULL;
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

int Compare(const Text &one , const Text &two, bool sensitive) {
    int length = (one._size < two._size) ? one._size : two._size;
    for(int i = 0; i < length; ++i) {
        const char a = one._data[i];
        const char b = two._data[i];
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

void Print(const Text &string) {
    std::cout << string._data;
}
Text GetLine() {
    int size = 1;
    char *input = NULL;
    char temporary = '\0';
    Text result = {NULL, 0};
    while ((temporary = getc(stdin)) != '\n') {
        char *temp = static_cast<char*>(realloc(input, (size + 1) * sizeof(char)));
        if (temp == NULL) {
            free(input);
            return result;
        }
        input = temp;
        input[size - 1] = temporary;
        ++size;
    }
    if (input) {
        input[size - 1] = '\0';
        result._size = size - 1;
        result._data = input;
    }
    return result;
}

char Uppercase(char letter) {
    if(letter >= 'a' && letter <= 'z') {
        letter -= ('a' - 'A');
    }
    return letter;
}

void Append(Text &target, const char *another) {
    std::strcat(target._data, another);
    target._size += std::strlen(another); 
}

void Append(Text &target, const Text &another) {
    Append(target, another._data);
}

void Assign(Text &target, const Text &source) {
    Initialize(target, source._data);
}