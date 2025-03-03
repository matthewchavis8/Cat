#include <iostream>
#include <string_view>
#include "include/Cat.hpp"
#include "include/args.hpp"

int main (int argc, char* argv[]) {
    args::ArgParser cli;

    Cat cat;
    cli.flag("n");
    cli.flag("w");

    cli.parse(argc, argv);

    // checks if user wants to output line number
    if (cli.found("n"))
        cat.is_line_numbers = true;
    // checks if users wants to write to a file instead
    if (cli.found("w"))
        cat.write_mode = true;


    if (cat.write_mode) {
        cat.write_to_file(cli.args[0]);
    } else {
        for (auto& file : cli.args) 
            cat.parse_file(file);
    }

   
    std::cout << cat;

    return 0;
}