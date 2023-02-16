#pragma once 

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <stack>
#include "Student.h"
#include "Utils.h"

using std::cout;

// Entry. Basically a node 
struct Entry {
  Student* student;
  Entry* nextLinked;

  Entry() {
    memset(this, 0x0, sizeof(Entry));
  }

  Entry(Student* s) {
    this->student = s;
    this->nextLinked = nullptr;
  }

  ~Entry() {
    delete student;
  }
};

// The hash table 
struct HashTable {
  unsigned int size;
  Entry** entries; 

  HashTable() {
    this->size = 101; // 101 is the first prime number after 100 
    this->entries = reinterpret_cast<Entry**>(new unsigned long long[101]);
    memset(this->entries, 0x0, 808);
  }

  // https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
  unsigned int hashID(unsigned int id) {
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id = (id >> 16) ^ id;
    return id % size;
  }

  // Hash table operations

  // Print for testing 
  void debugPrint() {
    for (int i = 0; i < size; i++) {
      Entry* e = entries[i];
      if (e != nullptr) {
        cout << "Array index: " << i << "\n";
        while (e != nullptr) {
          cout << e->student->id << "\n";
          e = e->nextLinked;
        }
      }
    }
  }

  // Print out the list
  void print() { // Emacs really doesn't want to indent this function properly 
    // Doing this since we probably aren't allowed to use vectors 
    Student* arr = new Student[size];
    int actualSize = 0;
    for (int i = 0; i < size; i++) {
      Entry* e = entries[i];
      while (e != nullptr) {
        arr[actualSize++] = *e->student;
        e = e->nextLinked;
      }
    }
    // Sort by ID 
    std::sort(arr, arr + actualSize, 
      [](Student& a, Student& b) { 
        return a.id < b.id; 
      });
    // Print the list of students 
    for (int i = 0; i < actualSize; i++) {
      cout << "[" << arr[i].id << "] " << arr[i].firstname << " " << arr[i].lastname << " (" << std::fixed << std::setprecision(2) << arr[i].gpa << ")\n";
    }
    // Make sure we don't have an insane memory leak 
    delete[] arr;
  }
  
  // Insert a student 
  bool insert(Student* s) {
    unsigned int hash = hashID(s->id);
    if (entries[hash] == nullptr) { // An entry with dis hash no existy :) 
      entries[hash] = new Entry(s);
      return true;
    }
    // There was a collision :(
    // Go through the linked list
    Entry* seek = entries[hash];
    Entry* prev = nullptr;
    int ctr = 0;
    while (seek != nullptr) {
      prev = seek;
      ctr++; // Don't break even if it's more than 3 cuz if we have an ID match we want to return false 
      if (seek->student->id == s->id) {
        // The ID is the same
        delete s;
        return false; 
      }
      seek = seek->nextLinked;
    }
    // Add to list, even if there are already too many collisions 
    prev->nextLinked = new Entry(s);
    // If there are too many collisions then we need to redo the entire table 
    if (ctr > 3) { // We need to expand the table
      cout << "Resizing table to " << (size * 2) << "!\n";
      // Build a list of all the students
      std::stack<Student> students;
      for (int i = 0; i < size; i++) {
        while (entries[i] != nullptr) {
          students.push(*entries[i]->student); // We have to copy out the actual student because the original will get deleted 
          Entry* e = entries[i];
          entries[i] = entries[i]->nextLinked;
          delete e;
        }
      }
      delete[] entries;
      // All of our students are now in the list, we can rehash and reinsert as needed
      size *= 2;
      this->entries = reinterpret_cast<Entry**>(new unsigned long long[size]);
      memset(this->entries, 0x0, size * 8);
      while (!students.empty()) {
        insert(new Student(&students.top()));
        students.pop();
      }
    }
    return true;
  }

  // Remove a student from the list 
  bool erase(unsigned int id) {
    unsigned int hash = hashID(id);
    Entry* seek = entries[hash];
    Entry* prev = nullptr;
    while (seek != nullptr) {
      if (seek->student->id == id) { // Check if we have a match 
        if (prev == nullptr) { // Check if this is the first entry 
          // Shift the first entry in the list to the next entry so now the next entry is the first 
          entries[hash] = seek->nextLinked;
        } 
        else { // This isn't the first entry 
          // Link the previous entry to the next entry
          prev->nextLinked = seek->nextLinked;
        }
        delete seek;
        return true;
      }
      prev = seek;
      seek = seek->nextLinked;
    }
    return false;
  }
  
};
