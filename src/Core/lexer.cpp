#include "lexer.h"

using namespace QuincePad;
using namespace StringFunctions;
using namespace Lex;

Lexer::Lexer(const std::string &filename): code_tag {}, file ( filename )
{
        extractCodeTags(file, code_tag);
}

Lexer::~Lexer() {
    //
}

void Lexer::extractCodeTags(File &file, std::vector<std::string> &container)
{
    std::string openTag { "[code" }, closeTag { "[/code]" };
    if( file ){
        std::string allFileContent { file.readAll() };
        bool mergeWithCodeTags = true;
        auto iter = findPairFrom(allFileContent, openTag, closeTag, mergeWithCodeTags);
        while(iter.first != allFileContent.end() && iter.second != allFileContent.end())
        {
            container.push_back( std::string(iter.first, iter.second) );
            allFileContent = std::string (iter.second, allFileContent.cend());
            iter = findPairFrom(allFileContent, openTag, closeTag, mergeWithCodeTags);
        }
    } else {
        printf("Specified file not found");
    }
}
Lexer::size_type Lexer::size() const { return code_tag.size(); }
Lexer::iterator Lexer::begin() { return code_tag.begin(); }
Lexer::iterator Lexer::end() { return code_tag.end(); }
Lexer::const_iterator Lexer::cbegin() { return code_tag.cbegin(); }
Lexer::const_iterator Lexer::cend() { return code_tag.cend(); }
