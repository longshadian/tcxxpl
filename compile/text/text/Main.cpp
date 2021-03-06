#include <iostream>
#include <string>

#include "Log.h"
#include "Lexer.h"
#include "File.h"

#ifndef AXX
# define AXX 10
#endif

void testAllToken(idLexer& lexer)
{
    idToken token{};
    while (!lexer.EndOfToken()) {
        token.Reset();
        if (lexer.GetToken(&token)) {
            LOG(debug) << "token: " << token.AsTypeStringView() << "\t\t" << token.AsStringView();
        } else {
            LOG(warning) << "get token error line: " << lexer.Line();
            break;
        }
    }

    /*
    for (auto c : lexer.GetBuffer()) {
        std::cout << c;
    }
    std::cout << "\n";
    */
}

void testFile()
{
    try {
        const char* fpath = "E:\\gitpro\\estl\\compile\\text\\text\\Lexer.h";
        File f{};
        f.Open(fpath);
        LOG(debug) << "filename: " << f.FileName();
    } catch (std::exception e) {
        LOG(warning) << "testFile exception: " << e.what();
    }
}

int main()
{
    // 哈哈哈你说呢
    LOG(info) << "start main";
    const char* fpath = "E:\\gitpro\\estl\\compile\\text\\text\\Lexer.h";

    idLexer lexer{};
    auto ret = lexer.LoadFile(fpath);
    if (!ret) {
        LOG(warning) << "load file error: " << fpath;
    } else {
        LOG(debug) << "load file success";
    }

    //testAllToken(lexer);
    testFile();

    system("pause");
    return 0;
}

