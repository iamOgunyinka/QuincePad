#ifndef METADATA_H
#define METADATA_H

#include <unordered_map>
#include <set>
#include <string>

namespace QuincePad
{
    template<class T, class U>
    struct pair
    {
        pair(): pair(T {}, T {}) { }
        pair& operator=(const pair<T, U> &_pair) = delete;
        
        pair(const T &first, const U &second): original(first), transformed(second) { }
        pair(T &&first, U &&second): original(std::move(first)), transformed(std::move(second)) { }
        pair(pair<T, U> && _pair): original(std::move(_pair.original)),
                                   transformed(std::move(_pair.transformed)) { }

        pair& operator=(pair<T, U> && _pair){
            std::swap(this->original, _pair.original);
            std::swap(this->transformed, _pair.transformed);
            _pair.original = T { };
            _pair.transformed = U {};
            return *this;
        }
        
        T original;
        U transformed;
    };
    enum class Language
    {
        NONE = 0, CPP, PASCAL, PERL, PYTHON, FORTRAN, WHITESPACE, ADA, OCAML, INTERCAL, JAVA,
        C, BRAINFUCK, ASM, CLIPS, PROLOG_SWI, ICON, RUBY, PIKE, HASKELL, PASCAL_FPC,
        SMALLTALK, NICE, LUA, CSHARP, BASH, PHP, NERMELE, C_LISP, SCHEME, C99_STRICT,
        JAVASCRIPT, ERLANG, TCL, SCALA, SQL, OBJECTIVE_C, CPP_0X, ASSEMBLER, PERL_6, VB_DOTNET,
        D_CMD, AWK_GAWK, AWK_MAWK, COBOL_85, FORTH, PROLOG, BC, CLOJURE, JAVASCRIPT_MONKEY, GO,
        UNLAMBDA, PYTHON_3, R, COBOL, OZ, GROOVY, NIMROD, FACTOR, F_SHARP, FALCON
    };
    struct MetaData
    {
        typedef bool code_privacy;
        
        MetaData(): MetaData("", Language::NONE, false, false) { }
        MetaData(const std::string &p_input, Language p_lang, bool p_run, code_privacy p_privacy):
            input(p_input), lang(p_lang), run_code(p_run), privacy(p_privacy) { }
            
        MetaData(const MetaData &) = default; //No way can a code have the same metadata
        MetaData(MetaData && data): input(std::move(data.input)), lang(data.lang), run_code(data.run_code),
            privacy(data.privacy) { }
        MetaData& operator=(MetaData &&data) {
            std::swap(data.input, input); data.input = std::string {};
            lang = data.lang; data.lang = Language::NONE;
            run_code = data.run_code; data.run_code = false;
            privacy = data.privacy; data.privacy = false;
            return *this;
        }

        std::string input;
        Language lang;
        bool run_code;
        code_privacy privacy;
    };
    struct Tokens
    {
        struct KeyWords;
        struct KeyHash;
        struct KeyEqual;
        Tokens(const KeyWords &key, Language lang);
        void insert(const std::initializer_list< std::string > & obj, Language lang);
        static std::unordered_map<KeyWords, Language, KeyHash, KeyEqual> tokens;
        static Language find(const std::string &str);
        static void INIT_KEYWORDS_TABLE();

    };
}// namespace QuincePad

#endif
