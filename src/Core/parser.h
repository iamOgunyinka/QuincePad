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
            
            void parseToken( Lexer &m_lexer, std::vector<MetaData> &m_meta );
            static void getToken( Lexer &lexer, MetaData &meta );
            static inline void getMetaData( const std::string &data, MetaData &metadatas );
            static inline void getCodeTagAttributes( const std::string &text, std::string &data );
            static inline std::string getValue( const std::string & data );
            static inline std::string getNormalCode(const std::string &text, const std::string &str);
        private:
            Lexer &lexer;
            std::vector<MetaData> meta;
        };
    }
}

#endif
