/*
================================================================================
Homework 3 for CS202
Bradley Fallon
bfallon@pdx.edu
5/24/2019

This file is the mega-header that contains all constants and prefabs for all classes
================================================================================
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>  // for rand()

using namespace std;

const int SIZE_SMALL = 64;
// Was going to be used for reading story from file, but didn't get there
const int SIZE_LARGE = 1024;


/*
To Do

Destructors and memory tests

        // This destructor should deallocate self and all following, 
        // but NOT the characters. That is only to be done explicitly.
        xxxxx ~CharacterList();
        xxxxx CharacterList::delete_characters_all();
        xxxxx CharacterList::delete_character();

        // Deallocate all characters, then deallocate lists
        xxxxx ~Realm();

        // If character list is still populated, delete all characters then delete list
        xxxxx ~Paragraph();

        // Destroy all paragraphs
        xxxxx ~Story();

        xxxxx virtual ~Character();
        xxxxx ~MainCharacter();

replace all delete characters with kill() which sets is_alive to false.

xxxxx headings

Constants in operators

xxxxx writeups

story dev
*/



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
Best of luck on your endeavors adventurer.
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
class Story; // Is a Realm

class Character;
class MainCharacter;
class Creature;
class Goat;
class Horse;
class Dragon;
class DragonEgg;


class CharacterList{
    public:
        CharacterList();
        CharacterList(Character * character);
        // This destructor should deallocate self and all following, 
        // but NOT the characters. That is only to be done explicitly.
        ~CharacterList();
        void delete_characters_all();
        void delete_character();
        Character * append(Character * to_add);
        CharacterList * append(CharacterList * to_add);
        Character * get_top();
        Character * get_ptr();
        CharacterList * get_next();
    protected:
        void get_top(Character * & current_best);
        Character * character;
        CharacterList * next;
};

class Realm {
    public:
        Realm();
        // Deallocate all characters, then deallocate lists
        ~Realm();
        // Display the most powerful leaders of the realm and their follower info
        Character * leaderboard();
        int pledge(Character * & leader_hi, Character * & leader_low);
        int treason(Character * & traitor);
    protected:
        Character * update_population(Character *);
        CharacterList * update_population(CharacterList *);
        // The entire population of the realm is tracked here, independent of
        // social standing and relationships.
        // Character ** inhabitants;
        // int index;
        // int size;
        CharacterList * inhabitants_head;

        // The single inhabitant with the greatest cmd_pwr is the keeper of
        // the realm. Commanding power is the sum of self power and all followers
        // recursively. A wizard or dragon may have greater power than an army,
        // so population alone does not make a character the keeper of the realm.
        Character * keeper_of_realm;
    private: 
};

class Paragraph{
    
    public:
        Paragraph();
        Paragraph(const char* new_text, Character * target, bool do_battle);
        Paragraph(CharacterList * new_characters, const char* new_text, Character * target, bool do_battle);
        // If character list is still populated, delete all characters then delete list
        ~Paragraph();
        // display options and execute commands
        // leaderboard
        // display following
        // continue win
        // continue fail
        // battle
        // treaty
        Paragraph * interact_user(Character * hero, Character * keeper);
        // If new characters are added to the realm, return them and the story
        // will deal with adding to realm list
        CharacterList * get_characters_list();
        Paragraph * connect_next_win(Paragraph * next_paragraph);
        Paragraph * connect_next_fail(Paragraph * next_paragraph);
    private:
        Character * battle_target;
        char * text;
        // Instead of left/right, I am calling these win/fail so that
        // it is obvious what convention is for winning and losing battles etc.
        Paragraph * next_win; 
        Paragraph * next_fail;
        CharacterList * characters_list;
        bool fight_the_keeper;

        int get_user_input();
};

// This is a protected derivation because we want to hide the inner workings from the client.
// The Story class creates a guided interaction rather than an open ended experiment.
class Story: protected Realm {
    public:
        Story();
        // Destroy all paragraphs
        ~Story();
        // displays the nexet paragraph and returns 0 if end of story, else 1
        bool read_next_paragraph();
    private:
        Character * hero;
        Paragraph * paragraphs_root;
        Paragraph * next_paragraph;
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
All of the comparisons will use integer comparison upon the cmd_pwr
after both RHS and LHS have been updated. This can be also used with an integer
and only the Character will be updated and cmd_pwr compared with the int.
*/
class Character {
    public:
        Character();
        Character(const char * name, int self_pwr);
        Character(const Character &);
        virtual ~Character();

        void display();
        int secede();
        // Check if this is root of a tree
        bool is_root();
        // Take an individual follower to be 
        Character * adopt(Character * other);
        Character * adopt_followers(Character * recruiter);
        // Character * adopt(Creature * other);
        Character * battle(Character * other);
        CharacterList * get_battle_order();
        CharacterList * get_battle_order(CharacterList* & tail_node);
        CharacterList * attack(CharacterList * enemies_head);
        bool attack(Character * enemy);
        int strike();

        // I am trying to improve runtime efficiency by deciding when it is necessary to refresh
        // It would be intensive to recursively calculate cmd power with every comparison
        // Update the power rating of self and all followers
        int update_cmd_pwr();

        //The LHS becomes an exact deepcopy of the RHS.
        Character& operator = (const Character&);
        // The result of adding characters, is the LHS character copied and gaining
        // the RHS followers. This does not affect the LHS and RHS, it creates a copy.
        int operator + (const Character&) const;
        // If a int is added to a character, the result is the gains the int to self power.
        int operator + (const int) const;
        // The character on the LHS inherits all rights and followers of the RHS.
        // Name and any identification info is not affected.
        Character& operator += (const Character&);
        // To adopt a character as a follower
        Character* operator+= (Character* other);
        // The character gains power equal to the int.
        Character& operator += (const int);

        /*
        ( [] )
        This will recursively fetch the follower of the nth position.
        Followers are sorted by head being the oldest and most trusted.
        */
        Character& operator [] (int);

        bool operator == (Character&);
        bool operator == (const int);
        bool operator != (Character&);
        bool operator != (const int);
        bool operator < (Character&);
        bool operator < (const int);
        bool operator > (Character&);
        bool operator > (const int);
        bool operator <= (Character&);
        bool operator <= (const int);
        bool operator >= (Character&);
        bool operator >= (const int);
        
        friend ostream & operator << (ostream &, const Character &);
        friend istream & operator >> (istream &, Character &);

    protected:
        // Name is remained as NULL for some characters if they are not important as individual to story
        char * name;
        // The power of this individual regardless of followers
        int self_pwr;
        // The result sum of personal power and recursive sum of all followers
        int cmd_pwr;
        
        Character * leader;
        // This is the highest rank follower, which is probably
        Character * followers_head;
        Character * followers_tail;
        // Creature * pets_head;
        // Creature * pets_tail;
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


        // Return the power of self plus all lesser commrades
        int rally_power();
        // Displays name, without endl. For recursion or inline insertion in cout
        virtual void display_name();
        // Displays all commrades names
        int display_rally();

    private:
};

class MainCharacter: public Character {
    public:
        MainCharacter();
        MainCharacter(const char * name, const char * house, int self_pwr);
        ~MainCharacter();
        // void display();
    protected:
        char * house;
        void display_name();
    private:
};

class Creature: public Character {
    public:
        Creature();
        Creature(const char * name, int self_pwr);
        Creature(const Creature &);
        // will attempt to delete a character and consume its calories,
        // not possible if power of other is higher than self.
        virtual int eat(Creature &);
        virtual int eat(int);
    protected:
        // The amount of energy a creature has, dies if 0
        // Higher energy may enable special features of derived classes
        int energy;
        // If a creature is consumed, it can provide this much energy
        int calories;
        // This is the weight capacity a creature can support for cargo/rider
        int mount_capacity;
        virtual const char* get_species() = 0;
        void display_name();
    private:
};

// This is a private creature because it is to be controlled by an owner
class Goat: public Creature {
    public:
        Goat();
        int eat(Creature &);
        int eat(int);
    protected:
        static char species[];
    private:
        // This spawns another goat, requires and consumes energy
        Goat * produce_offspring();
        const char* get_species();
};

class Horse: public Creature {
    public:
        Horse();
        int eat(Creature &);
        int eat(int);
    protected:
        static char species[];
    private:
        // This spawns another Horse, requires and consumes energy
        Horse * produce_offspring();
        const char* get_species();
};


class Dragon: public Creature {
    public:
        Dragon();
        Dragon(const char * name, int self_pwr);
        Dragon(const DragonEgg &);
        // This may destroy target and friends depending on energy levels
        int incinerate(Character * & target);
        // If a dragon is fed enough, it may lay an egg
        int eat(Creature &);
        int eat(int);
    protected:
        static char species[];
    private:
        DragonEgg * lay_egg();
        const char* get_species();
        
};

class DragonEgg: public Creature {
    public:
        int eat(Creature &); // always fails, cannot eat
        int eat(int);
    protected:
        static char species[];
    private:
        DragonEgg();
        DragonEgg(const char * name, int self_pwr);
        // When heated, the egg may hatch if the energy has surpassed threshold
        Dragon * hatch();
        const char* get_species();
};



/*
PRESS ENTER TO CONTINUE...
0. continue
1. Treaty with goat
2. fight goat
3. Scream

"Roooooar"
"What in he bloody seven hells was that?" Jimmy exclaimed.
"Meh." (goat).
"Whoosh... Whoosh... Whoosh..." (dragon).
"Almighty seven, old and new, thats a bloody Dragon!".
"Meh." (goat)

PRESS ENTER TO CONTINUE...
0. continue
1. Treaty with goat
2. fight goat
3. Scream


The caravan guards fight in vain as they are burned and swallowed by the dragon.
The dragon roasts and devours the horse heading Jimmy's cart, 
but miraculously, Jimmy's goat cart rolls down a hill, through the woods and
comes to a stop safely in a meadow four miles away.

PRESS ENTER TO CONTINUE...

After the pain and exhaustion become unbarable, he gives up and watches
the goats as the graze in the meadow. As night falls, Jimmy and the goats
pile together for warmth under the stars.

PRESS ENTER TO CONTINUE...

"What in the bloody seven hells is this?" a voice called out.
Jimmy is awoken by a rider on horse.
"What are you doing farming goats in my meadow? Boy!".
"Uncle Flynn? Is that you?" Jimmy croaked.
"Jimmy boy?!?!? What have you gotten yourself into, your'e all tied up!"
Uncle Flynn breaks Jimmys bonds.
"Thanks uncle Flynn, you're the best!".
"Well, start talking boy..."
"I can't remember, I was being help prisoner with these goats..."
Jimmy explained the story up to this point to Uncle Flynn.

PRESS ENTER TO CONTINUE...

"Oh yeah, now I remember! I was on my way to go tell the dragon queen that I
am her older brother's son. Then, as I was on my way, the Queen of the Realm's 
patrols captured me."
"What are you on about, you're my brother's bastard boy!"
"Yeah, well actually no, I'm like really super royal blooded."
"Alright then, well let's band together an army and take over the realm."
"It is my birthright!"
"It is your birthright!"
"Meh!" (goat)

PRESS ENTER TO CONTINUE...

"How do you suppose we rise up to command the most powerful army in the realm."
Uncle Flynn pondered aloud.
Jimmy scratched his head. One of the goats layed its head upon Jimmy's lap.
"Meh" the goat bleated.
"Well... Looks like you've got yourself a loyal army of goats!"
"Hahahahahahahaha" Jimmy laughed. "Looks like I do, dont I uncle Flynn!".
"Hahahahahahahahahahahahahaha, you sure do boy!".
"meh." (goat)

*/