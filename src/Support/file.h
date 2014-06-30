#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

namespace QuincePad
{
    using s_iterator = std::string::const_iterator;
    using pairs_iterator = std::pair<s_iterator, s_iterator>;
    static pairs_iterator findPairFrom(const std::string &text, const std::string &a, const std::string &b,
                                        bool lastOfB = false)
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
    /*
    static void replace(std::string &text, const std::string &searchString, const std::string &replaceString)
    {
        //
    }
    */
    static std::vector<std::string> splitStringBy( const std::string &a, const char &b )
    {
        std::vector<std::string> temp { };
        std::string tempStr = a;
        auto found = std::find( tempStr.cbegin(), tempStr.cend(), b );
        while( found != a.cend() ){
            temp.push_back( std::string { tempStr.cbegin(), found } );
            tempStr = std::string { found + 1, tempStr.cend() };
            found = std::find( tempStr.cbegin(), tempStr.cend(), b );
        }
        return temp;
    }

    struct File
    {
        File() = delete;
        File(const File &)= delete;
        File(const std::string &filename): source( *(new std::ifstream{filename})) { }
        ~File() { delete &source; }
        std::string readAll() const
        {
            std::string allString { };
            if( !source ) { throw std::string { "Unable to open file" }; }
            else {
                while(!atEnd()){
                    allString += readLine();
                }
            }
            return allString;
        }

        bool atEnd() const { return source.eof(); }
        std::string readLine() const
        {
            std::string curr_line {};
            std::getline(source, curr_line);
            curr_line.push_back('\n');
            return curr_line;
        }
        operator bool () {
            return source.is_open();
        }
    private:
        std::ifstream &source;
    };

    
}
#endif
