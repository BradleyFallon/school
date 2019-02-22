#include "lstring.h"


int main()
{
    String race("race");

    String car;
    car.append('a');
    car.append('r');
    car.prepend('c');

    race.append(car);

    cout << "car is empty: " << car.empty() << endl;
	cout << "car = ";
	car.display();

    cout << "racecar = ";
    race.display();
    cout << endl;

    cout << "racecar is a palindrome: " << race.palindrome() << endl;

}
