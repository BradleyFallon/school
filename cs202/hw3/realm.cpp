
#include "header.h"


Realm::Realm(){
    inhabitants_head = NULL;
    size = 0;
    index = 0;


    // A Character can be added to the realm and the pointer can be retained from return value
    Character* jimmy = add_character(new MainCharacter("Jimmy", "Flake", 20));

    // Character additions can be nested in adoptions
    // Adoptions cause the argument character to become a follower of the caller
    jimmy->adopt(
        add_character(new MainCharacter("Flynn", "Stronk", 20))->adopt(
            add_character(new MainCharacter("Flynn", "Stronk", 20))
        )
    );

    // Adoptions can be made by using the += operator with a character or creature pointer
    // Jimmy really likes goats
    for (int i = 0; i<30; ++i){
        jimmy->adopt(add_character(new Goat()));
        // Jimmy likes goats so much, he gains personal strength from their presence
        jimmy += 1;
    }

    // A Character can be added to the realm and the pointer can be retained from return value
    Character* danise = add_character(new MainCharacter("Danise", "Dragonian", 20));
    danise->adopt(
        add_character(new Character("Gronk", 5))
        );
    danise->adopt(
        add_character(new Dragon("Vesuvius", 300))
        );

    
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
        if (*(current->character) > *keeper_of_realm){
            keeper_of_realm = current->character;
        }
    }
    cout << ".oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.\n\n"
        <<  "     Behold, Ye Keeper of the Realm:\n\n";
    keeper_of_realm->display();
    cout << "     May thine reign be long," << "\n"
        <<  "        thy rains be wet," << "\n"
        <<  "            and thine thighs clap loud with thickness." << endl;
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