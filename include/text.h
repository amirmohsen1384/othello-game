#ifndef TEXT_H
#define TEXT_H

/* A basic type to work with dynamic text. */
typedef struct Text {    
    char*   _data;
    int     _size;
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

#endif