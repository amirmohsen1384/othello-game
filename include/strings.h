#ifndef STRINGS_H
#define STRINGS_H

#include <cstdlib>

/* A basic type to work with dynamic strings. */
typedef struct String {    
    char *data;
    int size;
}
String;

// Checks whether a string is empty or not.
bool IsEmpty(const String &);

// Initialize a string with a constant array of bytes.
void Initialize(String &, const char *);

// Get a line of text from the input stream.
String GetLine();

// Free up the memory cosumed by the string.
void Destroy(String &);

// Remove a character from the string.
int Remove(String &, size_t);

// Compare two different strings.
int Compare(const String & , const String &, bool sensitive = true);

// Construct a string based on a constant array of bytes.
String Construct(const char *);

#endif