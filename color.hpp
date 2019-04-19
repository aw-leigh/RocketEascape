// adapted from: https://pastebin.com/zWC3t9hC
// color code reference https://misc.flogisoft.com/bash/tip_colors_and_formatting

#ifndef COLOR_HPP
#define COLOR_HPP

#include <ostream>

namespace Color {
    enum Code 
    {
        FG_DEFAULT      = 39,
        FG_BLACK        = 30,
        FG_RED          = 31,
        FG_GREEN        = 32,
        FG_YELLOW       = 33,
        FG_BLUE         = 34,
        FG_MAGENTA      = 35,
        FG_CYAN         = 36,
        FG_LIGHT_GRAY   = 37,
        FG_DARK_GRAY    = 90,
        FG_LIGHT_RED    = 91,
        FG_LIGHT_GREEN  = 92,
        FG_LIGHT_YELLOW = 93, 
        FG_LIGHT_BLUE   = 94, 
        FG_LIGHT_MAGENTA = 95, 
        FG_LIGHT_CYAN   = 96, 
        FG_WHITE        = 97,
        BG_DEFAULT      = 49, 
        BG_RED          = 41, 
        BG_GREEN        = 42,
        BG_YELLOW       = 43, 
        BG_BLUE         = 44,
        BG_MAGENTA      = 45,
        BG_CYAN         = 46,
        BG_LIGHT_GRAY   = 47, 
        BG_DARK_GRAY    = 100,  
        BG_LIGHT_RED    = 101,
        BG_LIGHT_GREEN  = 102,
        BG_LIGHT_YELLOW = 103, 
        BG_LIGHT_BLUE   = 104, 
        BG_LIGHT_MAGENTA = 105, 
        BG_LIGHT_CYAN   = 106,
        BG_WHITE        = 107
    };
    std::ostream& operator<<(std::ostream& os, Code code);
}

#endif  //color

/*  Example use:

    cout << "This ->" << Color::FG_RED << Color::BG_GREEN << "word"
         << Color::FG_DEFAULT << Color::BG_DEFAULT << "<- is red with a green background." << endl;

*/