#include "parser.h"

using namespace QuincePad::Parse;
using namespace QuincePad::Lex;
using namespace QuincePad::StringFunctions;

Parser::Parser(Lexer &m_lexer): lexer_ptr(nullptr), lexer( m_lexer ), meta(m_lexer.size())
{
    parseToken( lexer, meta );
}

Parser::Parser(const std::string &filename): lexer_ptr(new Lexer{ filename }), lexer( *lexer_ptr ),
                                             meta( lexer.size() )
{
    parseToken( lexer, meta );
}                                     

Parser::~Parser() = default;

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
    const char comma = ',';
    auto find_str = std::find(data.cbegin(), data.cend(), comma );
    if ( find_str == data.cend() ) {
        return;
    } else {
        auto container = splitStringBy( data, comma );
        for( const auto &i: container ){
            if( i.find( "input" ) != std::string::npos ) {
                metadatas.input = getValue( i );
            } else if ( i.find( "lang" ) != std::string::npos ) {
                metadatas.lang = Tokens::getLanguage( getValue( i ) );
            } else if ( i.find( "run" ) != std::string::npos ) {
                metadatas.run_code = ( getValue( i ) == std::string { "true" } ? true :
                                getValue( i ) == std::string { "1" } ? true : false );
            } else if ( i.find( "private" ) != std::string::npos ) {
                metadatas.privacy = ( getValue( i ) == std::string { "true" } ? true :
                                getValue( i ) == std::string { "1" } ? true : false );
            }
        }
    }
    printf("MetaData: input => %s -- n_code => %s -- lang = %d -- run_code => %d -- privacy => %d\n",
            metadatas.input.c_str(), metadatas.n_code.c_str(), (int)metadatas.lang, (int)metadatas.run_code,
            metadatas.privacy );
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
    std::string closeTag { "[/code]" };
    return { text.cbegin() + str.size(), text.cbegin() + text.find(closeTag) };
}
