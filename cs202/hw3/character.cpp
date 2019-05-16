
#include "header.h"

Character::Character():
    name(NULL), personal_power(0), commanding_power(0), loyalty(0),
    leader(NULL), followers_head(NULL), pets_head(NULL), next(NULL),
    prev(NULL), is_privileged(false) {
    
    cout << "in the character constructor" << endl;

    name = new char[7];
    strcpy(name, "noname");

}

Character::Character(char * name, int personal_power):
    loyalty(0), leader(NULL), followers_head(NULL), pets_head(NULL), next(NULL),
    prev(NULL), is_privileged(false) {
    
    cout << "in the character constructor" << endl;

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    this->personal_power = personal_power;
}

Character::~Character(){}

int Character::update_commanding_power(){};

void Character::display(){
    
    cout << "Name: " << name << "\n"
        << "Power: " << commanding_power << endl;
}

// Break away from current alliance. Keep followers
int Character::secede(){
    if (prev)
        prev->next = next;
    if (next)
        next->prev = prev;
    if (leader)
        leader = NULL;
}

// Take an individual follower to be 
int Character::adopt(Character & other){
    cout << "hello" << endl;
    other.secede();
    other.leader = this;
    other.next = NULL;
    other.prev = followers_tail;
    followers_tail = &other;
    return 1;
}


//The LHS becomes an exact deepcopy of the RHS.
Character& Character::operator=(const Character& other){
    // If assigned to self, do nothing
    if (this == &other)
        return *this; 

    commanding_power = other.commanding_power;
    personal_power = other.personal_power;
    return *this;
}

// The result of adding characters, is the LHS character copied and gaining
// the RHS followers. This does not affect the LHS and RHS, it creates a copy.
Character Character::operator+(const Character& other) const{
    Character temp;
    temp.commanding_power = this->commanding_power + other.commanding_power;
    return temp;
}

// If a int is added to a character, the result is the gains the int to self power.
Character Character::operator+(const int val) const{
    Character temp;
    temp.commanding_power = this->commanding_power + val;
    return temp;
}

// The character on the LHS inherits all rights and followers of the RHS.
// Name and any identification info is not affected.
Character& Character::operator+=(const Character& other){
    this->commanding_power += other.commanding_power;
    return *this;
}

// The character gains power equal to the int.
Character& Character::operator+=(const int val){
    this->commanding_power += val;
    return *this;
}


/*
( [] )
This will recursively fetch the follower of the nth position.
Followers are sorted by head being the oldest and most trusted.
*/
Character& Character::operator[](int){
    
}


/*
( == ) (int, Character)
( != ) (int, Character)
( >, >= ) (int, Character)
( <, <= ) (int, Character)
*/
bool Character::operator==(const Character& other)const{
    return (this->commanding_power == other.commanding_power);
}

bool Character::operator==(const int val)const{
    return (this->commanding_power == val);
}

bool Character::operator!=(const Character& other)const{
    return !(*this == other);
}

bool Character::operator!=(const int val)const{
    return !(*this == val);
}

bool Character::operator<(const Character& other)const{
    return (this->commanding_power < other.commanding_power);
}

bool Character::operator<(const int val)const{
    return (this->commanding_power < val);
}

bool Character::operator>(const Character& other)const{
    return (this->commanding_power > other.commanding_power);
}

bool Character::operator>(const int val)const{
    return (this->commanding_power > val);
}

bool Character::operator<=(const Character& other)const{
    return (this->commanding_power <= other.commanding_power);
}

bool Character::operator<=(const int val)const{
    return (this->commanding_power <= val);
}

bool Character::operator>=(const Character& other)const{
    return (this->commanding_power > other.commanding_power);
}

bool Character::operator>=(const int val)const{
    return (this->commanding_power > val);
}


// friend ostream& operator << (ostream&, const Character&){
//     return true;
// }

MainCharacter::MainCharacter(): Character("Masked", 1){
    personal_power = 1;
    cout << "In the mainchar constructor" << endl;
}

MainCharacter::MainCharacter(char * name, int personal_power): Character(name, personal_power){};

MainCharacter::~MainCharacter(){
    cout << "Deleting main character" << endl;
}

void MainCharacter::display(){
    cout << "Hero ";
    Character::display();
}

int MainCharacter::update_commanding_power(){
    commanding_power = personal_power;
}

Creature::Creature(){}

int Creature::eat(Creature & prey){
    int absorbed;
    if (*this > prey){
        absorbed = prey.calories;
        energy += absorbed;
        delete &prey;
        return 1;
    }
    else return 0;
}

int Creature::eat(int energy){
    this->energy += energy;
    return 1;
}

Goat::Goat(){
    cout << "hello goat" << endl;
}
Horse::Horse(){}
Dragon::Dragon(){}
DragonEgg::DragonEgg(){}

