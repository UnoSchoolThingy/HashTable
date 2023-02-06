/* Uno Pasadhika 
 * Hash Table - Basically student list but we use a hash table 
 * 2/6/2023
 */ 
#include "HashTable.h"
#include "Utils.h"
#include <vector>

using namespace std;

// Prompt the user to add a student 
void promptAddStudent(vector<Student*>* students) {
  
}

// Print the list size and the list 
void printList(vector<Student*>* students) {
   
}

// Delete a student from the list
void deleteStudent(vector<Student*>* students) {
  
}

int main() {
  vector<Student*>* students = new vector<Student*>(); // Vector of student struct pointers 
  HashTable table;
  char in[35];
  // Epic testing
  char* yes = "pp";
  int deez = 5;
  for (int i = 0; i < 5000; i++) {
    table.insert(new Student(yes, yes, deez++, 3.5f));
  }
  table.debugPrint();
  return 0;
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
