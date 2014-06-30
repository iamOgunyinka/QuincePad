#include <iostream>
#include "parser.h"

#include <chrono>
#include <algorithm>
using namespace QuincePad;
using namespace Lex;
using namespace Parse;

/**
using s_iterator = std::string::const_iterator;
using pairs_iterator = std::pair<s_iterator, s_iterator>;

pairs_iterator findPairFrom(const std::string &text, const std::string &a, const std::string &b, bool lastOfB)
{
    std::string::size_type found_first = text.find(a), found_second { };
    if(found_first != std::string::npos )
    {
        found_second = text.substr(found_first).find(b);
        if(found_second != std::string::npos){
            std::string::const_iterator first = text.cbegin() + found_first,
                                        second = first + found_second + (lastOfB ? b.size() : 0);
            return { first, second };
        }
    }
    return { text.end(), text.end() };
}

pairs_iterator findPairFrom(std::string::const_iterator f, std::string::const_iterator s,
            const std::string &a, const std::string &b)
{
    auto found_first = std::search(f, s, a.cbegin(), a.cend());
    if( found_first != s )
    {
        auto found_second = std::search(found_first, s, b.cbegin(), b.cend());
        if(found_second != s){
            return { found_first, found_second };
        }
    }
    return { s, s };
}
**/

int main(int argc, char **argv)
{
    std::string filename { "/home/matrix/QuincePAD/doc.txt" };
    if( argc > 1 ) {
        filename = argv[1];
    }
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    
    Lexer lex ( filename );
    Parser parse( lex );

    //~ for(int i = 0; i != lex.size(); ++i) { std::cout << lex[i] << std::endl; }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::cout << "The lexer spent " << seconds.count() << "seconds " << std::endl;
    return 0;
}

/*
g++ -std=c++11 -o main lexer.h lexer.cpp parser.h parser.cpp ../Support/file.h ../Support/metadata.h ../Support/metadata.cpp main.cpp
*/
