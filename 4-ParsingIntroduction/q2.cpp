#include <bits/stdc++.h>
using namespace std;

void input_prod_rules(int &non_terms, vector<string> &non_terminals, vector<vector<string>> &productions)
{
    // cout << "Enter the number of non-terminal characters" << endl;
    string produces = "->";
    char del = '|';
    cin >> non_terms;

    // cout << "Enter the non-terminal characters with their production rules" << endl;
    // cout << "Enter $ for null" << endl;

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

string get_new_char()
{
    static int current = 0;

    char res = 77 + current++;
    string ans;
    ans = ans + res + "'";
    return ans;
}

int LCP(string a, string b)
{
    int i;
    int l = min(a.length(), b.length());
    for (i = 0; i < l; i++)
    {
        if (a[i] != b[i])
            break;
    }
    return i;
}

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("input_2.txt", "r", stdin);
    freopen("output_2.txt", "w", stdout);

    int non_terms;
    vector<string> non_terminals;
    vector<vector<string>> productions;

    input_prod_rules(non_terms, non_terminals, productions);

    cout << "Initial Production Rules" << endl;
    print_prod_rules(non_terminals, productions);

    for (int i = 0; i < productions.size(); i++)
    {
        if (productions[i].size() > 1)
        {

            sort(productions[i].begin(), productions[i].end());
            int index = 0, prev = 0;
            char first_char;
            while (index < productions[i].size())
            {
                first_char = productions[i][prev][0];
                index++;
                while (index < productions[i].size() && productions[i][index][0] == first_char)
                {
                    index++;
                }

                if (index - prev > 1)
                {
                    int max_lcp = LCP(productions[i][prev], productions[i][prev + 1]);
                    for (int j = prev + 2; j < index; j++)
                    {
                        max_lcp = min(max_lcp, LCP(productions[i][prev], productions[i][j]));
                    }

                    if (max_lcp > 0)
                    {
                        string new_char = get_new_char();

                        vector<string> new_rules;
                        string new_rule_rhs = productions[i][prev].substr(0, max_lcp) + new_char;
                        for (int k = prev; k < index; k++)
                        {
                            string temp = productions[i][k].substr(max_lcp, productions[i][k].size() - max_lcp + 1);

                            new_rules.push_back(temp);
                        }
                        productions.push_back(new_rules);
                        non_terminals.push_back(new_char);

                        vector<string>::iterator it1, it2;
                        it1 = productions[i].begin() + prev;
                        it2 = productions[i].begin() + index;
                        productions[i].erase(it1, it2);
                        productions[i].push_back(new_rule_rhs);

                        index = prev;
                    }
                    else
                    {
                        prev = index;
                    }
                }
                else
                {
                    index++;
                    prev++;
                }
            }
        }
    }

    cout << endl
         << endl;

    cout << "Modified Production Rules" << endl;
    print_prod_rules(non_terminals, productions);

    return 0;
}