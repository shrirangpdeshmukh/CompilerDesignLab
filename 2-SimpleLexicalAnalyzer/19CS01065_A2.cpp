#include <bits/stdc++.h>
using namespace std;

class Token
{
private:
    string token_type;
    string token_value;

public:
    Token()
    {
        this->token_type = " ";
        this->token_value = " ";
    }

    void UpdateToken(string token_type, string token_value)
    {
        this->token_type = token_type;
        this->token_value = token_value;
    }

    void printToken()
    {
        cout << "(" << token_type << "," << token_value << ")" << endl;
    }

    string getTokenType()
    {
        return this->token_type;
    }
};

class LexicalAnalyzer
{
private:
    string expression;

    int failure(string token_type)
    {
        // cout << "This string is not a valid token_type " << token_type << endl;
        return -1;
    }

    int retract(string token_type, int &index)
    {
        // cout << "The string is accepted by " << token_type << endl;
        // cout << "Retracting to previous state index" << --index << endl;
        --index;
        return index;
    }

    int get_if(int start, Token &token)
    {
        string token_type = "if";
        int state = 0;
        int i = start;
        while (1)
        {
            if (i > expression.length() && state != 3)
            {
                return failure(token_type);
            }
            switch (state)
            {
            case 0:
            {

                if (expression[i] == 'i')
                {
                    i++;
                    state = 1;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 1:
            {
                if (expression[i] == 'f')
                {
                    i++;
                    state = 2;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 2:
            {
                if (!(isalnum(expression[i])))
                {
                    state = 3;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 3:
            {

                token.UpdateToken(token_type, "");
                return retract(token_type, i);
                break;
            }
            }
        }
        return failure(token_type);
    }

    int get_then(int start, Token &token)
    {
        string token_type = "then";
        int state = 0;
        int i = start;
        while (1)
        {
            if (i > expression.length() && state != 5)
            {
                return failure(token_type);
            }
            switch (state)
            {
            case 0:
            {

                if (expression[i] == 't')
                {
                    i++;
                    state = 1;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 1:
            {
                if (expression[i] == 'h')
                {
                    i++;
                    state = 2;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 2:
            {
                if (expression[i] == 'e')
                {
                    i++;
                    state = 3;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 3:
            {
                if (expression[i] == 'n')
                {
                    i++;
                    state = 4;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 4:
            {
                if (!(isalnum(expression[i])))
                {
                    // i++;
                    state = 5;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 5:
            {

                token.UpdateToken(token_type, "");
                return retract(token_type, i);
                break;
            }
            }
        }
        return failure(token_type);
    }

    int get_else(int start, Token &token)
    {
        string token_type = "else";
        int state = 0;
        int i = start;
        while (1)
        {
            if (i > expression.length() && state != 5)
            {
                return failure(token_type);
            }
            switch (state)
            {
            case 0:
            {

                if (expression[i] == 'e')
                {
                    i++;
                    state = 1;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 1:
            {
                if (expression[i] == 'l')
                {
                    i++;
                    state = 2;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 2:
            {
                if (expression[i] == 's')
                {
                    i++;
                    state = 3;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 3:
            {
                if (expression[i] == 'e')
                {
                    i++;
                    state = 4;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 4:
            {
                if (!(isalnum(expression[i])))
                {
                    // i++;
                    state = 5;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 5:
            {

                token.UpdateToken(token_type, "");
                return retract(token_type, i);
                break;
            }
            }
        }
        return failure(token_type);
    }

    int get_identifier(int start, Token &token)
    {
        string token_type = "identifier";
        int state = 0;
        int i = start;
        while (1)
        {
            if (i > expression.length() && state != 2)
            {
                return failure(token_type);
            }
            switch (state)
            {
            case 0:
            {
                if (isalpha(expression[i]))
                {
                    i++;
                    state = 1;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 1:
            {

                if (isalpha(expression[i]) || isdigit(expression[i]))
                {
                    i++;
                    state = 1;
                }
                else
                {
                    state = 2;
                }
                break;
            }
            case 2:
            {
                string sub = expression.substr(start, i - start);
                token.UpdateToken(token_type, sub);
                return retract(token_type, i);
            }
            }
        }
        return failure(token_type);
    }

    int get_relop(int start, Token &token)
    {
        string token_type = "relop";
        int i = start;
        int state = 0;
        while (1)
        {
            if (i > expression.length() && state != 2 && state != 4)
            {
                return failure(token_type);
            }
            switch (state)
            {
            case 0:
            {
                char c = expression[i];
                if (c == '<')
                {
                    state = 1;
                    i++;
                }
                else if (c == '=')
                {
                    state = 5;
                    // i++;
                }
                else if (c == '>')
                {
                    state = 6;
                    i++;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 1:
            {
                char c = expression[i];
                if (c == '=')
                {
                    state = 2;
                    // i++;
                }
                else if (c == '>')
                {
                    state = 3;
                    // i++;
                }
                else
                {
                    state = 4;
                    // i++;
                }
                break;
            }
            case 2:
            {
                token.UpdateToken(token_type, "<=");
                return i;
            }
            case 3:
            {
                token.UpdateToken(token_type, "<>");
                return i;
            }
            case 4:
            {

                token.UpdateToken(token_type, "<");
                return retract(token_type, i);
            }
            case 5:
            {
                token.UpdateToken(token_type, "=");
                return i;
            }
            case 6:
            {
                char c = expression[i];
                if (c == '=')
                {
                    state = 7;
                    // i++;
                }

                else
                {
                    state = 8;
                    // i++;
                }
                break;
            }
            case 7:
            {
                token.UpdateToken(token_type, ">=");
                return i;
            }
            case 8:
            {
                token.UpdateToken(token_type, ">");
                return retract(token_type, i);
            }
            }
        }
        return failure(token_type);
    }

    int get_number(int start, Token &token)
    {
        string token_type = "number";
        int i = start;
        int state = 0;
        while (1)
        {
            if (i > expression.length() && state != 7 && state != 8 && state != 9)
            {
                return failure(token_type);
            }
            switch (state)
            {
            case 0:
            {
                if (isdigit(expression[i]))
                {
                    state = 1;
                    i++;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 1:
            {
                if (isdigit(expression[i]))
                {
                    state = 1;
                    i++;
                }
                else if (expression[i] == '.')
                {
                    state = 2;
                    i++;
                }
                else if (expression[i] == 'E')
                {
                    state = 4;
                    i++;
                }
                else
                {
                    state = 8;
                    // i++;
                }
                break;
            }
            case 2:
            {
                if (isdigit(expression[i]))
                {
                    state = 3;
                    i++;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 3:
            {
                if (isdigit(expression[i]))
                {
                    state = 3;
                    i++;
                }
                else if (expression[i] == 'E')
                {
                    state = 4;
                    i++;
                }
                else
                {
                    state = 9;
                    // i++;
                }
                break;
            }
            case 4:
            {
                if (expression[i] == '+' || expression[i] == '-')
                {
                    i++;
                    state = 5;
                }
                else if (isdigit(expression[i]))
                {
                    i++;
                    state = 6;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 5:
            {
                if (isdigit(expression[i]))
                {
                    i++;
                    state = 6;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 6:
            {
                if (isdigit(expression[i]))
                {
                    i++;
                    state = 6;
                }
                else
                {
                    // i++;
                    state = 7;
                }
                break;
            }
            case 7:
            {
                string sub = expression.substr(start, i - start);
                token.UpdateToken(token_type, sub);
                return retract(token_type, i);
            }
            case 8:
            {
                string sub = expression.substr(start, i - start);
                token.UpdateToken(token_type, sub);
                return retract(token_type, i);
            }
            case 9:
            {
                string sub = expression.substr(start, i - start);
                token.UpdateToken(token_type, sub);
                return retract(token_type, i);
            }
            }
        }
        return failure(token_type);
    }

    int get_ws(int start, Token &token)
    {
        string token_type = "blank";
        int state = 0;
        int i = start;

        while (1)
        {
            if (i > expression.length() && state != 2)
                return failure(token_type);
            switch (state)
            {
            case 0:
            {
                char c = expression[i];
                if (c == ' ' || c == '\t' || c == '\n')
                {
                    i++;
                    state = 1;
                }
                else
                {
                    return failure(token_type);
                }
                break;
            }
            case 1:
            {
                char c = expression[i];
                if (c == ' ' || c == '\t' || c == '\n')
                {
                    i++;
                    state = 1;
                }
                else
                {
                    // i++;
                    state = 2;
                }
                break;
            }
            case 2:
            {
                token.UpdateToken(token_type, " ");
                return retract(token_type, i);
            }
            break;
            }
        }
        return failure(token_type);
    }

    Token parser(int &index)
    {

        int start = index;

        Token t = Token();
        int last_index;

        // keyword
        last_index = get_if(start, t);

        if (last_index != -1)
        {
            index = last_index + 1;
            return t;
        }

        last_index = get_then(start, t);

        if (last_index != -1)
        {
            index = last_index + 1;
            return t;
        }

        last_index = get_else(start, t);

        if (last_index != -1)
        {
            index = last_index + 1;
            return t;
        }

        // identifier
        last_index = get_identifier(start, t);

        if (last_index != -1)
        {
            index = last_index + 1;
            return t;
        }

        // number
        last_index = get_number(start, t);

        if (last_index != -1)
        {
            index = last_index + 1;
            return t;
        }

        // relop
        last_index = get_relop(start, t);

        if (last_index != -1)
        {
            index = last_index + 1;
            return t;
        }

        // blanks
        last_index = get_ws(start, t);

        if (last_index != -1)
        {
            index = last_index + 1;
            return t;
        }

        t.UpdateToken("Failure", "Failure");
        return t;
    }

public:
    LexicalAnalyzer(string expression)
    {
        this->expression = expression;
    }

    void analyze()
    {
        vector<Token> tokens;
        int i = 0, len = expression.length();

        while (i < len)
        {
            Token t = parser(i);
            if (t.getTokenType() == "Failure")
            {
                cout << endl;
                cout << "Given Expression: " << expression << endl;
                cout << "There is something wrong with the expression." << endl;
                return;
            }
            tokens.push_back(t);
        }

        // cout << "\033[2J\033[1;1H";
        cout << endl;
        cout << "Given Expression: " << expression << endl;

        for (int j = 0; j < tokens.size(); j++)
        {
            if (tokens[j].getTokenType() != "blank")
            {
                tokens[j].printToken();
            }
        }
    }
};

int main()
{

    string expression;
    cout << "Enter the Expression" << endl;
    getline(cin, expression);
    LexicalAnalyzer analyzer = LexicalAnalyzer(expression);
    analyzer.analyze();
    return 0;
}
