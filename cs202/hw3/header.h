#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

/*
This is a text adventure game. It is very simple. Your hero is an up and coming 
dragon trainer. The user reads a paragrah at a time of the story. The User
makes decisions of how much to feed their dragon and makes judgement calls
to make alliances and engage in battles. The goal of the game is to become the
keeper of the realm. To become the keeper of the realm, you must achieve the
highest commanding power of any being of existance in the realm. To gain 
commanding power, you build a hierarchy of followers. In addition, you can 
increase your own personal power and the power of your pets. 
One strategy to win could be to train a dragon to be stronger than the 
greatest leader of the realm. Another strategy could be to take out other
leaders and take control by inspiring their followers to convert to your cause.
Best of luck on your endeavors adveneturer.
*/

// If a hero is imminent danger, they may recieve this blessing power
const int HERO_BLESSING = 5000;
// If a privileged named character is imminent danger, they may recieve this blessing power
// (e.g. wealthy attractive english speaking support characters)
const int PRIVILEGE_BLESSING = 1000;
// If a named character is imminent danger, they may recieve this blessing power
const int NAMED_BLESSING = 200;
// Threshold power to trigger blessing.
const int BLESSINGS_THRESHOLD = 50;

class Realm;
class Story;
class Character;
class MainCharacter;
class Creature;
class Goat;
class Horse;
class Dragon;
class DragonEgg;

class Realm {
    public:
        Realm();
        // Display the most powerful leaders of the realm and their follower info
        void display_top();
        // Cause two leaders to battle, a characterer to victor is returned
        Character * battle(Character * & leader_a, Character * & leader_b);
        int pledge(Character * & leader_hi, Character * & leader_low);
        int treason(Character * & traitor);
    protected:
        // The entire population of the realm is tracked here, independent of
        // social standing and relation ships. This is a dynamic array which 
        // will be taking inspiration from python list implementation. This means
        // it will be an array that will reallocate and copy to a new larger array
        // whenever full. The size increase is a function of old size. As population
        // dies off, the array may be reallocated to a smaller size.
        Character * inhabitants[];
        // The single inhabitant with the greatest commanding_power is the keeper of
        // the realm. Commanding power is the sum of self power and all followers
        // recursively. A wizard or dragon may have greater power than an army,
        // so population alone does not make a character the keeper of the realm.
        Character * keeper_of_realm;
    private: 
};

// This is a protected derivation because we want to hide the inner workings from the client.
// The Story class creates a guided interaction rather than an open ended experiment.
class Story: protected Realm {
    public:
        Story();
        // displays the nexet paragraph and returns 0 if end of story, else 1
        int read_next_paragraph();
    private:
        Character * hero;
};

/*
A character is a node of a tree.
The characters have a single leader and a list of followers.
( = )
The LHS becomes an exact deepcopy of the RHS.
( + ) (character)
The result of adding characters, is the LHS character copied and gaining
the RHS followers. This does not affect the LHS and RHS, it creates a copy.
( + ) (int)
If a int is added to a character, the result is the 
LHS character adopts the followers of the RHS.
( ++ ) (pre-increment)
Add one character to the character's power.
( += ) (character)
The character on the LHS inherits all rights and followers of the RHS.
Name and any identification info is not affected.
( += ) (int)
The character gains power equal to the int.
( [] )
This will recursively fetch the follower of the nth position.
Followers are sorted by head being the oldest and most trusted.
( == ) (int, Character)
( != ) (int, Character)
( >, >= ) (int, Character)
( <, <= ) (int, Character)
All of the comparisons will use integer comparison upon the commanding_power
after both RHS and LHS have been updated. This can be also used with an integer
and only the Character will be updated and commanding_power compared with the int.
*/
class Character {
    public:
        Character();
        virtual ~Character();

        void display();
        // Take an individual follower to be 
        int adopt(Character *);

        //The LHS becomes an exact deepcopy of the RHS.
        Character& operator = (const Character&);
        // The result of adding characters, is the LHS character copied and gaining
        // the RHS followers. This does not affect the LHS and RHS, it creates a copy.
        Character  operator + (const Character&) const;
        // If a int is added to a character, the result is the gains the int to self power.
        Character  operator + (const int) const;
        // The character on the LHS inherits all rights and followers of the RHS.
        // Name and any identification info is not affected.
        Character& operator += (const Character&);
        // The character gains power equal to the int.
        Character& operator += (const int);

        /*
        ( [] )
        This will recursively fetch the follower of the nth position.
        Followers are sorted by head being the oldest and most trusted.
        */
        Character& operator [] (int);

        /*
        ( == ) (int, Character)
        ( != ) (int, Character)
        ( >, >= ) (int, Character)
        ( <, <= ) (int, Character)
        */
        bool operator == (const Character&)const;
        bool operator == (const int)const;
        bool operator != (const Character&)const;
        bool operator != (const int)const;
        bool operator < (const Character&)const;
        bool operator < (const int)const;
        bool operator > (const Character&)const;
        bool operator > (const int)const;
        bool operator <= (const Character&)const;
        bool operator <= (const int)const;
        bool operator >= (const Character&)const;
        bool operator >= (const int)const;
        
        // friend ostream& operator << (ostream&, const Character&);

        // Recursively sum power of all followers and update commanding_power
        // Main characters get an even greater blessing
        virtual int update_commanding_power();

    protected:
        // Name is remained as NULL for some characters if they are not important as individual to story
        char * name;
        // The power of this individual regardless of followers
        int personal_power;
        // The result sum of personal power and recursive sum of all followers
        int commanding_power;
        // The higher this property, the less likely to change sides in face of defeat
        int loyalty;
        Character * leader;
        // This is the highest rank follower, which is probably
        Character * followers_head;
        Creature * pets_head;
        // Characters have a next and prev so that they can independently
        // change teams without the command of their leader. Otherwise the leader
        // would need to command traversal in order to give away followers.
        // If prev is NULL, then this is a top rank follower, and leaving is not
        // so easy. A head follower simply deciding to change teams would cause
        // much confusion in the realm (see Jamie Lannister).
        Character * next;
        Character * prev;


        // Named characters get a blessing to personal power whenever their
        // commanding power is significantly low. Change the configuration constant
        // vlaues to adjust the intensity of this feature. For a JR Tolkien realm, 
        // this feature should be so intense that it is virtually impossible for
        // a named character to perish. For a GRR Martin realm this is almost negligible
        // unless adapted to television. This blessing is more significant for privileged characters.
        bool is_privileged;

    private:
};

class MainCharacter: public Character {
    public:
        MainCharacter();
        ~MainCharacter();
        void display();
        int update_commanding_power();
    protected:
        
    private:
};

class Creature: public Character {
    public:
        Creature();
        // will attempt to delete a character and consume its calories,
        // not possible if power of other is higher than self.
        int eat(Creature *);
    protected:
        // The amount of energy a creature has, dies if 0
        // Higher energy may enable special features of derived classes
        int energy;
        // If a creature is consumed, it can provide this much energy
        int calories;
        // This is the weight capacity a creature can support for cargo/rider
        int mount_capacity;
    private:
};

// This is a private creature because it is to be controlled by an owner
class Goat: private Creature {
    public:
        // This spawns another goat, requires and consumes energy
        Goat * produce_offspring();
    protected:
    private:
};

class Horse: private Creature {
    public:
        Horse();
        // This spawns another Horse, requires and consumes energy
        Horse * produce_offspring();
    protected:
    private:
};

class Dragon: public Creature {
    public:
        Dragon();
        // This may destroy target and friends depending on energy levels
        int incinerate(Character * & target);
        // If a dragon is fed enough, it may lay an egg
        DragonEgg * eat();
    protected:
    private:
        DragonEgg * lay_egg();
};

class DragonEgg: protected Dragon {
    public:
        DragonEgg();
        Dragon * heat();
    protected:
    private:
        // When heated, the egg may hatch if the energy has surpassed threshold
        Dragon * hatch();
};


