#include <iostream>

int main(){
    char ch;

    std::istream* ip = &std::cin;
    std::string num;
    do{
        if(!ip -> get(ch)) return 0;
        std::cout << ch << std::endl;
    }while(ch != '\n' && std::isspace(ch));

    ip->putback(ch);
    *ip >> num;
    std::cout << num << std::endl;
}