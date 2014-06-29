#include "metadata.h"

using namespace QuincePad;

struct Tokens
{
    struct KeyWords
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
    struct KeyHash {
        size_t operator()(const KeyWords &a) const {
            return std::hash< std::string > ()(*a.i_list.begin()) << 2;
        }
    };
    struct KeyEqual {
        bool operator()(const KeyWords &a, const KeyWords &b) const {
            return *a.i_list.begin() == *b.i_list.begin();
        }
    };
    
    Tokens(const KeyWords &tk, MetaData tl): kmap { } {
        tokens.insert( { tk, tl });
    }
    void insert(const std::initializer_list< std::string > & obj, MetaData tk){
        tokens.insert( { obj, tk });
    }
    
};
Tokens::Language find(const std::string &str)
