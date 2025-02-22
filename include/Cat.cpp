#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <fstream>
#include "Cat.hpp"

void Cat::parse_file (const std::string& path) {
    std::ifstream file(path);
    std::string line{};
    std::ostringstream res;

    if (file.is_open()) {
        
        if (is_line_numbers) {
            while (std::getline(file, line)) {
                res << line_count << ": " << line << '\n';
                line_count++;
            }
        } else {
            while (std::getline(file, line)) {
                res << line << '\n';
            }
        }
        
    } else {
        std::cerr << "Error parsing our file" << '\n';
    }
    
    content.push_back(res.str());
}