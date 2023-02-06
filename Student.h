#pragma once

#include <cstring>

// Student struct (we make a list of these) 
struct Student {
  char firstname[35];
  char lastname[35];
  unsigned int id;
  float gpa;

  Student(char* firstname, char* lastname, unsigned int id, float gpa) {
    strcpy(this->firstname, firstname);
    strcpy(this->lastname, lastname);
    this->id = id;
    this->gpa = gpa;
  }

  Student(Student* s) {
    memcpy(this, s, sizeof(Student));
  }
};
