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

    // Parse with line numbers
    auto parse_file_with_line_numbers = [&]() {
        while (std::getline(file, line)) {
            res << line_count << ": " << line << '\n';
            line_count++;
        }
    };
    // Regular parse 
    auto parse_file_with_default = [&]() {
        while (std::getline(file, line)) {
            if (ignore_blank_line_mode && line.empty())
                continue;
            res << line << '\n';
        }
    };

    // Parse with line ending with $]
    auto parse_file_with_dollar = [&]() {
        while (std::getline(file, line)) 
            res << line << "$" << '\n';
    };

    if (!file.is_open()) {
        std::cerr << "Error parsing our file" << '\n';
        return;
    }   

    if (line_number_mode) 
        parse_file_with_line_numbers();
    else if (mark_end_of_line_mode)
        parse_file_with_dollar();
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
    std::ofstream output_file;

    for (std::size_t i{}; i < args.size(); ++i) {
        if (args[i] == ">") {
            if (i + 1 < args.size()) {
                output_file.open(args[i + 1], std::ios::app);

                if (!output_file.is_open()) {
                    std::cerr << "Error opening the file";
                    return;
                }
                ++i;
            } else {
                std::cerr << "Redirection operator '>' found without a file though";
                return;
            }
        } else {
            parse_file(args[i]);
        }
    }

    output_file << cat;
}