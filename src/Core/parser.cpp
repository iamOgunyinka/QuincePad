#include "parser.h"

using namespace QuincePad::Parse;
using namespace QuincePad::Lex;

Parser::Parser(Lexer &m_lexer): lexer(m_lexer), meta(m_lexer.size())
{
    parseToken( lexer, meta );
}

Parser::~Parser()
{
    //
}
void Parser::parseToken(Lexer &m_lexer, std::vector<MetaData> &m_meta)
{
    std::string codeAttributes { };
    for( std::vector<std::string>::size_type i = 0; i != m_lexer.size(); ++i ){
        getCodeTagAttributes( m_lexer[i], codeAttributes );
        m_meta[i].n_code = getNormalCode(m_lexer[i], codeAttributes);
        if( !codeAttributes.empty() ){
            getMetaData( codeAttributes, m_meta[i] );
        }
    }
}

void Parser::getMetaData(const std::string &data, MetaData &metadatas)
{
    MetaData temp { };
    const char comma = ',';
    auto find_str = std::find(data.cbegin(), data.cend(), comma );
    if ( find_str == data.cend() ) {
        metadatas = MetaData { };
        return;
    } else {
        auto container = QuincePad::splitStringBy( data, comma );
        for( const auto &i: container ){
            if( i.find( "input" ) != std::string::npos ) {
                temp.input = getValue( i );
            } else if ( i.find( "lang" ) != std::string::npos ) {
                temp.lang = Tokens::getLanguage( getValue( i ) );
            } else if ( i.find( "run" ) != std::string::npos ) {
                temp.run_code = ( getValue( i ) == std::string { "true" } ? true : false );
            } else if ( i.find( "private" ) != std::string::npos ) {
                temp.privacy = ( getValue( i ) == std::string { "true" } ? true :
                                getValue( i ) == std::string { "1" } ? true : false );
            } else {
                continue;
            }
        }
    }
    metadatas = std::move( temp );
}

inline void Parser::getCodeTagAttributes( const std::string &text, std::string &data )
{
    auto find_iter = std::find( text.cbegin(), text.cend(), ']' );
    if( find_iter != text.cend() && find_iter != text.crend().base() ) {
        data = std::string( text.cbegin(), find_iter + 1 );
    }
}

inline std::string Parser::getValue( const std::string &data )
{
    auto found = findQuotesFrom( data, "\"", "\"", true );
    return std::string { found.first, found.second };
}

inline std::string Parser::getNormalCode(const std::string &text, const std::string &str)
{
    auto foundCloseTag = text.find("[/code]");
    std::string foo = text.substr(str.size(), 7
    return foo;
}
