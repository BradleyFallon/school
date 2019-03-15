// ====================================================================
// Homework 5 for CS163
// Bradley Fallon
// bfallon@pdx.edu
// 3/15/2019
//
// Interactive test client
// ====================================================================

#include "header.h"

const int SIZE = 256;

// Prototypes - See definitions below
int auto_test();
bool prompt_bool();
int read_task_no();
int define_term(vertex & ref_term);

// Main loop of the test interface
int main()
{
    Graph my_graph;
    bool do_run = true;  // Flag to control if the user is still interacting with the program
    int task_no = 0;     // Stores the user's option for which ask to operate
    char text1[SIZE_TEMP_CHARS];
    int int_get1;
    int int_get2;

    cout << "====================================================================" << endl
        << "====================================================================" << endl
        << "     WELCOME TO BRADLEY FALLON'S HOMEWORK 5 TEST PROGRAM    " << endl << endl
        << "  Hey, fyi, if you want to get a good head start on testing, " << endl
        << "  there is a file which is meant to be used test with cat/piping." << endl
        << "  cat test_input_cat.txt | ./a.out" << endl << endl
        << "             ENJOY! ;)" << endl
        << "====================================================================" << endl
        << "====================================================================" << endl;


    // This is the main interactive loop
    while (do_run)
    {
        task_no = read_task_no();
        if (task_no == 1)
        {
            cout << "Option 1 selected!" << endl;
            // 1: Add a new vertex.
            cout << "Enter your decision description (for char array):" << endl;
            cin.get(text1, SIZE_TEMP_CHARS, '\n');
            cin.ignore(SIZE_TEMP_CHARS,'\n');
            if (my_graph.insert_vertex(text1)){
                cout << "vertex added successfully!" << endl;
            } else cout << "An error occurred! Not added to graph." << endl;
        }
        else if (task_no == 2)
        {
            // 2: Add a new edge.
            cout << "Option 2 selected!" << endl;
            // Get the edge weight data
            cout << "What is the decision outcome description (for char array):" << endl;
            cin.get(text1, SIZE_TEMP_CHARS, '\n');
            cin.ignore(SIZE_TEMP_CHARS,'\n');
            // Get the indexes of the vertices to connect, in order of direction
            cout << "Enter your decision id connecting FROM (whole number):" << endl;
            while (!(cin >> int_get1)){
                cin.clear();
                cin.ignore(SIZE_TEMP_CHARS,'\n');
                int_get1 = 0;
                cout <<"Try again with a number:" << endl;
            }
            cin.ignore(SIZE_TEMP_CHARS,'\n');
            cout << "Enter your decision id connecting TO (whole number):" << endl;
            while (!(cin >> int_get2)){
                cin.clear();
                cin.ignore(SIZE_TEMP_CHARS,'\n');
                int_get2 = 0;
                cout <<"Try again with a number:" << endl;
            }
            cin.ignore(SIZE_TEMP_CHARS,'\n');
            if (my_graph.insert_edge(int_get1, int_get2, text1)){
                cout << "vertex added successfully!" << endl;
            } else cout << "An error occurred! Not added to graph." << endl;
        }
        else if (task_no == 3)
        {
            cout << "Option 3 selected!" << endl;
            // 3: Check connectivity.
            if (my_graph.is_fully_connected()){
                cout << "The graph is fully connected!" << endl;
            } else cout << "Graph is either not full connected or poorly defined!" << endl;
        }
        else if (task_no == 4)
        {
            cout << "Option 4 selected!" << endl;
            // 4: Display all vertices.
            my_graph.display_vertices();
        }
        else if (task_no == 5)
        {
            cout << "Option 5 selected!" << endl;
            // 5: Display all adjacency.
            my_graph.display_adjacency();
        }
        else if (task_no == 6)
        {
            cout << "Option 6 selected!" << endl;
            // 6: Exit.
            cout << "Goodbye!" << endl;
            do_run = false;
        }
        // Invalid option
        else
        {
            // Invalid response
            cout << "That was not a valid option, please try again." << endl;
        }
    }
    return 0;
}

// Read from user which task they want to perform
int read_task_no(){
    int option = 0; // The number of the chosen option
    bool failed = false; // Tracks if the user has alread failed to get option
    char garbage[SIZE]; // In case they dont enter a number

    while (!(option >=1 & option <= 9))
    {
        // After first try, print failed vertex
        if (failed)
        {
            cout << "Invalid response. Please try again..." << endl;
        }
        failed = true;
        // Give instructions and get response
        cout << "\n\nWhat do you want?" << endl
            << "1: Add a new vertex." << endl
            << "2: Add a new edge." << endl
            << "3: Check connectivity." << endl
            << "4: Display all vertices." << endl
            << "5: Display all adjacency." << endl
            << "6: Exit." << endl
            << "\nEnter a number to enjoy an option." << endl
            << endl;
        if (!(cin >> option)){
            // I was annoyed with input errors, discovered clear() on a forum
            // http://www.cplusplus.com/forum/beginner/26821/
            cin.clear();
            cin.ignore();
            option = 0;
        } else
        // cin.get(garbage, SIZE_TEMP_CHARS, '\n');
        cin.ignore(SIZE_TEMP_CHARS, '\n');
    }
    return option;
}
