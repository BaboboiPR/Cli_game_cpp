#pragma once

#include "polluter std.h"



class IO {
          public:
          static std::fstream file;
          static std::string line;
          static std::string context;
          public:
          static void new_file(std::fstream& NEW_FILE) {
                    file = std::move(NEW_FILE);
          }

          static std::string read_file(const std :: string& word) {
                    while (file >> line) {
                              if (line == word) {
                                        file >> context;
                                        return context;
                              }
                    }
                    std :: cerr << "Error at reading  file " << word << "\n";
                    return  (std:: string) "0";
          }

          static void write_file(const std :: string& word, const auto& value) {
                    while (file >> line) {
                              if (line == word) {
                                        file << "\n";
                                        file << value;
                                        return;
                              }
                              std::cout << line << "\n";
                    }
                    std :: cerr << "Error at writing file" << word << " " << value << "\n";
          }

};




