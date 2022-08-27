#include <bits/stdc++.h>
using namespace std;

void input_prod_rules(int &non_terms, vector<string> &non_terminals, vector<vector<string>> &productions)
{

    string produces = "->";
    char del = '|';

    cin >> non_terms;

    string non_term;
    string prod_rule;
    string rules;

    for (int i = 0; i < non_terms; i++)
    {
        cin >> prod_rule;
        int id = prod_rule.find(produces);

        vector<string> prod_rules;

        if (id != string ::npos)
        {
            non_term = prod_rule.substr(0, id);
            non_terminals.push_back(non_term);

            rules = prod_rule.substr(id + 2);
            stringstream ss(rules);
            string word;
            while (!ss.eof())
            {
                getline(ss, word, del);
                prod_rules.push_back(word);
            }
        }
        else
        {
            cout << "Error with production rules" << endl;
            return;
        }
        productions.push_back(prod_rules);
    }
}

void print_prod_rules(vector<string> &non_terminals, vector<vector<string>> &productions)
{
    for (int i = 0; i < non_terminals.size(); i++)
    {
        cout << non_terminals[i] << " -> ";
        int l = productions[i].size();
        for (int j = 0; j < l - 1; j++)
        {
            cout << productions[i][j] << " | ";
        }
        cout << productions[i][l - 1] << endl;
    }
}

bool checkIfLeftRecursive(string non_terminal, string prod_rule)
{

    if (non_terminal.length() <= prod_rule.length())
    {
        string sub = prod_rule.substr(0, non_terminal.length());
        return (non_terminal.compare(sub) == 0);
    }
    return false;
}

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("input_1.txt", "r", stdin);
    freopen("output_1.txt", "w", stdout);

    int non_terms;
    vector<string> non_terminals;
    vector<vector<string>> productions;

    input_prod_rules(non_terms, non_terminals, productions);
    vector<bool> isLeftRecursive(non_terms, false);

    cout << "Initial Production Rules" << endl;
    print_prod_rules(non_terminals, productions);

    for (int i = 0; i < non_terms; i++)
    {
        for (int j = 0; j < productions[i].size(); j++)
        {
            if (checkIfLeftRecursive(non_terminals[i], productions[i][j]))
            {
                isLeftRecursive[i] = true;
                break;
            }
        }
    }

    for (int i = 0; i < non_terms; i++)
    {
        if (isLeftRecursive[i])
        {
            non_terminals.push_back(non_terminals[i] + "'");

            vector<string> new_prod;
            for (int j = 0; j < productions[i].size(); ++j)
            {
                if (checkIfLeftRecursive(non_terminals[i], productions[i][j]))
                {
                    string rhs = productions[i][j].substr(non_terminals[i].length(), productions[i][j].length() - non_terminals[i].length()) + non_terminals[i] + "'";
                    new_prod.push_back(rhs);
                    productions[i].erase(productions[i].begin() + j);
                    --j;
                }
                else
                {
                    productions[i][j] += non_terminals[i] + "'";
                }
            }
            new_prod.push_back("#");
            productions.push_back(new_prod);
        }
    }

    cout << endl
         << endl;

    cout << "Modified Production Rules" << endl;
    print_prod_rules(non_terminals, productions);

    return 0;
}