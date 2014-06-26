#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "../Support/metadata.h"

namespace QuincePad
{
    using namespace QuincePad::Lex;
    namespace Parse
    {
        struct Parser {
            Parser() = delete;
            Parser(Lexer &m_lexer);
            ~Parser();
            
            void parseToken(Lexer &m_lexer, std::vector<MetaData> &m_meta);
            static void getMetaData(const std::string &data, MetaData &metadatas);
        private:
            Lexer &lexer;
            std::vector<MetaData> meta;
        };
    }
}

#endif
