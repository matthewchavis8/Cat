#include <iostream>
#include <string_view>
#include <algorithm>
#include "include/Cat.hpp"
#include "include/args.hpp"

int main (int argc, char* argv[]) {
    args::ArgParser cli;

    Cat cat;
    cli.flag("n");
    cli.flag("w");
    cli.flag("r");
    cli.flag("e");
    cli.flag("s");

    cli.parse(argc, argv);
    // checks if user wants to output line number
    if (cli.found("n"))
        cat.line_number_mode = true;
    // checks if users wants to write to a file instead
    if (cli.found("w"))
        cat.write_mode = true;
    // check if redirction operator was found in arguments
    if (std::find(cli.args.begin(), cli.args.end(), ">") != cli.args.end())
        cat.redirection_mode = true;
    // check if user wants to reverse the output
    if (cli.found("r"))
        cat.reverse_parse_mode = true;
    // check if user wants to mark the end of line
    if (cli.found("e"))
        cat.mark_end_of_line_mode = true;
    // remove blank line mode
    if (cli.found("s"))
        cat.ignore_blank_line_mode = true;


    if (cat.redirection_mode) {
        cat.redirect_to_file(cli.args, cat);
    } else if (cat.write_mode) {
        cat.write_to_file(cli.args[0]);
    } else {
        for (auto& file : cli.args) 
            cat.parse_file(file);
    }

    std::cout << cat;

    return 0;
}