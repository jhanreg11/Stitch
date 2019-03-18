#include <iostream>
#include <fstream>
#include <stack>
#include <string>


using namespace std;

int main() {
    ifstream fin;
    string fileName, buffer, line;
    stack<double> digits;
    char curr;
    stack<string> strings, operators, keywords, identifiers, literals;
    string keywordList[] = {"if", "else", "while", "for", "int", "double", "bool", "char", "string", "true", "false", "continue", "break", "main", "return"}; //{"asm", "auto", "bool", "break", "case", "catch", "char", "class", "const", "const_cast", "continue", "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float", "for", "friend", "if", "inline", "int", "long", "mutable", "namespace", "new", "operator", "private", "protected", "public", "register", "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_cast", "struct", "switch", "template", "this", "throw", "true", "try", "typedef", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while"};
    
    do {
        cout <<"Enter the filename: ";
        getline(cin, fileName);
        fin.open(fileName);
    } while (!fin);
    
    //cout << "Enter the line to be lexed: ";
    //getline(cin, line);
    
    while (fin.get(curr)) {
            
        //Finds Digits
        if (isdigit(curr)) {
            buffer += curr;
            while (fin.get(curr) && (isdigit(curr) || curr == '.')) {
                if (isdigit(curr) || curr == '.') {
                    if (!buffer.find("."))
                        break;
                    else
                        buffer += curr;
                }
                else break;
            }
                
            string::size_type sz;
            digits.push(stod(buffer, &sz));
            buffer = "";
        }
            
        //Finds Identifiers
        else if (isalpha(curr) || curr == '_') {
            buffer += curr;
            while (isalnum(curr) || curr == '_') {
                buffer += curr;
            }
            strings.push(buffer);
            buffer = "";
        }
            
        //Finds Operators
        else if (ispunct(curr)) {
            cout <<"found operator\n";
            buffer += curr;
            while (fin.get(curr)) {
                if (ispunct(curr)) {
                    cout <<"Entering switch\n";
                    switch (buffer[0]) {
                        case '+': if (curr == '+' || curr == '=') buffer += curr;
                            else return 69;
                            break;
                        case '-': if (curr == '-' || curr == '=') buffer += curr;
                            else return 69;
                            break;
                        case '/': if (curr == '/' || curr == '=') buffer += curr;
                            else return 69;
                            break;
                        case '*': if (curr == '=') buffer += curr;
                            else return 69;
                            break;
                        case '%': if (curr == '=') buffer += curr;
                            else return 69;
                            break;
                        case '>': if (curr == '=') buffer += curr;
                            else return 69;
                            break;
                        case '<': if (curr == '=') buffer += curr;
                            else return 69;
                            break;
                        case '=': if (curr == '=') buffer += curr;
                            else return 69;
                            break;
                        case '|': if (curr == '|') buffer += curr;
                            else return 69;
                            break;
                        case '&': if (curr == '&') buffer += curr;
                            else return 69;
                    }
                }
                else {
                    operators.push(buffer);
                    buffer = curr;
                }
            }
                operators.push(buffer);
                buffer = "";
        }
        //Finds string literals;
        else if (buffer[0] == '"') {
            buffer = "";
            while (curr != '"')
                buffer += curr;
            literals.push(buffer);
            buffer = "";
        }
        else {
            operators.push(buffer);
            buffer = "";
        }
    }
        //cout <<"Enter the next line (enter nothing to stop lexing): ";
        //getline (cin, line);
    
    //Separates keywords from identifiers
   while (!strings.empty()) {
       string top = strings.top();
       bool keyword = false;
        for (int i = 0; i < 13; ) {
            if (top == keywordList[i]) {
                keyword = true;
                break;
            }
        }
       if (keyword == true)
           keywords.push(top);
       else
           identifiers.push(top);
       strings.pop();
    }
    
    
    //Prints out all found lexemes categorized
    cout <<"All found digits: \n";
    while (!digits.empty()) {
        cout <<digits.top() <<endl;
        digits.pop();
    }
    
    cout <<"\n\nAll found operators: \n";
    while (!operators.empty()) {
        cout <<operators.top() <<endl;
        operators.pop();
    }
    
    cout <<"\n\nAll found identifiers: \n";
    while (!identifiers.empty()) {
        cout <<identifiers.top() <<endl;
        identifiers.pop();
    }
    
    cout <<"\n\nall found keywords: \n";
    while (!keywords.empty()) {
    string t = keywords.top();
        cout <<t <<endl;
        keywords.pop();
    }
    
    cout <<"\n\nall found literals: \n";
   while (!literals.empty()) {
        cout <<literals.top() <<endl;
        literals.pop();
   }
    return 0;
}


