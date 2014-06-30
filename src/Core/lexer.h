#ifndef LEXER_H
#define LEXER_H

#include "../Support/file.h"

namespace QuincePad
{
    namespace Lex
    {
        struct Lexer
        {
            using size_type = typename std::vector<std::string>::size_type;
            using iterator = typename std::vector<std::string>::iterator;
            using const_iterator = typename std::vector<std::string>::const_iterator;
            
            Lexer() = delete;
            Lexer(const std::string &filename);
            ~Lexer();
            
            std::string &operator[](const int &i) {
                return code_tag[i];
            }
            iterator begin();
            iterator end();
            const_iterator cbegin();
            const_iterator cend();
            size_type size();
            static void extractCodeTags(File &, std::vector<std::string> & container);

        private:
            std::vector<std::string> code_tag;
            File file;
        };
        
    }
    
}

#endif
