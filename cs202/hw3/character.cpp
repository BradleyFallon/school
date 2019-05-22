
#include "header.h"

Character::Character():
    name(NULL), self_pwr(4), cmd_pwr(4), leader(NULL),
    followers_head(NULL), followers_tail(NULL),
    next(NULL), prev(NULL), is_privileged(false) {
    
    name = new char[7];
    strcpy(name, "noname");
}

Character::Character(const char * name, int self_pwr):
    self_pwr(self_pwr), cmd_pwr(self_pwr), leader(NULL),
    followers_head(NULL), followers_tail(NULL),
    next(NULL), prev(NULL), is_privileged(false) {
    
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Character::Character(const Character & other){
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    self_pwr = other.self_pwr;
    cmd_pwr = other.cmd_pwr;
    leader = other.leader;
    followers_head = other.followers_head;
    followers_tail = other.followers_tail;
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

bool Character::is_root(){
    if (leader) return false;
    return true;
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
    // if (pets_head)
    //     cmd_pwr += pets_head->rally_power();
    return cmd_pwr;
}

void Character::display(){
    int follower_count = 0;
    // int pets_count = 0;

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

    // cout << "Direct Pets: " << "\t";
    // if (pets_head) {
    //     pets_count = pets_head->display_rally();
    //     cout << pets_count << " direct pets." << "\n";
    // }
    // else cout << "No pets" << "\n";

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
Character * Character::adopt(Character * recruit){
    recruit->secede();

    recruit->leader = this;
    recruit->next = NULL;
    recruit->prev = followers_tail;

    if (!followers_head){
        followers_head = recruit;
    } else
        followers_tail->next = recruit;
    followers_tail = recruit;

    return this;
}

// // Take an individual follower to be 
// Character * Character::adopt(Creature * pet){
//     pet->secede();

//     pet->leader = this;

//     pet->next = NULL;
//     pet->prev = pets_tail;

//     if (!pets_head){
//         pets_head = pet;
//     } else
//         pets_tail->next = pet;
//     pets_tail = pet;
    
//     return this;
// }

Character * Character::battle(Character * other){
    // Get a LLL of characters from each side
    // Order using postorder follower_tail, prev, root
    // This is meant to simulate sending lowest rank followers into battle first
    CharacterNode * defenders_head;

    // Build LLL of defending characters sequence
    defenders_head = other->get_battle_order();

    // Recursively attack 1 to 1 until offensive tree has all attacked
    // or end if reaches end of defenders list
    // In attack, if a vertex is defeated, take ownership of children leafs
    // vertexes cannot be captures
    // Benifit of having many direct reports as leaves is better defense, only direct report leaves contribute to defense in an attack
    attack(defenders_head);

    // Delete defenders LLL, but not the characters
}

CharacterNode * Character::attack(CharacterNode * enemies_head){
    CharacterNode * current_target = enemies_head;

    // Job done... You lucked out this time, buddy!
    if (!enemies_head) return;

    // This character sends next commrade to fight first, then sends followers second, then self

    // first sent next commrade to fight
    if (next)
        // Let the next guy attack current_target,
        // then update current_target to point at whover he reports is the next target
        current_target = next->attack(current_target);

    // after next commrade, send followers to fight
    if (followers_head)
        current_target = followers_head->attack(current_target);    

    // after next and followers have been sent, send self
    // Now that all delegation has been done, make this guy the next tail
    // Whoever is more powerful gets to make the call attack
    update_cmd_pwr(); // Update power because followers may have been defeated
    enemies_head->character->update_cmd_pwr();
    if (*this > *enemies_head->character){
        this->attack(enemies_head->character);
    } else {
        enemies_head->character->attack(this);
    }

    // Tell whover is above in stack to attack next target
    return current_target->next;
}

// Recursively attack 1 to 1 until offensive tree has all attacked
// or end if reaches end of defenders list
// In attack, if a vertex is defeated, take ownership of children leafs
// vertexes cannot be captures
// Benifit of having many direct reports as leaves is better defense, only direct report leaves contribute to defense in an attack
CharacterNode * Character::get_battle_order(CharacterNode* & tail_node){
    // Head node is the first to fight
    // Tail Node is the last to fight
    // Tail node should be the highest rank (root)
    // Head node should be the lowest rank (lowest of lowest follower)
    CharacterNode* this_node;
    CharacterNode* head_node = NULL;

    // Set up new node for this character
    // within scope of this call, this will always be appended as the tail node
    this_node = new CharacterNode;
    this_node->character = this;
    this_node->next = NULL;

    // This character sends next commrade to fight first, then sends followers second, then self

    // first sent next commrade to fight
    if (next)
        head_node = next->get_battle_order(tail_node);
    // after next commrade, send followers to fight
    if (followers_head)
        head_node = followers_head->get_battle_order(tail_node);
    // after next and followers have been sent, send self
    // Now that all delegation has been done, make this guy the next tail
    if (!tail_node) {
        tail_node = this_node;
    } else {
        tail_node->next = this_node;
    }

    // Base Case. If nobody lower, then return this as head
    // There can only be one returned for head of the whole alliance tree
    // Note, this is not root of the leadership tree, this is the first to attack.
    if (!head_node)
        head_node = this_node;
    
    return head_node;
}


CharacterNode * Character::get_battle_order(){
    CharacterNode* tail_node = NULL;
    return get_battle_order(tail_node);
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
bool Character::operator==(Character& other){
    update_cmd_pwr();
    other.update_cmd_pwr();
    return (this->cmd_pwr == other.cmd_pwr);
}

bool Character::operator==(const int val){
    update_cmd_pwr();
    return (this->cmd_pwr == val);
}

bool Character::operator!=(Character& other){
    update_cmd_pwr();
    other.update_cmd_pwr();
    return !(*this == other);
}

bool Character::operator!=(const int val){
    update_cmd_pwr();
    return !(*this == val);
}

bool Character::operator<(Character& other){
    update_cmd_pwr();
    other.update_cmd_pwr();
    return (this->cmd_pwr < other.cmd_pwr);
}

bool Character::operator<(const int val){
    update_cmd_pwr();
    return (this->cmd_pwr < val);
}

bool Character::operator>(Character& other){
    update_cmd_pwr();
    other.update_cmd_pwr();
    return (this->cmd_pwr > other.cmd_pwr);
}

bool Character::operator>(const int val){
    update_cmd_pwr();
    return (this->cmd_pwr > val);
}

bool Character::operator<=(Character& other){
    update_cmd_pwr();
    other.update_cmd_pwr();
    return (this->cmd_pwr <= other.cmd_pwr);
}

bool Character::operator<=(const int val){
    update_cmd_pwr();
    return (this->cmd_pwr <= val);
}

bool Character::operator>=(Character& other){
    update_cmd_pwr();
    other.update_cmd_pwr();
    return (this->cmd_pwr > other.cmd_pwr);
}

bool Character::operator>=(const int val){
    update_cmd_pwr();
    return (this->cmd_pwr > val);
}


// friend ostream& operator << (ostream&, const Character&){
//     return true;
// }

MainCharacter::MainCharacter(): Character("Masked", 6){
    is_privileged = true;
    cout << "In the mainchar constructor" << endl;
}

MainCharacter::MainCharacter(const char * name, const char * house, int self_pwr): Character(name, self_pwr){
    is_privileged = true;
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
Creature::Creature(const char * name, int self_pwr): Character(name, self_pwr){};
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
Horse::Horse(): Creature("Horsey", 8){}
const char* Horse::get_species() {return species;}
int Horse::eat(int energy){
    Creature::eat(energy);
}
int Horse::eat(Creature & prey){
    Creature::eat(prey);
}

char DragonEgg::species[7] = "Dragon";
DragonEgg::DragonEgg(): Creature("?????", 0){}
DragonEgg::DragonEgg(const char * name, int self_pwr): Creature(name, self_pwr){};
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
Dragon::Dragon(const char * name, int self_pwr): Creature(name, self_pwr){};
Dragon::Dragon(const DragonEgg & other): Creature(other) {
}
const char* Dragon::get_species() {return species;}
int Dragon::eat(int energy){
    Creature::eat(energy);
}
int Dragon::eat(Creature & prey){
    Creature::eat(prey);
}
