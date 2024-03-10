#include <iostream>
#include <string>
#include <cmath>
#include "headers/db.hpp"
using namespace std;

DB db;

void log(string str) {
  cout << "\n>>> " << str;
}

void execCmd(int cmd) {
  if(cmd == 1) {
    string name;
    int salary;
      
    log("Name: ");
    cin >> name;
      
    log("Salary: ");
    cin >> salary;
      
    db.addUser(name, salary);
  } else if(cmd == 2) {
    db.getAll();
  } else if(cmd != 0) {
    log("Inavlid Command");
  }
}

int main() {
  int cmd;
  log("<==== STARTING PROGRAM ====>");
  db.load();
  
  do {
    log("Enter a command to execute (0 to exit) ~> ");
    cin >> cmd;

    execCmd(cmd);
  } while(cmd != 0);

  log("<==== EXITING PROGRAM ====>");
  return 0;
}