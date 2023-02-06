#pragma once

#include <cstring>

// Student class (we make a list of these) 
struct Student {
  char firstname[35];
  char lastname[35];
  int id;
  float gpa;

  Student(char* firstname, char* lastname, int id, float gpa) {
    strcpy(this->firstname, firstname);
    strcpy(this->lastname, lastname);
    this->id = id;
    this->gpa = gpa;
  }
};
