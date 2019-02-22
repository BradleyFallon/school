
#include <iostream>
using namespace std;

// Grade information used to calculate final exam score needed and current working grade.
struct GradeInfo {
	float grade_earned; // The gradually incremented tracker for grade out of all points in course.
	float grade_available; // The max possible grade so far based on what has been graded.
};

bool prompt_bool()
{
	// This repeatedly prompts the user for a yes or no response until valid input is provided.
	int i = 0;
	char response;
	while (i=0, i++, i<5)
	{
		// Make sure the input buffer is clear, just in case.
		while(cin.get() != '\n');
		cout << "Please respond with 'y' (yes) or 'n' (no)." << endl;
		cin >> response;
		if (response=='y')
		{
			return true;	
		} else if (response=='n')
		{
			return false;
		} else cout << "Invalid response..." << endl;
	}
	cout << "This is taking too long. I'll answer for you... 'y'." << endl;
	return true;
}


GradeInfo add_item_to_grade(float item_value, char item_name[], GradeInfo my_grade_info)
{
	float pcnt_earned = 0.0;
	char response;

	cout << "\nHas " << item_name << " been graded yet?" << endl;
	if (prompt_bool())
	{
		cout << "Please enter your score as a percentage (e.g. 92.5)." << endl;
		cin >> pcnt_earned;
		cout << "You entered: " << pcnt_earned << endl;
		if (pcnt_earned)
		{
			my_grade_info.grade_earned += (pcnt_earned * item_value);
			cout << "Your grade: " << my_grade_info.grade_earned << endl;
			my_grade_info.grade_available += (100.0 * item_value);
		}
	}
	return my_grade_info;
}

float calculate_final_req(GradeInfo my_grade_info, float target_grade)
{
	// This will calculate the score required to earn on the Final Exam in
	// order to acheive the target grade in the class.
	// Assume all ungraded work other than the final exam will receive 100%.
	return 0.0;
}

int main(){
	// These are my assignment names. These are passed into a generic grade prompter function.
	// I would like to learn how to associate the name with other properties using a struct.
	char HW1[] = "HW1"; // Assignment name
	char HW2[] = "HW2"; // Assignment name
	char HW3[] = "HW3"; // Assignment name
	char HW4[] = "HW4"; // Assignment name
	char HW5[] = "HW5"; // Assignment name
	char LAB1[] = "LAB1"; // Assignment name
	char QUIZ[] = "QUIZ"; // Assignment name
	char MID[] = "MIDTERM"; // Assignment name
	char FINAL[] = "FINAL"; // Assignment name
	GradeInfo my_grade_info; // Instance of GradeInfo to track my grade.
	float target_grade = 0.0; // Grade the user wishes to earn in class. For calculating required Final Exam score.
	// Utilites for looping.
	bool running = true; // This is a boolean to switch off the main function looping.
	
	// It would be nice to figure this prompting for scores process out in a loop, but I don't want to end up being tagged as a cheater...
	// Experimenting with arrays.
	/*
	char *ITEM_NAMES[5] = {
		HW1,
		HW2,
		HW3,
	};

	int i;
	for (i=0; i<sizeof(ITEM_NAMES); i++)
	{
		cout << "Your thing: " << ITEM_NAMES[i] << endl;
	}
	return 0;
	*/

	while (running)
	{
		GradeInfo my_grade_info = {0.0, 0.0}; // Reset instance of GradeInfo to track my grade.

		cout << "\n\n" <<
			"========================================================\n" <<
			"========================================================\n" <<
			"Welcome to Bradley Fallon's grade calculator for CS162." << endl;


		// The same function is called for all graded class items.
		// The score arguments are incremented and carried over from assignment to assignment.
		// Get the score for HW1.
		my_grade_info = add_item_to_grade(
				0.05,
				HW1,
				my_grade_info
				);
		my_grade_info = add_item_to_grade(
				0.05,
				HW2,
				my_grade_info
				);
		my_grade_info = add_item_to_grade(
				0.05,
				HW3,
				my_grade_info
				);
		my_grade_info = add_item_to_grade(
				0.05,
				HW4,
				my_grade_info
				);
		my_grade_info = add_item_to_grade(
				0.05,
				HW5,
				my_grade_info
				);
		my_grade_info = add_item_to_grade(
				0.05,
				LAB1,
				my_grade_info
				);
		my_grade_info = add_item_to_grade(
				0.05,
				QUIZ,
				my_grade_info
				);
		my_grade_info = add_item_to_grade(
				0.25,
				MID,
				my_grade_info
				);
		my_grade_info = add_item_to_grade(
				0.40,
				FINAL,
				my_grade_info
				);
		// Present the current standing grade.
		cout << "\n" <<
			"Percentage of final grade earned: " << my_grade_info.grade_earned << endl;
		cout << "Percentage of available grade earned: " << my_grade_info.grade_earned/my_grade_info.grade_available << endl;
		cout << "\nLet's calculate the score you will need to get on the Final Exam." << endl;
		cout << "What is the minimum grade you wish to recieve in the class (e.g. 90.0)?" << endl;
		cin >> target_grade;
		cout << "\nRequired final lexam score to get " << target_grade << ": "<<
			calculate_final_req(my_grade_info, target_grade) << "%" <<
			endl;
		cout << "\n" <<
			"Would you like to try again?" << endl;
		running = prompt_bool();
	}
	return 0;
}
