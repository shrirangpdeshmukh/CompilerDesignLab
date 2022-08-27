#include <bits/stdc++.h>
using namespace std;

class Parser
{
private:
    string input;
    int ptr;
    int error;

    void E()
    {
        cout << "Current Input Position: " << (ptr < input.length() ? input[ptr] : '$') << endl;
        cout << "Parsing with E()\n";
        cout << "Calling T() from E()\n";
        T();
        cout << "Calling EPrime() from E()\n";
        EPrime();
    }

    void EPrime()
    {
        cout << "Current Input Position: " << (ptr < input.length() ? input[ptr] : '$') << endl;
        cout << "Parsing with EPrime()\n";
        if (input[ptr] == '+')
        {
            ptr++;
            cout << "Calling T() from EPrime()\n";
            T();
            cout << "Calling EPrime() from EPrime()\n";
            EPrime();
        }
    }

    void T()
    {
        cout << "Current Input Position: " << (ptr < input.length() ? input[ptr] : '$') << endl;
        cout << "Parsing with T()\n";
        cout << "Calling F() from T()\n";
        F();
        cout << "Calling TPrime() from T()\n";
        TPrime();
    }

    void TPrime()
    {
        cout << "Current Input Position: " << (ptr < input.length() ? input[ptr] : '$') << endl;
        cout << "Parsing with TPrime()\n";
        if (input[ptr] == '*')
        {
            ptr++;
            cout << "Calling F() from TPrime()\n";
            F();
            cout << "Calling TPrime() from TPrime()\n";
            TPrime();
        }
    }

    void F()
    {
        cout << "Current Input Position: " << (ptr < input.length() ? input[ptr] : '$') << endl;
        cout << "Parsing with F()\n";
        if (isalnum(input[ptr]))
        {
            ptr++;
        }
        else if (input[ptr] == '(')
        {
            ptr++;
            cout << "Calling E() from F()\n";
            E();
            if (input[ptr] == ')')
            {
                ptr++;
            }
            else
            {
                error = 1;
            }
        }
        else
        {
            error = 1;
        }
    }

public:
    Parser()
    {
        this->ptr = 0;
        this->error = 0;
    }

    bool parse(string s)
    {
        this->input = s;
        E();
        if (ptr == s.size() && error == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("input_3.txt", "r", stdin);
    freopen("output_3.txt", "w", stdout);

    string input;
    cin >> input;

    cout << "Input string: " << input << endl
         << endl;
    Parser parser = Parser();
    bool parsing_result = parser.parse(input);
    if (parsing_result)
    {
        cout << "Successfully Parsed Expression\n";
    }
    else
    {
        cout << "Error Found In Expression\n";
    }

    return 0;
}