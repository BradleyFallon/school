
#include <iostream>
using namespace std;



void add_item_to_grade(float item_value, bool is_graded, char item_name[], float my_grade)
{
    float pcnt_earned = 0.0;

    item_value = 0.05;
    if (is_graded)
    {
        cout << "If " << item_name << " has been graded, please enter your score as a percentage (e.g. 92.5)." << endl;
        cin >> pcnt_earned;
        cout << "You entered: " << pcnt_earned << endl;
        if (pcnt_earned)
        {
            my_grade += pcnt_earned * item_value;
            return;
        }
        is_graded = false;
    }
    my_grade += 100.0 * item_value;
    return;
}


int main(){

    char HW1[] = {'H', 'W', '1', '\0'};
    char HW2[] = {'H', 'W', '2', '\0'};
    char HW3[] = {'H', 'W', '3', '\0'};
    char HW4[] = {'H', 'W', '4', '\0'};
    char HW5[] = {'H', 'W', '5', '\0'};

    float my_grade = 0.0;

    float pcnt_earned = 0.0;   // This is where we track the points earned. Each percentage is worth 1.
    float item_value = 0.0;    // This is where we track the current assignments portion of the final grade as decimal.
    bool is_graded = true;     // To track if we have gone beyond which assignments have been graded and to stop prompts.

    add_item_to_grade(
        0.5,
        is_graded,
        HW1,
        my_grade
        );
    add_item_to_grade(
        0.5,
        is_graded,
        HW2,
        my_grade
        );
    add_item_to_grade(
        0.5,
        is_graded,
        HW3,
        my_grade
        );
    add_item_to_grade(
        0.5,
        is_graded,
        HW4,
        my_grade
        );
    add_item_to_grade(
        0.5,
        is_graded,
        HW5,
        my_grade
        );



    return 0;
}