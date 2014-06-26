all:main

CPPFLAGS+=-std=c++11 -Wall -pedantic -Wextra
CPPFLAGS+=-g -O0

main:Core/lexer.h Core/parser.h Support/file.h \
	 Core/main.cpp Core/lexer.cpp Core/parser.cpp Support/file.cpp Support/metadata.h
	 $(CXX) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)
