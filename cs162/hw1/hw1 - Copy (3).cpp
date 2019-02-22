
#include <iostream>
using namespace std;



float add_item_to_grade(float item_value, bool is_graded, char item_name[], float my_grade, float graded)
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
            my_grade += (pcnt_earned * item_value);
            cout << "Your grade: " << my_grade << endl;
            graded += 100.0 * item_value;
            return my_grade;
        }
        is_graded = false;
    }
    my_grade += 100.0 * item_value;
    return my_grade;
}


int main(){

    char HW1[] = {'H', 'W', '1', '\0'};
    char HW2[] = {'H', 'W', '2', '\0'};
    char HW3[] = {'H', 'W', '3', '\0'};
    char HW4[] = {'H', 'W', '4', '\0'};
    char HW5[] = {'H', 'W', '5', '\0'};
    char LAB1[] = {'L', 'A', 'B', '\0'};
    char QUIZ[] = {'Q', 'U', 'I', 'Z', '\0'};
    char MID[] = {'M', 'I', 'D', 'T', 'E', 'R', 'M', '\0'};
    char FINAL[] = {'F', 'I', 'N', 'A', 'L', '\0'};

    float my_grade = 0.0;
    float grade_available = 0.0;

    float pcnt_earned = 0.0;   // This is where we track the points earned. Each percentage is worth 1.
    float pcnt_graded = 0.0;   // This is where we track the points earned. Each percentage is worth 1.
    float item_value = 0.0;    // This is where we track the current assignments portion of the final grade as decimal.
    bool is_graded = true;     // To track if we have gone beyond which assignments have been graded and to stop prompts.


    // Not that the is_graded bool is carried over from one assignment to the next.
    // For homeworks we are assuming if one is not graded, all following are also not graded.
    my_grade = add_item_to_grade(
        0.05,
        is_graded,
        HW1,
        my_grade,
        grade_available
        );
    my_grade = add_item_to_grade(
        0.05,
        is_graded,
        HW2,
        my_grade,
        grade_available
        );
    my_grade = add_item_to_grade(
        0.05,
        is_graded,
        HW3,
        my_grade,
        grade_available
        );
    my_grade = add_item_to_grade(
        0.05,
        is_graded,
        HW4,
        my_grade,
        grade_available
        );
    my_grade = add_item_to_grade(
        0.05,
        is_graded,
        HW5,
        my_grade,
        grade_available
        );
    my_grade = add_item_to_grade(
        0.05,
        is_graded,
        HW5,
        my_grade,
        grade_available
        );
    // Here I am setting is graded back to true, because I don't want
    // to assume that all homeworks are graded before anthing else.
    is_graded = true;
    my_grade = add_item_to_grade(
        0.05,
        is_graded,
        LAB1,
        my_grade,
        grade_available
        );
    // Don't assume graded in order. Always prompt for grade for this item.
    is_graded = true;
    my_grade = add_item_to_grade(
        0.05,
        is_graded,
        QUIZ,
        my_grade,
        grade_available
        );
    // Don't assume graded in order. Always prompt for grade for this item.
    is_graded = true;
    my_grade = add_item_to_grade(
        0.25,
        is_graded,
        MID,
        my_grade,
        grade_available
        );
    // Don't assume graded in order. Always prompt for grade for this item.
    is_graded = true;
    my_grade = add_item_to_grade(
        0.40,
        is_graded,
        FINAL,
        my_grade,
        grade_available
        );
    // Present the current stannding grade.
    cout << "Percentage of final grade earned: " << my_grade << endl;
    cout << "Percentage of available grade earned: " << 100.0*my_grade/grade_available << endl;
    

    return 0;
}