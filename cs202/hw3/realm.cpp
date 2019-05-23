
#include "header.h"


Realm::Realm(): inhabitants_head(NULL), keeper_of_realm(NULL){
}


// Was experimenting with arrays, decided to use an LLL
// Character * Realm::update_population(Character * new_character){
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

CharacterList::CharacterList(Character * character): next(NULL){
    this->character = character;
}

CharacterList::CharacterList(): character(NULL), next(NULL) {}

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
    if (!inhabitants_head) {
        inhabitants_head = new CharacterList(new_character);
    } else {
        inhabitants_head->append(new_character);
    }
    return new_character;
}

CharacterList * Realm::update_population(CharacterList * new_characters){
    if (!inhabitants_head) {
        inhabitants_head = new_characters;
    } else {
        inhabitants_head->append(new_characters);
    }
    return inhabitants_head;
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
}

Character * Realm::leaderboard(){
    if (inhabitants_head){
        keeper_of_realm = inhabitants_head->get_top();
    } else
        keeper_of_realm = NULL;
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


Story::Story(): Realm(){
    Character* new_character = NULL;

    // A Character can be added to the realm and the pointer can be retained from return value
    Character* jimmy = update_population(new MainCharacter("Jimmy", "Flake", 20));

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
    Character* danise = update_population(new MainCharacter("Danise", "Dragonian", 20));
    new_character = update_population(new Dragon("Vesuvius", 300));
    danise->adopt(new_character);
    new_character = update_population(new Character("Gronk", 5));
    danise->adopt(new_character);

    danise->display();


    Paragraph * new_paragraph = NULL;
    CharacterList * new_characters = NULL;
    Character * new_enemy = NULL;

    new_paragraph = new Paragraph(
        new_characters,
        "Welcome to the Ralm of Dragonlore.",
        new_enemy,
        false
    );
}

bool Story::read_next_paragraph(Character * hero, Character * keeper){
    if (!next_paragraph) return false;
    update_population(next_paragraph->get_new_characters());
    next_paragraph = next_paragraph->interact_user(hero, keeper);
};

Paragraph::Paragraph(): battle_target(NULL), text(NULL), next_win(NULL),
    next_fail(NULL), characters_list(NULL), fight_the_keeper(false) {}

Paragraph::Paragraph(CharacterList * new_characters, const char* new_text, Character * target, bool do_battle): Paragraph(){
    characters_list = new_characters;
    text = new char[strlen(new_text) + 1];
    strcpy(text, new_text);
}

int Paragraph::get_user_input(){
    int option = 0; // The number of the chosen option
    bool failed = false; // Tracks if the user has alread failed to get option

    while (!(option >=1 && option <= 5))
    {
        // After first try, print failed Term
        if (failed)
        {
            cout << "Invalid response. Please try again..." << endl;
        }
        failed = true;
        // Give instructions and get response
        cout << "\n\nWhat wouldst thou doth?" << "\n"
            << "1: Display mine power." << "\n"
            << "2: Proceed with Ye story." << "\n";
        if (battle_target){
            cout << "3: Battle with thy present foe." << "\n"
                << "4: Forbear conflict with thy present foe." << "\n";
        if (characters_list) cout << "5: Assay to compose alliance with thy company." << "\n"
            << "\nEnter a number to enjoy an option." << "\n"
            << endl;
        if (!(cin >> option)){
            cin.clear();
            cin.ignore();
            option = 0;
        } else
        cin.ignore(SIZE_SMALL, '\n');
    }
    return option;
}


Paragraph * Paragraph::interact_user(Character * hero, Character * keeper){
    // display options and execute commands
    int option;

    option = get_user_input();
    Paragraph * next_paragraph = NULL;

    switch (option)
    {
        case 1: // Display followers
            break;
        case 2: // Take path of least resistance or continue
            break;
        default: // code to be executed if n doesn't match any cases
    }

    return next_paragraph;
}

// If new characters are added to the realm, return them and the story
// will deal with adding to realm list
CharacterList * Paragraph::get_new_characters(){
    return characters_list;
}

Paragraph * Paragraph::connect_next_win(Paragraph * next_paragraph){
    next_win = next_paragraph;
}

Paragraph * Paragraph::connect_next_fail(Paragraph * next_paragraph){
    next_fail = next_paragraph;
}

