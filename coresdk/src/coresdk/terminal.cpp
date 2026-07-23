//
//  terminal.cpp
//  splashkit
//
//  Created by Andrew Cain on 8/10/16.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include <easylogging++.h>
#include "types.h"
#include <iostream>
#include <map>
#include <limits>
#include <utility>

namespace splashkit_lib
{
    void write(std::string text)
    {
        std::cout << text;
        std::cout.flush();
    }

    void write(int data)
    {
        write(std::to_string(data));
    }

    void write(char data)
    {
        write(std::string("") + data);
    }

    void write(double data)
    {
        write(std::to_string(data));
    }

    void write_line()
    {
        std::cout << std::endl;
        std::cout.flush();
    }

    void write_line(std::string line)
    {
        std::cout << line << std::endl;
        std::cout.flush();
    }

    void write_line(int data)
    {
        write_line(std::to_string(data));
    }

    void write_line(double data)
    {
        write_line(std::to_string(data));
    }

    void write_line(char data)
    {
        write_line(std::string(1, data));
    }

    std::string read_line()
    {
        std::string result;
        std::cin.clear();
        std::cin.sync();
        getline(std::cin, result);
        return result;
    }

    char read_char()
    {
        char result = 0;
        std::cin.clear();
        std::cin.sync();
        std::cin >> result;
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return result;
    }

    bool terminal_has_input()
    {
        return std::cin.gcount() > 0;
    }
}
