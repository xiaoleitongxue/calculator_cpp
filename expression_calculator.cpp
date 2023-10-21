#include <iostream>
#include <string>
#include <unordered_map>
std::unordered_map<std::string, double> table;

// function prototype
double error(const std::string &s);
double expr(bool get);
double term(bool get);
double prim(bool get);

int no_of_errors;
double error(const std::string &s)
{
    no_of_errors++;
    std::cerr << "error: " << s << '\n';
    return 1;
}

enum class Kind : char
{
    name,
    number,
    end,
    plus = '+',
    minus = '-',
    mul = '*',
    div = '/',
    print = ';',
    assign = '=',
    lp = '(',
    rp = ')'
};

struct Token
{
    Kind kind;
    std::string string_value;
    double number_value;
};

class Token_stream
{
public:
    Token_stream(std::istream &s) : ip{&s}, owns{false}
    {
    }

    Token_stream(std::istream *p) : ip{p}, owns{true} { close(); }

    ~Token_stream() { close(); }
    Token get();
    Token &current();

    void set_input(std::istream &s)
    {
        close();
        ip = &s;
        owns = false;
    }
    void set_input(std::istream *p)
    {
        close();
        ip = p;
        owns = true;
    }

private:
    void close()
    {
        if (owns)
            delete ip;
    }
    std::istream *ip;
    bool owns;
    Token ct{Kind::end};
};

Token_stream ts{std::cin};

double prim(bool get)
{
    if (get)
        ts.get();

    switch (ts.current().kind)
    {
    case Kind::number:
    {
        double v = ts.current().number_value;
        ts.get();
        return v;
    }
    case Kind::name:
    {
        double &v = table[ts.current().string_value];
        if (ts.get().kind == Kind::assign)
            v = expr(true);
        return v;
    }
    case Kind::minus:
    {
        return -prim(true);
    }

    case Kind::lp:
    {
        auto e = expr(true);
        if (ts.current().kind != Kind::rp)
            return error("')' expected");
        ts.get();
        return e;
    }
    default:
    {
        return error("primary expected");
    }
    }
}

double term(bool get)
{
    double left = prim(get);
    for (;;)
    {
        switch (ts.current().kind)
        {
        case Kind::mul:
        {
            left *= prim(true);
            break;
        }
        case Kind::div:
        {
            if (auto d = prim(true))
            {
                left /= d;
                break;
            }
            return error("divide by 0");
        }
        default:
            return left;
        }
    }
}

double expr(bool get)
{
    double left = term(get);
    for (;;)
    {
        switch (ts.current().kind)
        {
        case Kind::plus:
        {
            left += term(true);
            break;
        }

        case Kind::minus:
        {
            left -= term(true);
            break;
        }

        default:
            return left;
        }
    }
}

Token &Token_stream::current()
{
    // TODO: insert return statement here
    return ct;
}

Token Token_stream::get()
{

    char ch;
    do{
        if(!ip -> get(ch)) return ct={Kind::end};
    }while(ch != '\n' && std::isspace(ch));
    //*ip >> ch;

    switch (ch)
    {
    // case 0:
    //     return ct = {Kind::end};
    case ';':
    case '\n':
        return ct = {Kind::print};
    case '*':
    case '/':
    case '+':
    case '-':
    case '(':
    case ')':
    case '=':
        return ct = {static_cast<Kind>(ch)};
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
        ip->putback(ch);
        *ip >> ct.number_value;
        ct.kind = Kind::number;
        return ct;
    default:
        if (isalpha(ch))
        {
            ct.string_value = "";
            ct.string_value.push_back(ch);
            while(ip -> get(ch) && isalnum(ch))
                ct.string_value += ch;
            ip -> putback(ch);
            ct.kind = Kind::name;
            return ct;
        }

        // bad token
        error("bad token");
        return ct = {Kind::print};
    }
}

void calculate()
{
    for (;;)
    {
        ts.get();
        if (ts.current().kind == Kind::end)
            break;
        if (ts.current().kind == Kind::print)
            continue;
        std::cout << expr(false) << '\n';
    }
}

int main()
{
    table["pi"] = 3.14;
    table["e"] = 2.71;
    calculate();
    return no_of_errors;
}