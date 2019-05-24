/*
================================================================================
Homework 3 for CS202
Bradley Fallon
bfallon@pdx.edu
5/24/2019

This file contains the implementations of all non-Character classes
================================================================================
*/
#include "header.h"


Realm::Realm(): inhabitants_head(NULL), keeper_of_realm(NULL){
}

Realm::~Realm(){
    if (inhabitants_head){
        inhabitants_head->delete_characters_all();
        delete inhabitants_head;
    }
}

CharacterList::CharacterList(Character * character): next(NULL){
    this->character = character;
}

CharacterList::CharacterList(): character(NULL), next(NULL) {}

CharacterList::~CharacterList(){
    // recursively deletes all
    // The characters must be deleted separately, because there are multiple
    // data structures that reference the same character data
    if (next) delete next;
}

void CharacterList::delete_characters_all(){
    delete_character();
    if (next) next->delete_characters_all();
}

void CharacterList::delete_character(){
    delete character;
    character = NULL;
}

Character * CharacterList::append(Character * to_add){
    CharacterList * new_node = new CharacterList(to_add);
    append(new_node);
    return to_add;
}

CharacterList * CharacterList::append(CharacterList * to_add){
    if (next) next->append(to_add);
    else
        next = to_add;
        to_add->next = NULL;
    return this;
}

Character * Realm::update_population(Character * new_character){
    if (new_character){
        if (!inhabitants_head) {
            inhabitants_head = new CharacterList(new_character);
        } else {
            inhabitants_head->append(new_character);
        }
    }
    return new_character;
}

CharacterList * Realm::update_population(CharacterList * new_characters){
    if (!new_characters) return new_characters;
    if (!inhabitants_head) {
        inhabitants_head = new_characters;
    } else {
        inhabitants_head->append(new_characters);
    }
    return new_characters;
}

CharacterList * CharacterList::get_next(){
    return next;
}

Character * CharacterList::get_ptr(){
    return character;
}

Character * CharacterList::get_top(){
    Character * current_best = NULL;
    get_top(current_best);
    return current_best;
}

void CharacterList::get_top(Character * & current_best){
    if (character->is_root()){
        // If no keeper, become keeper
        if (!current_best)
            current_best = character;
        // If greater than current keeper, become keeper
        else if (*character > *current_best){
            current_best = character;
        }
    }
    if (next)
        next->get_top(current_best);
}

Character * Realm::leaderboard(){
    if (inhabitants_head){
        keeper_of_realm = inhabitants_head->get_top();
    } else
        keeper_of_realm = NULL;
    if (!keeper_of_realm) return NULL;

    cout << ".oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.\n\n"
        <<  "     BEHOLD, Ye KEEPER OF Ye REALM:\n\n";
    keeper_of_realm->display();
    cout << "     May the reigns of thine reign be lengthy," << "\n"
        <<  "        thy rains be wet," << "\n"
        <<  "            and thine thighs clap loud with thickness." << "\n\n"
        << ".oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.\n" << endl;

    return keeper_of_realm;
}

// Character * Realm::treaty(Character * leader_a, Character * leader_b){
//     if (leader_a > leader_b)
//             penalty();
//         return leader_a;
    
//     return leader_b;
// }


Story::Story(): Realm(){
    Character* new_character = NULL;

    Character * jimmy;
    Character * danise;
    Character * kahuna_dodo;

    

    // A Character can be added to the realm and the pointer can be retained from return value
    jimmy = update_population(new MainCharacter("Jimmy", "Flake", 20));
    hero = jimmy;

    // Character additions can be nested in adoptions
    // Adoptions cause the argument character to become a follower of the caller
    new_character = update_population(new MainCharacter("Flynn", "Stronk", 20));
    new_character->adopt(update_population(new Horse()));
    jimmy->adopt(new_character);

    // Adoptions can be made by using the += operator with a character or creature pointer
    // Jimmy really likes goats
    for (int i = 0; i<30; ++i){
        new_character = update_population(new Goat());
        jimmy->adopt(new_character);
        // Jimmy likes goats so much, he gains personal strength from their presence
        *jimmy += 1;
    }

    jimmy->display();
    

    // A Character can be added to the realm and the pointer can be retained from return value
    danise = update_population(new MainCharacter("Danise", "Dragonian", 20));
    new_character = update_population(new Dragon("Vesuvius", 300));
    danise->adopt(new_character);
    new_character = update_population(new MainCharacter("Jerpuh", "Morningmouth", 30));
    danise->adopt(new_character);
    new_character = update_population(new Character("Mistyday", 1));
    danise->adopt(new_character);
    new_character = update_population(new Character("Ash-maggot", 15));
    danise->adopt(new_character);
    for (int i = 0; i<30; ++i){
        new_character->adopt(update_population(new Character("Never-giggle", 12)));
    }
    danise->display();

    kahuna_dodo = update_population(new MainCharacter("Kuhuna", "DoDo", 25));
    kahuna_dodo->adopt(new Horse());
    for (int i = 0; i<30; ++i){
        kahuna_dodo->adopt(
            update_population(new Character("Blood Rider", 9))->adopt(
                update_population(new Horse())
            )
        );
    }
    kahuna_dodo->display();

    Paragraph * new_paragraph = NULL;
    CharacterList * new_characters = NULL;
    Character * new_enemy = NULL;

    paragraphs_root = new Paragraph(
        "Welcome to the Ralm of Dragonlore.",
        new_enemy,
        false
    );
    next_paragraph = paragraphs_root;
    cout << next_paragraph;
}

Story::~Story(){
    if (paragraphs_root) delete paragraphs_root;
}

bool Story::read_next_paragraph(){
    CharacterList * new_characters = NULL;
    leaderboard();
    if (!next_paragraph){
        cout << "And thus the story concludes." << endl;
        return false;
    }
    cout << "next paragraph " << endl;
    cout << next_paragraph << endl;
    new_characters = next_paragraph->get_characters_list();
    cout << new_characters << endl;
    if (new_characters)
        update_population(new_characters);
    next_paragraph = next_paragraph->interact_user(hero, keeper_of_realm);
    return true;
};

Paragraph::Paragraph(): battle_target(NULL), text(NULL), next_win(NULL),
    next_fail(NULL), characters_list(NULL), fight_the_keeper(false) {}

Paragraph::Paragraph(const char* new_text, Character * target, bool do_battle):
    next_win(NULL), next_fail(NULL), characters_list(NULL), fight_the_keeper(false){
    cout << " in the paragraph constructor" << this << endl;
    text = new char[strlen(new_text) + 1];
    strcpy(text, new_text);
}

Paragraph::Paragraph(CharacterList * new_characters, const char* new_text, Character * target, bool do_battle){
    characters_list = new_characters;
    text = new char[strlen(new_text) + 1];
    strcpy(text, new_text);
}

Paragraph::~Paragraph(){
    if (characters_list){
        characters_list->delete_characters_all();
        delete characters_list;
    }
    if (text) delete [] text;
    // Recursively delete following
    if (next_fail) delete next_fail;
    if (next_win) delete next_win;
}

int Paragraph::get_user_input(){
    int option = 0; // The number of the chosen option
    bool failed = false; // Tracks if the user has alread failed to get option

    do {
        // After first try, print failed Term
        if (failed) {
            cout << "Invalid response. Please try again..." << endl;
        }
        failed = true;
        // Give instructions and get response
        cout << "\n\nWhat wouldst thou doth?" << "\n"
            << "1: Display mine power." << "\n";

        if (battle_target || fight_the_keeper){
            cout << "2: Forbear conflict with thy present foe." << "\n"
                << "3: Battle with thy present foe." << "\n";
        } else
            cout << "2: Proceed with the story." << "\n";

        if (characters_list) cout << "4: Assay to compose alliance with thy company." << "\n";
        cout << "\nEnter a number to enjoy an option." << "\n"
            << endl;

        if (!(cin >> option)){
            cin.clear();
            cin.ignore();
            option = 0;
        } else
        cin.ignore(SIZE_SMALL, '\n');
    } while (!(option >=1 && option <= 4));
    return option;
}

Paragraph * Paragraph::interact_user(Character * hero, Character * keeper){
    // display options and execute commands
    int option;

    cout << "HELLO" << endl;

    option = get_user_input();
    Paragraph * next_paragraph = NULL;

    

    while (next_paragraph==NULL){
        if (option==1) { // Display followers
                hero->display();
                next_paragraph = this;
        } else if (option=2) { // Take path of least resistance or continue
                if (next_fail){
                    cout << "Our hero hast taken the path of the coward." << "\n"
                        << "Nay blood wast shed this present day." << endl;
                    next_paragraph = next_fail;
                }
                else
                    next_paragraph = next_win;
        } else if (option=3) { // Battle with target
                next_paragraph = next_win; // default
                if (fight_the_keeper)
                    if (!hero->battle(keeper)) next_paragraph = next_fail;
                else if (battle_target)
                    if (hero->battle(battle_target)) next_paragraph = next_fail;
                else 
                    cout << "Our hero shouts fiercly into the vacant distance." << endl;
                    option = 2;
        } else if (option=4) { // Treaty with other head
                cout << "Not implemented. Proceeding with story." << endl;
                option = 2;
        } else {// code to be executed if n doesn't match any cases
                cout << "The realm is experiencing etchnical difficulties." << endl;
                option = 3;
        }
        if (next_paragraph == this){
            next_paragraph = interact_user(hero, keeper);
        }
        if (!next_win) return NULL;
    }
    return next_paragraph;
}

// If new characters are added to the realm, return them and the story
// will deal with adding to realm list
CharacterList * Paragraph::get_characters_list(){
    cout << text << endl;
    return NULL;
}

Paragraph * Paragraph::connect_next_win(Paragraph * next_paragraph){
    next_win = next_paragraph;
}

Paragraph * Paragraph::connect_next_fail(Paragraph * next_paragraph){
    next_fail = next_paragraph;
}

