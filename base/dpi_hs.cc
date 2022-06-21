//
// Created by Administrator on 2022/6/21.
//

#include "dpi_hs.h"

dpi_hs::dpi_hs(const char *filename, hs_database_t **db_block) {
    vector<string> patterns;
    vector<unsigned> flags;
    vector<unsigned> ids;

    parseFile(filename, patterns, flags, ids);

    //解析pattern
    for (int i = 0; i < patterns.size(); i++) {
        cout << patterns[i] << endl;
    }
    //解析flags
    for (int j = 0; j < flags.size(); j++) {
        cout << flags[j] << endl;
    }
    //解析ids
    for (int k = 0; k < flags.size(); k++) {
        cout << ids[k] << endl;
    }

    vector<const char *> cstrPatterns;
    for (const auto &pattern : patterns) {
        cstrPatterns.push_back(pattern.c_str());
    }

    cout << "Compiling Hyperscan databases with " << patterns.size()
    << " patterns." << endl;

    *db_block = buildDatabase(cstrPatterns, flags, ids, HS_MODE_BLOCK);
}

dpi_hs::~dpi_hs() {
    hs_free_database(db_block);
}

hs_database_t *dpi_hs::buildDatabase(const vector<const char *> &expressions,
                                    const vector<unsigned> flags,
                                    const vector<unsigned> ids,
                                    unsigned int mode){
    hs_database_t *db;
    hs_compile_error_t *compileErr;
    hs_error_t err;

    err = hs_compile_multi(expressions.data(), flags.data(), ids.data(), expressions.size(),
                           mode, nullptr, &db, &compileErr);
    if (err != HS_SUCCESS){
        if (compileErr->expression < 0) {
            // The error does not refer to a particular expression.
            cerr << "ERROR: " << compileErr->message << endl;
        } else {
            cerr << "ERROR: Pattern '" << expressions[compileErr->expression]
            << "' failed compilation with error: " << compileErr->message
            << endl;
        }
        hs_free_compile_error(compileErr);
        exit(-1);
    }

    return db;
}

int dpi_hs::parseFile(const char *filename, vector<string> &patterns,
                      vector<unsigned> &flags, vector<unsigned> &ids) {
    ifstream inFile(filename);
    if (!inFile.good()) {
        cerr << "ERROR: Can't open pattern file \"" << filename << "\"" << endl;
        exit(-1);
    }
    for (unsigned i = 1; !inFile.eof(); ++i) {
        string line;
        getline(inFile, line);
        if (line.empty() || line[0] == '#') {
            continue;
        }
        size_t colonIdx = line.find_first_of(':');
        if (colonIdx == string::npos) {
            cerr << "ERROR: Could not parse line " << i << endl;
            exit(-1);
        }
        //获取pattern ID
        unsigned id = std::stoi(line.substr(0, colonIdx).c_str());

        const string expr(line.substr(colonIdx + 1));
        size_t flagsStart = expr.find_last_of('/');
        if (flagsStart == string::npos) {
            cerr << "ERROR: no trailing '/' char" << endl;
            exit(-1);
        }
        string pcre(expr.substr(1, flagsStart - 1));
        string flagsStr(expr.substr(flagsStart + 1, expr.size() - flagsStart));
        unsigned flag = parseFlags(flagsStr);

        patterns.push_back(pcre);
        flags.push_back(flag);
        ids.push_back(id);
    }
    return 0;
}

unsigned dpi_hs::parseFlags(const string &flagsStr) {
    unsigned flags = 0;
    for (const auto &c : flagsStr) {
        switch (c) {
            case 'i':
                flags |= HS_FLAG_CASELESS;
                break;
            case 'm':
                flags |= HS_FLAG_MULTILINE;
                break;
            case 's':
                flags |= HS_FLAG_DOTALL;
                break;
            case 'H':
                flags |= HS_FLAG_SINGLEMATCH;
                break;
            case 'V':
                flags |= HS_FLAG_ALLOWEMPTY;
                break;
            case '8':
                flags |= HS_FLAG_UTF8;
                break;
            case 'W':
                flags |= HS_FLAG_UCP;
                break;
            case '\r': // stray carriage-return
                break;
            default:
                cerr << "Unsupported flag \'" << c << "\'" << endl;
                exit(-1);
        }
    }
    return flags;
}
