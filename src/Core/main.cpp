#include <iostream>
#include "lexer.h"
#include <chrono>
#include <algorithm>
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
    std::vector<std::string> foo;
    QuincePad::File _file( "/home/matrix/QuincePAD/doc.txt" );
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    
    QuincePad::Lex::Lexer::extractCodeTags(_file, foo );
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::cout << "findPairFrom took " << seconds.count() << "s\n";
    for(const auto &i: foo) { std::cout << i << std::endl; }
    return 0;
}
