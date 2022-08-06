/*****************************************************************************
 ** File: Trivia.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Kush Shah and CMSC202
 ** Date:    04/05/2022
 ** Email:   k216@umbc.edu
 **
 Description: CPP file for Trivia class. Includes both class definition and
 class function definitions. Loads a file of trivia questions
*****************************************************************************/

#ifndef TRIVIA_CPP
#define TRIVIA_CPP
#include "Lqueue.cpp"
#include "Question.cpp"
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

const string DEFAULT_FILE = "proj5_string.txt";
const char DELIMITER = '|';

template <class T>
class Trivia {
public:
  // Name: Default Constructor
  // Desc: Displays the title, Loads Questions and calls menu
  // Indicates if the file was not loaded.
  // Precondition: None
  // Postcondition: User is prompted with assignment menus
  Trivia(string filename= DEFAULT_FILE);
  // Name: Destructor
  // Desc: Deallocates memory allocated for the Questions and
  // resets all variables.
  // Precondition: A Trivia exists.
  // Postcondition: All dynamically allocated memory in Trivia is deleted.
  ~Trivia();
  // Name: LoadQuestions
  // Desc: Each input file will be for a specific type of question (int, double, string)
  //       Reads in Questions from a file and stores them in anLqueue.
  //       An input file will be for exactly one type of question (int, double, string)
  // Precondition: None.
  // Postcondition: Returns true if file was read. Otherwise, it returns false.
  bool LoadQuestions(string filename);
  // Name: MainMenu
  // Desc: Presents user with menu options for showing subjects and allowing
  // user to work on a subject.
  // Precondition: None.
  // Postcondition: The main menu is presented.
  void MainMenu();
  // Name: DisplaySubjects
  // Desc: Presents all Subjects with corresponding numerical identifiers.
  // Precondition: Subjects have been added.
  // Postcondition: All assignments are printed to the screen.
  void DisplaySubjects();
  // Name: StartSubject
  // Desc: Starts working on a selected Subject.
  // Displays the number of questions in subject.
  // Starts at beginning and goes through each question.
  // After all questions have been answered:
  //       displays total correct, incorrect, and percentage correct
  // Precondition: m_questions has been populated
  // Postcondition: Returns to main menu
  void StartSubject();
  // Name: AddSubject
  // Desc: Checks to see if a subject exists in m_subjects.
  //       If not, inserts subject into m_subjects.
  // Precondition: A Subject exists.
  // Postcondition: Add subject to m_subjects if new subject.
  void AddSubject(string subject);
  // Name: ChooseSubject
  // Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
  // in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
  // Precondition: A Subject exists.
  // Postcondition: Returns value entered minus one
  int ChooseSubject();
  // Name: QuestionsPerSubject
  // Desc: Iterates over m_questions and counts how many questions match the subject
  // passed into function
  // Precondition: A Subject exists.
  // Postcondition: Returns number of questions of a particular subject
  int QuestionsPerSubject(string subject);
  // Name: DisplayTitle
  // Desc: Displays opening Welcome message
  // Precondition: None.
  // Postcondition: Title is displayed.
  void DisplayTitle();
private:
  Lqueue<Question<T>* >* m_questions; // Holds questions using a specific data type
  vector<string> m_subjects; //Populated as file is loaded
};

// Precondition: None
// Postcondition: User is prompted with assignment menus
template <class T>
Trivia<T>::Trivia(string filename) {
    m_questions = new Lqueue<Question<T>* >(); // allocates new question
    DisplayTitle(); // calls display title
    LoadQuestions(filename); // calls load questions

    int choice = 0;
    while (choice != 3) {
        MainMenu();
        cin >> choice;
        if (choice == 1) {
            DisplaySubjects(); // if the user chooses 1
        } else if (choice == 2) {
            StartSubject(); // if the user chooses 2
        }
    }

}


// Precondition: A Trivia exists.
// Postcondition: All dynamically allocated memory in Trivia is deleted.
template <class T>
Trivia<T>::~Trivia<T>() {

    for (int i = 0; i < m_questions->GetSize(); i++) {
        delete m_questions->At(i);
    }
    delete m_questions;
}







// Precondition: None.
// Postcondition: Returns true if file was read. Otherwise, it returns false.
template <class T>
bool Trivia<T>::LoadQuestions(string filename) {
    ifstream file(filename); // uses ifstream to read in file
    string line;

    while (getline(file, line, DELIMITER)) {
        string subject = line;  // reads in subject
        getline(file, line, DELIMITER);
        string question = line; // reads in question
        getline(file, line, DELIMITER);
        string type = line; // reads in type
        getline(file, line, DELIMITER);
        int difficulty = stoi(line); // reads in difficulty and casts it to int
        getline(file, line);
        stringstream ss(line);
        T answer; // reads in answer as template
        ss >> answer;
        Question<T> *q =  new Question<T>(subject, question, type, difficulty, answer);
        m_questions->Push(q);
        AddSubject(subject);

    }
    return true;
}


// Precondition: None.
// Postcondition: The main menu is presented.
template <class T>
void Trivia<T>::MainMenu() {
    cout << "Choose an option." << endl; // simply displays menu from document
    cout << "1. Display Subjects" << endl;
    cout << "2. Start Subject" << endl;
    cout << "3. Quit" << endl;

}


// Precondition: Subjects have been added.
// Postcondition: All assignments are printed to the screen.
template <class T>
void Trivia<T>::DisplaySubjects() {
    cout << "Possible subjects: " << endl;
    for (unsigned int i = 0; i < m_subjects.size(); i++) { // iterate through vector
        cout << i + 1 << ". " << m_subjects[i] << endl; // print the subjects in a list
    }
}


// Precondition: m_questions has been populated
// Postcondition: Returns to main menu
template <class T>
void Trivia<T>::StartSubject() {
    int choice = ChooseSubject(); // takes in choice from user
   int count = QuestionsPerSubject(m_subjects[choice]);
   cout << "There are " << count << " questions in this subject." << endl;

   int i = 0;
   int j = 0;
   T answer;
   int correct = 0;
   while (i < count) {
       Question<T> *q = m_questions->At(j); // calls at function from lqueue
       if (q->m_subject == m_subjects[choice]) {
           cout << i+1 << ". " << *q << endl;
           i++;
           cin >> answer;
           if (answer == q->m_answer) {
               cout << "Correct" << endl; // if the user answers correctly
               correct++;
           } else {
               cout << "Incorrect" << endl; // if the user answers incorrectly
           }
       }
       j++;
   }
   cout << "You got " << correct << " answers correct." << endl;
   cout << "You got " << count-correct << " answers incorrect." << endl;
   int percent = (correct/(double)count) * 100; // presentage calculator
   cout << "Which is a " << percent << "%." << endl;


}


// Precondition: A Subject exists.
// Postcondition: Add subject to m_subjects if new subject.
template <class T>
void Trivia<T>::AddSubject(string subject) {
    bool subjectFound = false; // creates flag to check if the subject already exists
    for (unsigned int i = 0; i < m_subjects.size(); i++) {
        if (m_subjects[i] == subject) {
           subjectFound = true; // if the subject is found
        }

    }
    if (!subjectFound) {
        m_subjects.push_back(subject); // if the subject is not found, add it to vector
    }
}


// Precondition: A Subject exists.
// Postcondition: Returns value entered minus one
template <class T>
int Trivia<T>::ChooseSubject() {
    int choice = 0;
    cout << "Which subject would you like to attempt? " << endl; // prompts user
    DisplaySubjects();
    cin >> choice; // reads in users choice
    return (choice - 1);
}


// Precondition: A Subject exists.
// Postcondition: Returns number of questions of a particular subject
template <class T>
int Trivia<T>::QuestionsPerSubject(string subject) {
    int count = 0;
    for (int i = 0; i < m_questions->GetSize(); i++) { // iterates through questions
        if (m_questions->At(i)->m_subject == subject) {
            count++; // if the subject matches
        }
    }
    return count;
}


// Precondition: None.
// Postcondition: Title is displayed.
template <class T>
void Trivia<T>::DisplayTitle() {
    cout << "Welcome to UMBC Trivia!" << endl;

}



#endif
