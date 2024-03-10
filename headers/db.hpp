#ifndef DB_HPP
#define DB_HPP
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class DB {
  private:
  string folder = "data";
  
  public:
  const char* Month[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

  void load() {
    if(!filesystem::exists(folder)) {
      filesystem::create_directory(folder);
      log("Folder created: " + folder);
    }
  }

  void addUser(string &name, int salary) {
    string path = folder + "/" + name;
    if(!filesystem::exists(path)) {
      filesystem::create_directory(path);
    };
    
    if(!filesystem::exists(path + "/current.salary")) {
      ofstream outFile(path + "/current.salary");
      string data = "name=" + name + ",salary=" + to_string(salary);
      outFile << data;
    }
    
    log("Added User: " + name);
  }

  int getAll() {
    for (const auto & entry : filesystem::directory_iterator(folder)) {
      for(const auto & entry : filesystem::directory_iterator(entry.path())) {
        if(entry.path().filename() == "current.salary") {
          ifstream file(entry.path());
          if(file.is_open()) {
            string token;
            string name;
            string salary;
            string paid;
            
            while(getline(file, token, ',')) {
              size_t found = token.find('=');
              if (found != string::npos) {
                string key = token.substr(0, found);
                string value = token.substr(found + 1);
                
                if(key == "name") {
                  name = value;
                } else if(key == "salary") {
                  salary = value;
                } else {
                  paid = value;
                }
              }
            }
            
            showUser(name, stoi(salary), stoi(paid));
          }
        }
      }
    }
    return 0;
  }
  
  void showUser(string &name, int salary, int paid) {
    log("Name ~> " + name);
    log("Salary ~> " + to_string(salary));
    log("");
    int pap = paid;
    
    for(int i = 0; i < 12; ++i) {
      int p = pap - salary;
      int pp;
      
      if(pap >= salary) {
        pp = salary;
      } else {
        pp = pap;
      }
      
      pap -= salary;
      
      if(pp > 0) {
        log(string(Month[i]) + " ~> Paid - " + to_string(pp));
      } else {
        break;
      }
    }
    
    int bonus = paid - (salary * 12);
    
    log("");
    log("Paid: " + to_string(paid));
    if(bonus > 0) {
      log("Bonus: " + to_string(bonus));
    }
    
    cout << "\n";
  }

  void log(string str) {
    cout << "\n >>> " << str;
  }
};

#endif // DB_HPP