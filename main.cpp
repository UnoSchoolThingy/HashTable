/* Uno Pasadhika 
 * Student List - list of students with name, student ID, and GPA 
 * 9/15/2022 
 */ 
#include "Student.h"
#include "Utils.h"
#include <vector>

using namespace std;

// Prompt the user to add a student 
void promptAddStudent(vector<Student*>* students) {
  char in[100];
  char in2[35];
  int id;
  float gpa;
  cout << "Enter first name: ";
  cin >> in;
  cout << "Enter last name: ";
  cin >> in2;
  cout << "Enter student ID: ";
  cin >> id;
  cout << "Enter GPA: ";
  cin >> gpa;
  students->push_back(new Student(in, in2, id, gpa));
}

// Print the list size and the list 
void printList(vector<Student*>* students) {
   cout << "The student list size is " << students->size() << "\n";
   for (Student* student : *students) {
     char buffer[10]; // For rounded float
     sprintf(buffer, "%.2f", student->gpa); // Make rounded float and put it into buffer
     cout << student->firstname << ' ' << student->lastname << ", "
	  << student->id << ", " << buffer << '\n';
   }
}

// Delete a student from the list
void deleteStudent(vector<Student*>* students) {
  char in[100];
  int id;
  cout << "Enter the student ID of the student that you want to remove: ";
  cin >> id;
  bool erased = false;
  auto it = students->begin(); // Iterator
  while (it != students->end()) {
    Student* student = *it;
    if (student->id == id) {
      cout << "Deleting " << student->firstname << ' ' << student->lastname << " with ID " << id << '\n';
      delete student;
      students->erase(it);
      erased = true;
    }
    else { // Don't iterate if we just deleted something
      it++;
    }
  }
  if (!erased) cout << "There is no student with that ID!\n";
}

int main() {
  vector<Student*>* students = new vector<Student*>(); // Vector of student struct pointers 
  char in[35];
  while (true) {
    cout << "Enter command (ADD, PRINT, DELETE, or QUIT): ";
    cin >> in;
    try {
      if (Utils::chkcmd(in, "add")) promptAddStudent(students);
      else if (Utils::chkcmd(in, "print")) printList(students);
      else if (Utils::chkcmd(in, "delete")) deleteStudent(students);
      else if (Utils::chkcmd(in, "quit")) break;
      else cout << "That command isn't recognized!\n";
    }
    catch (...) {
      cout << "Oopsie, make sure you only enter the right stuff!\n";
    }
  }
}
