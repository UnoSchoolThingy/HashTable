/* Uno Pasadhika 
 * Hash Table - Basically student list but we use a hash table 
 * 2/6/2023
 */ 

#include "HashTable.h"

using namespace std;

// Prompt the user to add a student 
bool promptAddStudent(HashTable& table) {
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
  return table.insert(new Student(in, in2, id, gpa));
}

// Delete a student from the list
bool promptDeleteStudent(HashTable& table) {
  cout << "Enter the ID to delete: ";
  int id;
  cin >> id;
  return table.erase(id);
}

int main() {
  HashTable table;
  char in[35];
  while (true) {
    cout << "Enter command (ADD, PRINT, DELETE, or QUIT): ";
    cin >> in;
    try {
      if (Utils::chkcmd(in, "add")) cout << (promptAddStudent(table) ? "Added!" : "Couldn't add, a student with the same ID already exists!") << endl;
      else if (Utils::chkcmd(in, "print")) table.print();
      else if (Utils::chkcmd(in, "delete")) cout << (promptDeleteStudent(table) ? "Deleted!" : "Couldn't delete, there was no student with that ID!") << endl;
      else if (Utils::chkcmd(in, "quit")) break;
      else cout << "That command isn't recognized!\n";
    }
    catch (...) {
      cout << "Oopsie, make sure you only enter the right stuff!\n";
    }
  }
}
