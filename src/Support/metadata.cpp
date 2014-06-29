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
//would have specialized std::hash for KeyWords struct but I didn't get the method
//and I don't want that to delay it. So have this
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
    Tokens::tokens.insert( {{ "cpp", "c++", "1" }, Language::CPP });
    Tokens::tokens.insert( {{ "pascal", "pas", "2" }, Language::PASCAL} );
    Tokens::tokens.insert( {{ "perl", "3" }, Language::PERL} );
}

Language Tokens::find(const std::string &str) {
    for(const auto &i: Tokens::tokens){
        if(i.first.find(str) != i.first.i_list.end()){
            return i.second;
        }
    }
    return Language::NONE;
}
