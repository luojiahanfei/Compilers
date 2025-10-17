#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <sstream>

// Use the standard namespace to make code like 'string' and 'cout' simpler.
using namespace std;

// A constant map to store the ToyC keywords and their token types.
const unordered_map<string, string> KEYWORDS = {
    {"int", "'int'"},
    {"void", "'void'"},
    {"if", "'if'"},
    {"else", "'else'"},
    {"while", "'while'"},
    {"break", "'break'"},
    {"continue", "'continue'"},
    {"return", "'return'"}
};

class Lexer {
public:
    Lexer(const string& source) : source_code(source), code_index(0), token_index(0) {}

    void tokenize() {
        while (code_index < source_code.length()) {
            skipWhitespaceAndComments();
            if (code_index >= source_code.length()) {
                break;
            }

            char current_char = source_code[code_index];

            if (isalpha(current_char) || current_char == '_') {
                processIdentifierOrKeyword();
            } else if (isdigit(current_char)) {
                processNumber();
            } else {
                processOperatorOrPunctuation();
            }
        }
    }

private:
    string source_code;
    size_t code_index;
    int token_index;

    void printToken(const string& type, const string& content) {
        cout << token_index++ << ":" << type << ":\"" << content << "\"" << endl;
    }
    
    char get() {
        return (code_index < source_code.length()) ? source_code[code_index] : '\0';
    }
    
    char getNext() {
        return (code_index + 1 < source_code.length()) ? source_code[code_index + 1] : '\0';
    }

    void advance() {
        code_index++;
    }

    void skipWhitespaceAndComments() {
        while (code_index < source_code.length()) {
            if (isspace(get())) {
                advance();
                continue;
            }
            if (get() == '/' && getNext() == '/') {
                while (get() != '\n' && get() != '\0') advance();
                continue;
            }
            if (get() == '/' && getNext() == '*') {
                advance(); advance();
                while (get() != '\0' && !(get() == '*' && getNext() == '/')) advance();
                if (get() != '\0') {
                    advance(); advance();
                }
                continue;
            }
            break;
        }
    }

    void processIdentifierOrKeyword() {
        size_t start = code_index;
        while (isalnum(get()) || get() == '_') {
            advance();
        }
        string lexeme = source_code.substr(start, code_index - start);

        if (KEYWORDS.count(lexeme)) {
            printToken(KEYWORDS.at(lexeme), lexeme);
        } else {
            printToken("Ident", lexeme);
        }
    }

    void processNumber() {
        size_t start = code_index;
        while (isdigit(get())) {
            advance();
        }
        string lexeme = source_code.substr(start, code_index - start);
        // --- THIS IS THE CORRECTED LINE ---
        printToken("IntConst", lexeme);
    }

    void processOperatorOrPunctuation() {
        char c1 = get();
        char c2 = getNext();
        string two_char_op = {c1, c2};
        string type;

        if (two_char_op == "&&") type = "'&&'";
        else if (two_char_op == "||") type = "'||'";
        else if (two_char_op == "==") type = "'=='";
        else if (two_char_op == "!=") type = "'!='";
        else if (two_char_op == "<=") type = "'<='";
        else if (two_char_op == ">=") type = "'>='";
        
        if (!type.empty()) {
            printToken(type, two_char_op);
            advance(); advance();
        } else {
            string one_char_op = {c1};
            type = "'" + one_char_op + "'";
            printToken(type, one_char_op);
            advance();
        }
    }
};

int main() {
    stringstream buffer;
    buffer << cin.rdbuf();
    string source_code = buffer.str();

    Lexer lexer(source_code);
    lexer.tokenize();

    return 0;
}