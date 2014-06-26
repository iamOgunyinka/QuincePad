#include "parser.h"

using namespace QuincePad::Parse;
using namespace QuincePad::Lex;

Parser::Parser(Lexer &m_lexer): lexer(m_lexer), meta(m_lexer.size())
{
    parseToken(lexer, meta);
}

void Parser::parseToken(Lexer &m_lexer, std::vector<MetaData> &m_meta)
{
    for(std::vector<std::string>::size_type i = 0; i != m_lexer.size(); ++i){
        getMetaData( m_lexer[i], m_meta[i] );
    }
}

void Parser::getMetaData(const std::string &data, MetaData &metadatas)
{
    
}
