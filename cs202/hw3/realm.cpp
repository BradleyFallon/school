
#include "header.h"


Realm::Realm(): inhabitants_head(NULL), keeper_of_realm(NULL){
    Character* new_character = NULL;

    // A Character can be added to the realm and the pointer can be retained from return value
    Character* jimmy = add_character(new MainCharacter((char *)"Jimmy", (char *)"Flake", 20));

    // Character additions can be nested in adoptions
    // Adoptions cause the argument character to become a follower of the caller
    new_character = add_character(new MainCharacter((char *)"Flynn", (char *)"Stronk", 20));
    jimmy->adopt(new_character);

    // Adoptions can be made by using the += operator with a character or creature pointer
    // Jimmy really likes goats
    for (int i = 0; i<30; ++i){
        new_character = add_character(new Goat());
        jimmy->adopt(new_character);
        // Jimmy likes goats so much, he gains personal strength from their presence
        *jimmy += 1;
    }

    // A Character can be added to the realm and the pointer can be retained from return value
    Character* danise = add_character(new MainCharacter((char *)"Danise", (char *)"Dragonian", 20));
    new_character = add_character(new Dragon((char *)"Vesuvius", 300));
    danise->adopt(new_character);
    new_character = add_character(new Character((char *)"Gronk", 5));
    danise->adopt(new_character);

    danise->display();
}


// Was experimenting with arrays, decided to use an LLL
// Character * Realm::add_character(Character * new_character){
//     int new_size;
//     Character** temp;

//     if (index==0) {
//         size = 10;
//         inhabitants = new Character*[size];
//     } else if (index == size){
//         new_size = size * 2;
//         temp = new Character*[new_size];
//         for (int i = 0; i < size; ++i){
//             temp[i] = inhabitants[i];
//         }
//         delete [] inhabitants;
//         inhabitants = temp;
//     }
//     inhabitants[index] = new_character;
//     return new_character;
// }

Character * Realm::add_character(Character * new_character){
    CharacterNode* current = inhabitants_head;
    CharacterNode* this_node = new CharacterNode;
    this_node->character = new_character;
    this_node->next = NULL;
    if (!inhabitants_head){
        inhabitants_head = this_node;
    } else {
        while (current->next) current = current->next;
        current->next = this_node;
    }
    return new_character;
}

Character * Realm::leaderboard(){
    CharacterNode* current = inhabitants_head;
    while (current) {
        // only top level leaders can be keeper of he realm
        if (current->character->is_root()){
            // If no keeper, become keeper
            if (!keeper_of_realm)
                keeper_of_realm = current->character;
            // If greater than current keeper, become keeper
            else if (*(current->character) > *keeper_of_realm){
                keeper_of_realm = current->character;
            }
        }
        current = current->next;
    }
    if (!keeper_of_realm) return NULL;
    cout << ".oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.\n\n"
        <<  "     Behold, Ye Keeper of Ye Realm:\n\n";
    keeper_of_realm->display();
    cout << "     May Ye reignf of thine reign be lengthy," << "\n"
        <<  "        thy rainf be wet," << "\n"
        <<  "            and thine thighf clap loud with thickneff." << "\n\n"
        << ".oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.\n" << endl;
    return keeper_of_realm;
}

// Character * Realm::treaty(Character * leader_a, Character * leader_b){
//     if (leader_a > leader_b)
//             penalty();
//         return leader_a;
    
//     return leader_b;
// }

// Character * Realm::battle(Character * leader_a, Character * leader_b){
//     if (leader_a > leader_b)
//             penalty();
//         return leader_a;
    
//     return leader_b;
// }