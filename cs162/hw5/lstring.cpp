#include "lstring.h"


// create an empty String with no characters
String::String()
{
	head = NULL;
}

// create a String from a character array
// String should have the same characters in the same order.
String::String(const char* from)
{
	int i = 0;

	if (!from)
	{
		head = NULL;
		return;
	}

	while (from[i] != '\0')
	{
		append(from[i]);
		++i;
	};
}	

// delete the String, and all of the characters
String::~String()
{
	return;
}

// check to see if the String is empty
bool String::empty()
{
	return (head==NULL);
}

// get the length of the String
int String::length()
{
	int count = 0;
	Letter* current;

	if (head==NULL)
	{
		return 0;
	}
	while (current)
	{
		current = current->next;
		++count;
	}
	return count;		
}

// return true if this String is equal to other.
// two Strings are equal if they have the same characters in the same order.
bool String::equals(String& other)
{
	Letter* current_this = head;
	Letter* current_other = other.head;

	if (current_this->val != current_other->val){
		return false;
	}

	while (current_this->next || current_other->next)
	{
		// If one is shorter than other, then one next is null and other is not
		// Since we are comparing nexts, we need to compare if this OR other has a non-null next pointer.
		if (!(current_this->next && current_other->next))
		{
			// One next is null, but other is not. Inequal strings.
			return false;
		}
		current_this = current_this->next;
		current_other = current_other->next;
		if (current_this->val != current_other->val)
		{
			return false;
		}
	}
	// If we made it this far, then there were no inqualities detected, so strings are a match
	return true;		
}

// creates a new String that with all of the characters in the opposite order
void String::reverse(String& out)
{
	Letter* current_this = head;
	
	if (!head) return;

	while (current_this)
	{
		out.prepend(current_this->val);
		current_this = current_this->next;
	}
}


// check to see if a String is a palindrome
// A palindrome is a word that is the same forwards and back
// for example: "racecar"
bool String::palindrome()
{
	// Make a new temp string that is a copy of this
	String reverse_copy;	
			
	// Reverse the copy
	reverse(reverse_copy);	

	// Check if the copy is equal to this after it was reversed	
	return equals(reverse_copy);
}

// put a single character in front of the String
void String::prepend(char start)
{
	Letter* new_letter = new Letter;

	// Initialize the new character with the given char
	new_letter->val = start;
	
	// Check if string is empty, then just set head to this letter
	if (!head)
	{
		head = new_letter;
		return;
	}	
	
	// If code gets to here, then we need to insert before an existing letter node
	// Make new letter next point to wherever head was, then put new letter in head.
	new_letter->next = head;
	head = new_letter;
}

// put a single character at the end of the String
void String::append(char end)
{
	Letter* current = head;
	Letter* new_letter = new Letter;

	// Initialize the new character with the given char
	new_letter->val = end;

	// If the string is empty, then the new letter just goes to head
	if (!head)
	{
		head = new_letter;
		return;
	}
	
	// If there are letters in the string, then we need to move current to the end
	while (current->next)
	{
		current = current->next;
	}
	current->next = new_letter;		
}

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
void String::append(String& other)
{
	Letter* current = head;
	Letter* new_letter = other.head;

	// If the string is empty, then the new letter just goes to head
	if (!head)
	{
		head = new_letter;
		return;
	}
	
	// If there are letters in the string, then we need to move current to the end
	while (current->next)
	{
		current = current->next;
	}
	current->next = new_letter;		
}

// print out all of the characters in the String.
void String::display()
{
	Letter* current = head;

	while (current)
	{
		cout << current->val;
		current = current->next;
	}
	cout << endl;
}

