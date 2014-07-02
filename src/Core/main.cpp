#include "parser.h"
#include <chrono>
#include <iostream>

using namespace QuincePad;
using namespace Lex;
using namespace Parse;

int main(int argc, char **argv)
{
    std::string filename { "/home/matrix/QuincePAD/doc.txt" };
    if( argc > 1 ) {
        filename = argv[1];
    }
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    
    Parser parse( filename );

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::cout << "The lexer spent " << seconds.count() << "seconds " << std::endl;
    return 0;
}
