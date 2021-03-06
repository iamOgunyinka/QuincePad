#include "metadata.h"

using namespace QuincePad;

struct Tokens::KeyWords
{
    KeyWords(const std::initializer_list< std::string > & list ): i_list { list } { }
    KeyWords(std::initializer_list<std::string> &&list): i_list(std::move(list)) { }
    std::set<std::string>::iterator find( const std::string & str)const {
        return i_list.find(str);
    }
    std::set<std::string> i_list;
};

struct Tokens::KeyHash {
    size_t operator()(const Tokens::KeyWords &a) const {
        return std::hash< std::string > ()(*a.i_list.begin()) << 2;
    }
};
struct Tokens::KeyEqual {
    bool operator()(const Tokens::KeyWords &a, const Tokens::KeyWords &b) const {
        return *a.i_list.begin() == *b.i_list.begin();
    }
};

Tokens::Tokens(const KeyWords &key, Language lang) {
    Tokens::tokens.insert( { key, lang });
}
void Tokens::insert(const std::initializer_list< std::string > & obj, Language lang){
    Tokens::tokens.insert( { obj, lang });
}

std::unordered_map<Tokens::KeyWords, Language, Tokens::KeyHash, Tokens::KeyEqual> Tokens::tokens;

void Tokens::INIT_KEYWORDS_TABLE()
{
    Tokens::tokens.insert( {{ "cpp", "c++", "1" }, Language::CPP } );
    Tokens::tokens.insert( {{ "pascal", "pas", "2" }, Language::PASCAL } );
    Tokens::tokens.insert( {{ "perl", "3" }, Language::PERL } );
    Tokens::tokens.insert( {{ "python", "py", "4"}, Language::PYTHON } );
    Tokens::tokens.insert( {{ "fortran", "fort", "for", "5" }, Language::FORTRAN } );
    Tokens::tokens.insert( {{ "whitespace", "white space", "white", "6" }, Language::WHITESPACE } );
    Tokens::tokens.insert( {{ "ada", "7" }, Language::ADA } );
    Tokens::tokens.insert( {{ "ocaml", "caml", "8", "o_caml" }, Language::OCAML } );
    Tokens::tokens.insert( {{ "intercal", "i_cal", "9" }, Language::INTERCAL } );
    Tokens::tokens.insert( {{ "java", "10" }, Language::JAVA } );
    Tokens::tokens.insert( {{ "c", "C", "11" }, Language::C } );
    Tokens::tokens.insert( {{ "brainfuck", "brain fuck", "bf", "12" }, Language::BRAINFUCK } );
    Tokens::tokens.insert( {{ "asm", "13" }, Language::ASM } );
}

Language Tokens::getLanguage(const std::string &str) {
    if ( tokens.empty() ){
        INIT_KEYWORDS_TABLE();
    }
    //change str to lower case
    std::string temp { };
    std::transform( str.cbegin(), str.cend(), std::back_inserter(temp), [](const char c)-> char { return ::tolower(c); });

    for(const auto &i: Tokens::tokens){
        if(i.first.find(temp) != i.first.i_list.cend()){
            return i.second;
        }
    }
    return Language::NONE;
}
