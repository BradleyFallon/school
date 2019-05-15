
#include "header.h"

Character::Character():
    name(NULL), personal_power(0), commanding_power(0), loyalty(0),
    leader(NULL), followers_head(NULL), pets_head(NULL), next(NULL),
    prev(NULL), is_privileged(false) {
    
    cout << "in the character constructor" << endl;

    name = new char[7];
    strcpy(name, "noname");

}

Character::~Character(){}

int Character::update_commanding_power(){};

void Character::display(){
    
    cout << "Name: " << name << "\n"
        << "Power: " << commanding_power << endl;
}


// Take an individual follower to be 
int Character::adopt(Character *){
    
}


//The LHS becomes an exact deepcopy of the RHS.
Character& Character::operator = (const Character& other){
    commanding_power = other.commanding_power;
    personal_power = other.personal_power;
    return *this;
}

// The result of adding characters, is the LHS character copied and gaining
// the RHS followers. This does not affect the LHS and RHS, it creates a copy.
Character  Character::operator + (const Character& other) const{
    Character temp;
    temp.commanding_power = other.commanding_power;
}

// If a int is added to a character, the result is the gains the int to self power.
Character  Character::operator + (const int) const{
    
}

// The character on the LHS inherits all rights and followers of the RHS.
// Name and any identification info is not affected.
Character& Character::operator += (const Character&){
    
}

// The character gains power equal to the int.
Character& Character::operator += (const int){
    
}


/*
( [] )
This will recursively fetch the follower of the nth position.
Followers are sorted by head being the oldest and most trusted.
*/
Character& Character::operator [] (int){
    
}


/*
( == ) (int, Character)
( != ) (int, Character)
( >, >= ) (int, Character)
( <, <= ) (int, Character)
*/
bool Character::operator == (const Character& other)const{
    return (this->commanding_power == other.commanding_power);
}

bool Character::operator == (const int)const{
    return true;
}

bool Character::operator != (const Character&)const{
    return true;
}

bool Character::operator != (const int)const{
    return true;
}

bool Character::operator < (const Character&)const{
    return true;
}

bool Character::operator < (const int)const{
    return true;
}

bool Character::operator > (const Character&)const{
    return true;
}

bool Character::operator > (const int)const{
    return true;
}

bool Character::operator <= (const Character&)const{
    return true;
}

bool Character::operator <= (const int)const{
    return true;
}

bool Character::operator >= (const Character&)const{
    return true;
}

bool Character::operator >= (const int)const{
    return true;
}


// friend ostream& operator << (ostream&, const Character&){
//     return true;
// }

MainCharacter::MainCharacter(): Character(){
    personal_power = 1;
    cout << "In the mainchar constructor" << endl;
};

MainCharacter::~MainCharacter(){
    cout << "Deleting main character" << endl;
};

void MainCharacter::display(){
    cout << "Hero ";
    Character::display();
}

int MainCharacter::update_commanding_power(){
    commanding_power = personal_power;
};

