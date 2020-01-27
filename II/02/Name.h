#ifndef NAME_H
#define NAME_H

struct Name
{
    // struct for storing a name and the length of the name

    const char * name;
    unsigned int length;

    // default constructor takes a pointer to anull terminated c-string and
    // length of the name
    Name(const char * name, unsigned int length) :
        name(name), length(length)
    {    
    }

    // additional constructor overload takes pointers to parts of a name
    // and combines the names into one string as "Last, First Middle"
    Name(const Name &first, const Name &middle, const Name &last) {
        // init members
        length = first.length + middle.length + last.length + 3; // add 3 for 
        char *fullName = new char[length];                       // spaces and
                                                                 // comma
        // declare a var for iterating over the full name
        unsigned int fullNameIndex = 0;

        // add last name
        for (unsigned int i = 0; i < last.length; i++) {
            *(fullName + fullNameIndex++) = *(last.name + i);
        }

        // add seperators
        *(fullName + fullNameIndex++) = ',';
        *(fullName + fullNameIndex++) = ' ';

        // add first name
        for (unsigned int i = 0; i < first.length; i++) {
            *(fullName + fullNameIndex++) = *(first.name + i);
        }

        // add space
        *(fullName + fullNameIndex++) = ' ';

        // add middle name
        for (unsigned int i = 0; i < middle.length; i++) {
            *(fullName + fullNameIndex++) = *(middle.name + i);
        }

        // assign to pointer member
        name = fullName;
    }

    // method for printing a name on one line
    void printName() {
        for (unsigned int i = 0; i < length; i++) {
            std::cout << *(name + i);
        }
        std::cout << std::endl;
    }

    // destructor frees the memory from the name allocation
    ~Name() {
        delete[] name;
    }
};

#endif // !NAME_H
