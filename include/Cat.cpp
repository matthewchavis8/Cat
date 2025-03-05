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

    //Parse with line numbers
    auto parse_file_with_line_numbers = [&]() {
        while (std::getline(file, line)) {
            res << line_count << ": " << line << '\n';
            line_count++;
        }
    };
    // Regular parse 
    auto parse_file_with_default = [&]() {
        while (std::getline(file, line)) 
            res << line << '\n';
    };

    if (!file.is_open()) {
        std::cerr << "Error parsing our file" << '\n';
        return;
    }   

    if (is_line_numbers) 
        parse_file_with_line_numbers();
    else 
        parse_file_with_default();    
    //Adds our file content into our content Container
    content.push_back(res.str());
}

void Cat::write_to_file(const std::string& file_name) {
    // added so you do not have to explicitly say ../ everytime
    std::string path{ "../" };
    path += file_name;

    // Creates our file and in append mode
    std::ofstream file(path, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Error creating file";
        return;
    }

    std::string content{};
    std::getline(std::cin, content);
    file << content << '\n';
}

void Cat::redirect_to_file (const std::vector<std::string>& args, Cat& cat) {
    for (auto it = args.begin(); it != args.end(); it++) {
        if (*it != ">") {
            parse_file(*it);
            it++;
        } else {
            it++;
            std::ofstream file(*it, std::ios::app);

            if (!file.is_open()) {
                std::cerr << "Error opening the file";
                return;
            }
            file << cat;
        }
    }
}