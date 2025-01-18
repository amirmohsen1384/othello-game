#include "container.h"
#include <cstdlib>

int Bound(int min, int value, int max) {
    if(value < min) {
        value = min;
    } 
    else if (value > max) {
        value = max;
    }
    return value;
}

void Destroy(Coordinates &container) {
    free(container._data);
    container._size = 0;
    container._data = nullptr;
}

bool Insert(Coordinates &container, const Point &point, int index) {
    container._data = (Point*) realloc(container._data, ++container._size * sizeof(Point));
    if(container._data == NULL) {
        return false;
    }
    Point *data = container._data;
    int position = Bound(0, index, container._size);
    for(int i = container._size - 2; i >= position; i--) {
        *(data + i + 1) = *(data + i);
    }
    *(data + position) = point;
    return true;
}

bool Remove(Coordinates &container, int index) {
    Point *data = container._data;
    int position = Bound(0, index, container._size);
    for(int i = position; i < container._size - 1; ++i) {
        *(data + i) = *(data + i + 1);
    }
    container._data = (Point*) realloc(container._data, --container._size * sizeof(Point));
    return container._data != NULL;
}

bool Append(Coordinates &container, const Point &point) {
    return Insert(container, point, container._size);
}

bool Prepend(Coordinates &container, const Point &point) {
    return Insert(container, point, 0);
}

bool IsEmpty(const Coordinates &container) {
    return container._data == NULL || container._size == 0;
}

int Find(const Coordinates &container, const Point &point) {
    for(int i = 0; i < container._size; ++i) {
        if(IsIdentical(container._data[i], point)) {
            return i;
        }
    }
    return NOT_FOUND;
}

void Initialize(ChoiceList &list) {
    list._choices = nullptr;
    list._count = 0;
}

void Destroy(ChoiceList &list) {
    free(list._choices);
    list._choices = nullptr;
    list._count = 0;
}

bool Append(ChoiceList &list, const Text &description) {
    list._choices = (Text*) realloc(list._choices, ++list._count * sizeof(Text));
    if(list._choices == NULL) {
        return false;
    }
    list._choices[list._count - 1] = description;
    return true;
}

bool Remove(ChoiceList &list, int index) {
    Text *data = list._choices;
    int position = Bound(0, index, list._count);
    for(int i = position; i < list._count - 1; ++i) {
        *(data + i) = *(data + i + 1);
    }
    list._choices = (Text*) realloc(list._choices, --list._count * sizeof(Text));
    return list._choices != NULL;
}

bool IsEmpty(const ChoiceList &list) {
    return list._choices == NULL || list._count == 0;
}

int Find(const ChoiceList &list, const Text &description) {
    for(int i = 0; i < list._count; ++i) {
        if(!Compare(list._choices[i], description)) {
            return i;
        }
    }
    return NOT_FOUND;
}

#include "system.h"
#include <cstring>
#include <limits>

int Execute(const ChoiceList &list, const Text &description)
{
    return Execute(list, description._data);
}

int Execute(const ChoiceList &list, const char *description)
{
    using namespace std;
    typedef enum {Normal = 0, InvalidInput, NotAvailable} State;

    int choice;
    State state = Normal;

    do {
        // Clears the console.
        ClearConsole();

        // Shows up the description.
        PrintWith(description, BrightBlue);
        cout << endl;

        // Draws a seperator.
        for(int i = 1; i <= strlen(description); ++i) {
            cout << '=';
        }
        cout << endl;

        SetForeground(BrightGreen);
        // Shows up the choices.
        for(int i = 0; i < list._count; ++i) {
            cout << i + 1 << ") " << list._choices[i]._data << '\n';
        }
        ResetForeground();

        // Draws a seperator.
        for(int i = 1; i <= strlen(description); ++i) {
            cout << '=';
        }
        cout << endl;

        // Prints relevant error messages.
        if(state == InvalidInput) {
            PrintWith("You have entered an invalid input.\n", BrightRed);
        
        } else if(state == NotAvailable) {
            PrintWith("The choice you have entered is not in the list.\n", BrightRed);

        }

        // Reads a choice.    
        istream &stream = (cin >> choice);
        if(stream.fail()) {
            stream.clear();
            state = InvalidInput;
            stream.ignore(numeric_limits<streamsize>::max(), '\n');
        
        } else if(choice < 1 || choice > list._count) {
            state = NotAvailable;
        
        } else {
            break;
        }

    } while(true);

    // Finalizes the input.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    MakeBeep();

    return (choice - 1);
}