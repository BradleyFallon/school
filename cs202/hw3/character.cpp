
#include "header.h"

Character::Character():
    name(NULL), self_pwr(0), cmd_pwr(0), leader(NULL),
    followers_head(NULL), pets_head(NULL), next(NULL), prev(NULL),
    is_privileged(false) {
    
    cout << "in the character constructor" << endl;

    name = new char[7];
    strcpy(name, "noname");

}

Character::Character(char * name, int self_pwr):
    cmd_pwr(0), leader(NULL),
    followers_head(NULL), pets_head(NULL), next(NULL), prev(NULL),
    is_privileged(false) {
    
    cout << "in the character constructor" << endl;

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    this->self_pwr = self_pwr;
}

Character::Character(const Character & other){
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    self_pwr = other.self_pwr;
    cmd_pwr = other.cmd_pwr;
    leader = other.leader;
    followers_head = other.followers_head;
    pets_head = other.pets_head;
    next = other.next;
    prev = other.prev;
    is_privileged = other.is_privileged;
}

Character::~Character(){}

void Character::display_name(){
    cout << name;
}

int Character::rally_power(){
    update_cmd_pwr();
    if (next) return cmd_pwr + next->rally_power();
    return cmd_pwr;
}

int Character::display_rally(){
    display_name();
    if (next) {
        cout << ", ";
        return 1 + next->display_rally();
    }
    else cout << endl;
    return 1;
}

int Character::update_cmd_pwr(){
    cmd_pwr = self_pwr;
    if (followers_head)
        cmd_pwr += followers_head->rally_power();
    if (pets_head)
        cmd_pwr += pets_head->rally_power();
    return cmd_pwr;
}

void Character::display(){
    int follower_count = 0;
    int pets_count = 0;

    update_cmd_pwr();
    display_name();
    cout << "\n"
        << "Individual Power: " << self_pwr << "\n"
        << "Total Commanding Power: " << cmd_pwr << "\n"

        << "Direct Followers: " << "\t";
    if (followers_head) {
        follower_count = followers_head->display_rally();
        cout << follower_count << " direct reports." << "\n";
    }
    else cout << "No Followers" << "\n";

    cout << "Direct Pets: " << "\t";
    if (pets_head) {
        pets_count = pets_head->display_rally();
        cout << pets_count << " direct pets." << "\n";
    }
    else cout << "No pets" << "\n";

    cout << "\n" << endl;
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
Character * Character::adopt(Character * other){
    other->secede();

    other->leader = this;

    other->next = NULL;
    other->prev = followers_tail;

    if (!followers_head){
        followers_head = other;
    } else
        followers_tail->next = other;
    followers_tail = other;

    return this;
}

// Take an individual follower to be 
Character * Character::adopt(Creature * other){
    other->secede();

    other->leader = this;

    other->next = NULL;
    other->prev = pets_tail;

    if (!pets_head){
        pets_head = other;
    } else
        pets_tail->next = other;
    pets_tail = other;
    
    return this;
}

//The LHS becomes an exact deepcopy of the RHS.
Character& Character::operator=(const Character& other){
    // If assigned to self, do nothing
    if (this == &other)
        return *this; 

    cmd_pwr = other.cmd_pwr;
    self_pwr = other.self_pwr;
    return *this;
}

// The result of adding characters, is the LHS character copied and gaining
// the RHS followers. This does not affect the LHS and RHS, it creates a copy.
int Character::operator+(const Character& other) const{

    return this->cmd_pwr + other.cmd_pwr;
}

// If a int is added to a character, the result is the gains the int to self power.
int Character::operator+(const int val) const{
    return this->cmd_pwr + val;
}

// The character on the LHS inherits all rights and followers of the RHS.
// Name and any identification info is not affected.
Character& Character::operator+=(const Character& other){
    this->cmd_pwr += other.cmd_pwr;
    return *this;
}

// To adopt a character as a follower
Character* Character::operator+=(Character* other){
    return adopt(other);
}

// The character gains power equal to the int.
Character& Character::operator+=(const int val){
    this->self_pwr += val;
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
    return (this->cmd_pwr == other.cmd_pwr);
}

bool Character::operator==(const int val)const{
    return (this->cmd_pwr == val);
}

bool Character::operator!=(const Character& other)const{
    return !(*this == other);
}

bool Character::operator!=(const int val)const{
    return !(*this == val);
}

bool Character::operator<(const Character& other)const{
    return (this->cmd_pwr < other.cmd_pwr);
}

bool Character::operator<(const int val)const{
    return (this->cmd_pwr < val);
}

bool Character::operator>(const Character& other)const{
    return (this->cmd_pwr > other.cmd_pwr);
}

bool Character::operator>(const int val)const{
    return (this->cmd_pwr > val);
}

bool Character::operator<=(const Character& other)const{
    return (this->cmd_pwr <= other.cmd_pwr);
}

bool Character::operator<=(const int val)const{
    return (this->cmd_pwr <= val);
}

bool Character::operator>=(const Character& other)const{
    return (this->cmd_pwr > other.cmd_pwr);
}

bool Character::operator>=(const int val)const{
    return (this->cmd_pwr > val);
}


// friend ostream& operator << (ostream&, const Character&){
//     return true;
// }

MainCharacter::MainCharacter(): Character("Masked", 1){
    self_pwr = 1;
    cout << "In the mainchar constructor" << endl;
}

MainCharacter::MainCharacter(char * name, char * house, int self_pwr): Character(name, self_pwr){
    this->house = new char[strlen(house) + 1];
    strcpy(this->house, house);
};

MainCharacter::~MainCharacter(){
    cout << "Deleting main character" << endl;
}

void MainCharacter::display_name(){
    cout << "*" << name << " of House " << house << "*";
}

// void MainCharacter::display(){
    
//     Character::display();
// }

// int MainCharacter::update_cmd_pwr(){
//     cmd_pwr = self_pwr;
// }

Creature::Creature(){}
Creature::Creature(char * name, int self_pwr): Character(name, self_pwr){};
Creature::Creature(const Creature & other): Character(other){};

void Creature::display_name(){
    cout << name << " (" << get_species() << ")";
}

int Creature::eat(int energy){
    this->energy += energy;
    return 1;
}

int Creature::eat(Creature & prey){
    int absorbed;
    if (*this > prey){
        eat(prey.calories);
        delete &prey;
        return 1;
    }
    else return 0;
}

char Goat::species[5] = "Goat";
Goat::Goat(): Creature("Goatey", 1){}
const char* Goat::get_species() {return species;}
int Goat::eat(int energy){
    Creature::eat(energy);
}
int Goat::eat(Creature & prey){
    Creature::eat(prey);
}

char Horse::species[6] = "Horse";
Horse::Horse(): Creature("Horsey", 4){}
const char* Horse::get_species() {return species;}
int Horse::eat(int energy){
    Creature::eat(energy);
}
int Horse::eat(Creature & prey){
    Creature::eat(prey);
}

char DragonEgg::species[7] = "Dragon";
DragonEgg::DragonEgg(): Creature("?????", 0){}
DragonEgg::DragonEgg(char * name, int self_pwr): Creature(name, self_pwr){};
const char* DragonEgg::get_species() {return species;}
int DragonEgg::eat(int energy){
    Creature::eat(energy);
    if (this->energy > 5){
        cout << "OMG the dragon egg is hatching!!!1!" << endl;
        Dragon * spawnling;
        spawnling = new Dragon(*this);
        delete this;
    }
}
int DragonEgg::eat(Creature & prey){
    return 0;
}

char Dragon::species[7] = "Dragon";
Dragon::Dragon(): Creature("Welp", 20){}
Dragon::Dragon(char * name, int self_pwr): Creature(name, self_pwr){};
Dragon::Dragon(const DragonEgg & other): Creature(other) {
}
const char* Dragon::get_species() {return species;}
int Dragon::eat(int energy){
    Creature::eat(energy);
}
int Dragon::eat(Creature & prey){
    Creature::eat(prey);
}
