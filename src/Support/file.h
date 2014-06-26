#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>

namespace QuincePad
{
    struct File
    {
        File() = delete;
        File(const File &)= delete;
        File(const std::string &filename);
        ~File();
        std::string readAll () const;
        bool atEnd() const;
        std::string readLine() const;
        operator bool () {
            return source.is_open();
        }
    private:
        std::ifstream &source;
    };
    using s_iterator = std::string::const_iterator;
    using pairs_iterator = std::pair<s_iterator, s_iterator>;
    pairs_iterator findPairFrom(const std::string &text, const std::string &a,
                                                    const std::string &b, bool lastOfB = false);
    void replace(std::string &text, const std::string &searchString, const std::string &replaceString);
}
#endif
