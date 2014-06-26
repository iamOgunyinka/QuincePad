#include "file.h"

using namespace QuincePad;

File::File(const std::string &filename): source( *(new std::ifstream{filename})) { }

std::string File::readAll() const
{
    std::string allString { };
    if( !source ) {
        throw std::string { "Unable to open file" };
    } else {
        while(!atEnd()){
            allString += readLine();
        }
    }
    return allString;
}

bool File::atEnd () const
{
    return source.eof();
}

std::string File::readLine() const
{
    std::string curr_line {};
    std::getline(source, curr_line);
    curr_line.push_back('\n');
    return curr_line;
}

File::~File()
{
    delete &source;
}

pairs_iterator QuincePad::findPairFrom(const std::string &text, const std::string &a, const std::string &b, bool lastOfB)
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

void QuincePad::replace(std::string &text, const std::string &searchString, const std::string &replaceString)
{
    //text.replace(, searchString.size(), replaceString);
}
