#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
/*
    Cat Struct
    Attributs:
        - content: vector<string>
        - A overload to print our content with the << operatorf

    methods
        parse_file() 
            - I want to go into our file and parse it and return a string   
           
*/

struct Cat {
    std::vector<std::string> content {};
    std::string output {};
    bool is_line_numbers { true };
    int line_count { 1 };

    operator const char*() {
        std::ostringstream result{};

        for (const auto& file : content) 
            result << file << '\n';
        
        output = result.str();
        return output.c_str();
    }

    void parse_file (const std::string& file);
};