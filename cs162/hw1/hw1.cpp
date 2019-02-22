// Homework 1 for CS162
// Bradley Fallon
// bfallon@pdx.edu
// 10/9/2018

/*
   Written Questions

   Question 1:
   I am a mechanical engineer. I have a program I wrote for work that
   does some tasks in parallel. It takes a Finite Element Method
   model and runs multiple simulations on a compute cluster and
   then processes the results into a single report.Many simulations
   are performed in parallel. This involves three serial tasks per
   each simulation, which are defining a variant of the model and
   scenario for this particular simulation, calculating the simulation
   solution, and processing the simulation result into a common data
   format. Each of these simulation variants are ran in parallel,
   but contain serial tasks. Also in parallel to the simulations,
   the main model is evaluated to generate data in a format used
   to make visual reports. Images and graphs of the model are
   also generated. This is all monitored, and when all of this
   is complete, a new process generates a report of all of thesimulation results.
   The data is all related and in the end it is all used to
   generate a single report, but it is very cleanly divided
   into portions of data with a different purpose. I’m leaning
   more toward task parallel. This is because in this example
   the parallelization and serialization are strictly based on
   input and output dependency of the discrete tasks.

   Question 2:
   I could improve the readability of my code by doing the following:
   For all functions, comment to explain the inputs, outputs, and purpose.
   I tend to rush my code and skip this because I think it is obvious,
   but it is not so obvious to others or after time has passed and I forget.
   I should comment on the purpose of each variable declared, rather
   than relying on variable name alone. I should also comment on why I
   give the default values I do, if they are not null.
   With loops, I should avoid using breaks. I tend to use breaks to exit
   “while” and “for” loops, and this make it less clear what the
   exit condition is meant to be.

   Question 4:
   I would expect my classmates to comply with the following rules:
   Do not attempt to access the files of other peoples accounts
   Do not use massive bandwidth for personal entertainment
   Do not attempt to remotely run programs  on machines actively used by others.
   */

/*
Purpose:
The purpose for this algorithm is to calculate a student’s working grade in CS162.
My interpretation of the problem is this: Calculate the percentage of
Final Grade Percentage Points, FGPs, earned out of FGPs that could have
been earned up to this time.

Known Information:
Final Grade Based On:
25% for 5 programs
5% for lab book
5% for quiz
25% for 1 midterm
40% for 1 final


Solve For:
The current percent of grade earned out of the grade possibly earned this far.
(EXTRA CREDIT) The minimum Final Exam score needed to get the user's target grade in the class.

Algorithm:
Start tracking FGPs-earned and FGPs-graded, counting from 0.
Note: These will be incremented within range 0 to 1 as we go.
For each item included in the final grade, do the following:
	Calculate the available FGPs for 100% score.
	Prompt user for if the assigment was graded.
	If not, move on to next assignment and do nothing.
	Prompt user for score earned.
	Add the possible FGPs available FGPs.
	Calculate and add FGPs-earned according to score entered.
Calculate percentage FGPs-earned out of FGPs-graded.
	Current Grade = FGPs-earned/FGPs-graded
Prompt user for their target grade for the class.
Calculate final exam score needed to earn the difference.
	F = (T + A - G - 60)/0.4
	Note: See the fn calculate_final_req() for more info.
	Note: I think that if this is less than 0% or greater than 100% , that is fun and informative for user. It is a feature not a bug.
Present results to user.
Prompt user for if they would like to quit or try again.
Quit or try again according to user input.

*/


#include <iostream>
using namespace std;

struct GradeInfo {
	// Grade information used to calculate final exam score needed and current working grade.
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
		// Prompt user for boolean response.
		cout << "Please respond with 'y' (yes) or 'n' (no)." << endl;
		cin >> response;
		// Make sure the input buffer is clear, just in case.
		while(cin.get() != '\n');
		// Process input and return true or false if input was valid.
		if (response=='y')
		{
			return true;
		} else if (response=='n')
		{
			return false;
		} else
		{
			// Invalid response. Inform user and try again.
			cout << "Invalid response..." << endl;
		}
	}
	// Give up because user has exceeded tries limit. Assume the assignment was graded.
	cout << "This is taking too long. I'll answer for you... 'y'." << endl;
	return true;
}

GradeInfo add_item_to_grade(float item_value, char item_name[], GradeInfo my_grade_info)
{
	// This function takes in grade info and returns an updated grade info.
	// This also function takes in the information about an assignment's name and its weight
	// The user is prompted for whether the assignment has been graded.
	// If the assignment has been graded, then prompt the user for score and
	// add that to the user's grade earned. Also add the grade value of the
	// assignment to the potential grade.If the assignment is not graded,
	// then do not update grade info.
	float pcnt_earned = 0.0;
	char response;
	// Prompt for if assignment is graded.
	cout << "\nHas " << item_name << " been graded yet?" << endl;
	if (prompt_bool())
	{
		// Prompt for score earned.
		cout << "Please enter your score as a percentage (e.g. 92.5)." << endl;
		cin >> pcnt_earned;
		cout << "You entered: " << pcnt_earned << endl;
		// Add grade earned on this assignment to total grade earned.
		my_grade_info.grade_earned += (pcnt_earned * item_value);
		// Add max available grade for this assignment to total possible graded.
		my_grade_info.grade_available += (100.0 * item_value);
	}
	return my_grade_info;
}

float calculate_final_req(GradeInfo my_grade_info, float target_grade)
{
	// This will calculate the score required to earn on the Final Exam in
	// order to acheive the target grade in the class.
	// Using grade info we can calculate the potential score to earn besides final exam.
	// Assume all ungraded work other than the final exam will receive 100%.
	// ungraded_potential = 100 - 100*final_exam_wt - grade_available
	// Formula for possible final class grade according to final exam score.
	// 		final_grade = final_exam_score*0.4 + grade_earned + ungraded_potential
	// 		target_grade =
	// 			final_exam_score*0.4 +
	// 			grade_earned +
	//      	(100 - 100*final_exam_wt - grade_available)
	// Make short variable names and simplify.
	// 		T = 0.4F + G + 100 - 40 - A
	// 		T = 0.4F + 60 + G - A
	// Rearrange to solve for score needed on exam to get target grade in class.
	// 		F = (T + A - G - 60)/0.4
	float final_exam_p_need = 0.0; // The score percent needed (0 to 100) on final exam to get target grade.
	final_exam_p_need = (
			target_grade +
			my_grade_info.grade_available -
			my_grade_info.grade_earned -
			60 ) / 0.4;
	return final_exam_p_need;
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

	// Restart process as long as user wants. Loop condition "running" will be made false
	// if the user indicates they are finished after a final result is given.
	while (running)
	{
		// Reset variables related to user input.
		GradeInfo my_grade_info = {0.0, 0.0}; // Reset instance of GradeInfo to track my grade.
		//Welcome!
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
		// Ask for the user's target grade for the class.
		cout << "\nWhat is the minimum grade you wish to recieve in the class (e.g. 90.0)?" << endl;
		cin >> target_grade;
		// Present the current standing grade. Present in form of 1% to 100% and not 0.01 to 1.0 because this is easier to read.
		cout << "\n" <<
			"Percentage of final grade earned: " <<
			my_grade_info.grade_earned <<
			"%" <<
			endl;
		cout << "Percentage of available grade earned: " <<
			100.0*my_grade_info.grade_earned/my_grade_info.grade_available <<
			"%" <<
			endl;
		// Calculate and present the current standing grade.
		cout << "Required final exam score to get " << target_grade << "% in class: "<<
			calculate_final_req(my_grade_info, target_grade) << "%" <<
			"\n(Assuming 100% on all other ungraded work.)" <<
			endl;
		// We are done. Ask user if they want to try again. This will kill main loop if false.
		cout << "\n" <<
			"Would you like to try again?" << endl;
		running = prompt_bool();
	}
	return 0;
}
