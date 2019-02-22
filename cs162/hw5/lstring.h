
#include <iostream>

using namespace std;

struct Letter
{
    char val = '?'; // This is the actual letter character
    Letter* next = NULL; // Pointer to the next letter in the string
};

class String
{
public:
    // create an empty String with no characters
    String();

    // create a String from a character array
    // String should have the same characters in the same order.
    String(const char* from);

    // delete the String, and all of the characters
    ~String();

    // check to see if the String is empty
    bool empty();

    // get the length of the String
    int length();

    // return true if this String is equal to other.
    // two Strings are equal if they have the same characters in the same order.
    bool equals(String& other);

    // creates a new String that with all of the characters in the opposite order
    void reverse(String& out);

    // check to see if a String is a palindrome
    // A palindrome is a word that is the same forwards and back
    // for example: "racecar"
    bool palindrome();

    // put a single character in front of the String
    void prepend(char start);

    // put a single character at the end of the String
    void append(char end);

    // put an entire second String at the end of the String
    // This should leave the second String empty
    //
    // example:
    // String abc("abc");
    // String def("def");
    // abc.append(def);
    //
    // at the end
    // abc == String("abcdef")
    // def == String("")
    void append(String& other);

    // print out all of the characters in the String.
    void display();

private: 
    //  How do we represent the String?
	Letter* head;
};
