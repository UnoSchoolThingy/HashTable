#pragma once 

#include <iostream>
#include <stack>
#include "Student.h"

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

  bool debugPrint() {
    for (int i = 0; i < size; i++) {
      Entry* e = entries[i];
      if (e != nullptr) {
	std::cout << "KEY: " << i << "\n";
	while (e != nullptr) {
	  std::cout << e->student->id << "\n";
	  e = e->nextLinked;
	}
      }
    }
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
      std::cout << "Resizing table to " << (size * 2) << "!\n";
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
  
};
