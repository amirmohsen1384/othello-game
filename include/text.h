#ifndef TEXT_H
#define TEXT_H
#include <cstdlib>
#include <cstdint>

// Defined a type for a certain integer data type.
typedef int64_t Size;

/* A basic type to work with dynamic text. */
typedef struct Text {    
    char*   _data;
    Size    _size;
}
Text;

// Checks whether a string is empty or not.
bool IsEmpty(const Text &);

// Initialize a string with a constant array of bytes.
void Initialize(Text &, const char *);

// Get a line of text from the input stream.
Text GetLine();

// Free up the memory cosumed by the string.
void Destroy(Text &);

// Remove a character from the string.
bool Remove(Text &, int);

// Compare two different strings.
int Compare(const Text & , const Text &, bool sensitive = true);

// Construct a string based on a constant array of bytes.
Text Create(const char *);

// Prints out a string.
void Print(const Text &);

// Uppercase the letter
char Uppercase(char);

// Serializes the text into the stream.
#include <iostream>
std::ofstream& WriteText(std::ofstream &stream, const Text &text);
std::ifstream& ReadText(std::ifstream &stream, Text &text);

#endif