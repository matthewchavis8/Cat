#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

/**
 * Cat Struct
 * 
 * This is a Cat object that holds our methods and groups up our attributes
 * 
 * @param content This Vector holds the content of each file we parse
 * @param output  Stores the C style string used to print out our Cat obj
 * @param is_line_numbers Toggle line numbers displayed
 * @param write_mode  Toggle write to a file
 * @param line_count  Counter that tracks the line count of our file
 * @param redirection_mode Toggle redirect previous files into file after '>'
 * @param reverse_parse_mode Toggle to reverse the output
 * @param mark_end_of_line_mode Toggle to add a $ to the end of the line
 */
struct Cat {
    std::vector<std::string> content {};
    std::string output {};
    int line_count { 1 };
    bool line_number_mode { false };
    bool write_mode { false };
    bool redirection_mode { false }; 
    bool reverse_parse_mode { false };
    bool mark_end_of_line_mode { false };

    /**
     * Convers the Cat Object into a C style string by concatenating its content.
     * 
     * @returns A pointer to a null-terminated string representing the Cat's Content
     */
    operator const char*() {
        if (reverse_parse_mode)
            std::reverse(content.begin(), content.end());

        std::ostringstream result{};

        for (const auto& file : content) 
            result << file << '\n';
        
        output = result.str();
        return output.c_str();
    }

    /**
     * Parses the specefied file within the command line arguments and updates our content Vector
     * 
     * @param file The path to the file to be parsed
     */
    void parse_file (const std::string& file);

    /**
     * Writes the concatonated content to a file
     * 
     * @param file_name The name of the file we want to write content too
     */
    void write_to_file (const std::string& file_name);

    /**
     * Redirect files and concatonates those files into a new file
     * 
     * @param args Takes the arguments from the CLI and parses files before the < 
     *              Which then it writes it into the file we want to insert into
     */
   void redirect_to_file (const std::vector<std::string>& args, Cat& cat);
};