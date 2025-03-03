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

    if (cli.found("n"))
        cat.is_line_numbers = true;
    if (cli.found("w"))
        cat.write_mode = true;

    if (cat.write_mode) {
            cat.write_to_file(cli.args[0]);
            
    } else {
        for (auto& arg : cli.args) 
            cat.parse_file(arg);
    }

   
    std::cout << cat;

    return 0;
}