#include <iostream>
#include "include/Cat.hpp"
#include "include/args.hpp"

int main (int argc, char* argv[]) {
    args::ArgParser cli;


    Cat cat;
    cli.flag("n");

    if (cli.found("n"))
        cat.is_line_numbers = true;


    cli.parse(argc, argv);

    for (std::size_t i{}; i < cli.args.size(); i++) 
        cat.parse_file(cli.args[i]);
    
    std::cout << cat;

    return 0;
}