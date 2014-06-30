#include "parser.h"

using namespace QuincePad::Parse;
using namespace QuincePad::Lex;

//[code, lang="php", run=1, input= "12 15"]

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
        auto container = QuincePad::splitStringBy(data, comma);
        for( const auto &i: container ){
            printf("%s\n", i.c_str());// << std::endl;
        }
    }
}

inline void Parser::getCodeTagAttributes( const std::string &text, std::string &data )
{
    auto find_iter = std::find( text.cbegin(), text.cend(), ']' );
    if( find_iter != text.cend() && find_iter != text.crend().base() ) {
        data = std::string( text.cbegin(), find_iter + 1 );
    }
    printf( "In getCodeAttribute: with text = %s and data = %s\n", text.c_str(), data.c_str() );
}

inline std::string Parser::getValue( const std::string &data )
{
    auto found = findPairFrom( data, "\"", "\"" );
    return std::string { found.first, found.second };
}
    
