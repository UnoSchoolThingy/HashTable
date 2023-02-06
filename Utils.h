#pragma once

#include <iostream>
#include <cstring>

// Various utilities (well actually there's just one here) 
struct Utils {
  // Check if a string is equal to a certain command 
  static bool chkcmd(const char* a, const char* b) {
    char* l = new char[strlen(a) + 1];
    for (int i = 0; i < strlen(a); i++) {
      l[i] = tolower(a[i]);
    }
    l[strlen(a)] = 0; // Just to be safe
    bool res = strcmp(l, b) == 0;
    delete[] l;
    return res;
  }
  
};
