#include <bits/stdc++.h>
using namespace std;

#define ASCII_M 77

class Grammar
{
public:
    string start_symbol;
    vector<string> non_terminals;
    vector<string> terminals;
    map<string, vector<string>> rules;

    Grammar()
    {
    }

    void input_grammar(string filename)
    {
        // input format
        // non_terminals - number of non-terminals followed by each non-terminal
        // terminals - number of terminals followed by each terminal
        // rules - number of rules followed by each rule

        string myText;

        // Read from the text file
        ifstream MyReadFile(filename);

        int terms, non_terms, rule_count;
        string temp_term, temp_non_term, prod_rule, non_term, rules_rhs;
        string produces = "->";
        char del = '|';

        getline(MyReadFile, myText);
        start_symbol = myText;

        getline(MyReadFile, myText);
        non_terms = stoi(myText);
        for (int i = 0; i < non_terms; i++)
        {
            getline(MyReadFile, myText);
            temp_non_term = myText;
            non_terminals.push_back(temp_non_term);
        }
        getline(MyReadFile, myText);

        terms = stoi(myText);
        for (int i = 0; i < terms; i++)
        {
            getline(MyReadFile, myText);
            temp_term = myText;
            terminals.push_back(temp_term);
        }
        getline(MyReadFile, myText);

        rule_count = stoi(myText);
        for (int i = 0; i < rule_count; i++)
        {
            getline(MyReadFile, myText);
            prod_rule = myText;
            int id = prod_rule.find(produces);

            vector<string> prod_rules;

            if (id != string ::npos)
            {
                non_term = prod_rule.substr(0, id);
                rules_rhs = prod_rule.substr(id + 2);
                stringstream ss(rules_rhs);
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
            rules[non_term] = prod_rules;
        }
        MyReadFile.close();
    }

    void output_grammar()
    {

        cout << "Non Terminals: ";
        for (auto i = 0; i < non_terminals.size() - 1; i++)
        {
            cout << non_terminals[i] << ", ";
        }
        cout << non_terminals[non_terminals.size() - 1] << endl;
        cout << "Terminals: ";
        for (auto i = 0; i < terminals.size() - 1; i++)
        {
            cout << terminals[i] << ", ";
        }
        cout << terminals[terminals.size() - 1] << endl;
        cout << "Rules:" << endl;
        for (auto i = rules.begin(); i != rules.end(); i++)
        {
            cout << i->first << " -> ";
            int l = i->second.size();
            for (int j = 0; j < l - 1; j++)
            {
                cout << i->second[j] << " | ";
            }
            cout << i->second[l - 1] << endl;
        }
    }

    void output_grammar(string filename)
    {
        ofstream MyFile(filename);
        MyFile << "Non Terminals: ";
        for (auto i = 0; i < non_terminals.size() - 1; i++)
        {
            MyFile << non_terminals[i] << ", ";
        }
        MyFile << non_terminals[non_terminals.size() - 1] << endl;
        MyFile << "Terminals: ";
        for (auto i = 0; i < terminals.size() - 1; i++)
        {
            MyFile << terminals[i] << ", ";
        }
        MyFile << terminals[terminals.size() - 1] << endl;
        MyFile << "Rules:" << endl;
        for (auto i = rules.begin(); i != rules.end(); i++)
        {
            MyFile << i->first << " -> ";
            int l = i->second.size();
            for (int j = 0; j < l - 1; j++)
            {
                MyFile << i->second[j] << " | ";
            }
            MyFile << i->second[l - 1] << endl;
        }
    }
};

string get_new_non_terminal(Grammar grammar)
{
    static int current = 0;

    int t = ASCII_M;

    if (grammar.non_terminals.size() > 13)
    {
        t = 84;
    }

    char res = t + current++;
    string temp = "";
    temp = temp + res;
    // cout << "New symbol " << temp << endl;
    return temp;
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

bool check_if_left_recursive(string non_terminal, string prod_rule)
{

    if (non_terminal.length() <= prod_rule.length())
    {
        string sub = prod_rule.substr(0, non_terminal.length());
        return (non_terminal.compare(sub) == 0);
    }
    return false;
}

void remove_left_recursion(Grammar &grammar)
{

    map<string, bool> isLeftRec;

    for (auto it = grammar.rules.begin(); it != grammar.rules.end(); ++it)
    {
        for (int j = 0; j < it->second.size(); ++j)
        {

            if (check_if_left_recursive(it->first, it->second[j]))
            {
                isLeftRec[it->first] = true;
                break;
            }
        }
    }

    for (auto i = grammar.rules.begin(); i != grammar.rules.end(); i++)
    {
        auto it = isLeftRec.find(i->first);
        if (it != isLeftRec.end() && it->second)
        {
            string new_term = get_new_non_terminal(grammar);

            vector<string> new_prod;
            for (int j = 0; j < i->second.size(); ++j)
            {
                if (check_if_left_recursive(i->first, i->second[j]))
                {
                    string rhs = i->second[j].substr(i->first.length(), i->second[j].length() - i->first.length()) + new_term;
                    new_prod.push_back(rhs);
                    i->second.erase(i->second.begin() + j);
                    --j;
                }
                else
                {
                    i->second[j] += new_term;
                }
            }
            new_prod.push_back("#");
            grammar.non_terminals.push_back(new_term);
            grammar.rules[new_term] = new_prod;
        }
    }
}

void get_left_factored_grammar(Grammar &grammar)
{

    for (auto i = grammar.rules.begin(); i != grammar.rules.end(); i++)
    {
        if (i->second.size() > 1)
        {

            sort(i->second.begin(), i->second.end());
            int index = 0, prev = 0;
            char first_char;
            while (index < i->second.size())
            {
                first_char = i->second[prev][0];
                index++;
                while (index < i->second.size() && i->second[index][0] == first_char)
                {
                    index++;
                }

                if (index - prev > 1)
                {
                    int max_lcp = LCP(i->second[prev], i->second[prev + 1]);
                    for (int j = prev + 2; j < index; j++)
                    {
                        max_lcp = min(max_lcp, LCP(i->second[prev], i->second[j]));
                    }

                    if (max_lcp > 0)
                    {
                        string new_char = get_new_non_terminal(grammar);

                        vector<string> new_rules;
                        string new_rule_rhs = i->second[prev].substr(0, max_lcp) + new_char;
                        for (int k = prev; k < index; k++)
                        {
                            string temp = i->second[k].substr(max_lcp, i->second[k].size() - max_lcp + 1);
                            if (temp == "")
                            {
                                temp = "#";
                            }

                            new_rules.push_back(temp);
                        }
                        grammar.rules[new_char] = new_rules;
                        grammar.non_terminals.push_back(new_char);

                        vector<string>::iterator it1, it2;
                        it1 = i->second.begin() + prev;
                        it2 = i->second.begin() + index;
                        i->second.erase(it1, it2);
                        i->second.push_back(new_rule_rhs);

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
}

void transform_to_LL1(Grammar &grammar)
{
    remove_left_recursion(grammar);
    get_left_factored_grammar(grammar);
}

void transform_to_single_char_grammar(string input_filename, string output_filename, map<string, string> &terminal_map, map<string, string> &r_terminal_map, map<string, string> &non_terminal_map, map<string, string> &r_non_terminal_map)
{
    ifstream MyReadFile(input_filename);
    ofstream MyFile(output_filename);

    string produces = "->";
    char del = '|';
    char new_del = ' ';

    char non_term_ch = 'A';
    char term_ch = 'a';
    vector<char> extra_terms{'+', '-', '*', '/', '%', '&'};

    int terms, non_terms, rule_count;
    string temp_term, temp_non_term, prod_rule, non_term, rules_rhs, temp, temp_start;
    string myText;

    // start_symbol
    getline(MyReadFile, myText);
    temp_start = myText;
    temp.assign(1, non_term_ch);
    non_terminal_map.insert(make_pair(temp_start, temp));
    r_non_terminal_map.insert(make_pair(temp, temp_start));
    MyFile << non_term_ch << endl;
    non_term_ch++;

    // non_terms
    getline(MyReadFile, myText);
    non_terms = stoi(myText);
    MyFile << myText << endl;
    for (int i = 0; i < non_terms; i++)
    {
        getline(MyReadFile, myText);
        temp_non_term = myText;
        if (temp_non_term != temp_start)
        {
            temp.assign(1, non_term_ch);
            non_terminal_map.insert(make_pair(temp_non_term, temp));
            r_non_terminal_map.insert(make_pair(temp, temp_non_term));
            MyFile << non_term_ch << endl;
            non_term_ch++;
        }
        else
        {
            MyFile << non_terminal_map[temp_start] << endl;
        }
    }

    // terms
    getline(MyReadFile, myText);
    terms = stoi(myText);
    MyFile << myText << endl;
    for (int i = 0; i < terms; i++)
    {
        getline(MyReadFile, myText);
        temp_term = myText;

        if (i >= 26)
        {
            term_ch = extra_terms[i - 26];
        }

        temp.assign(1, term_ch);
        terminal_map.insert(make_pair(temp_term, temp));
        r_terminal_map.insert(make_pair(temp, temp_term));
        MyFile << term_ch << endl;
        term_ch++;
    }
    terminal_map.insert(make_pair("#", "#"));
    r_terminal_map.insert(make_pair("#", "#"));

    // rules
    getline(MyReadFile, myText);
    rule_count = stoi(myText);
    MyFile << myText << endl;
    for (int i = 0; i < rule_count; i++)
    {
        getline(MyReadFile, myText);
        prod_rule = myText;
        stringstream ss(prod_rule);
        string word;
        getline(ss, word, new_del);
        MyFile << non_terminal_map[word];
        while (!ss.eof())
        {
            getline(ss, word, new_del);
            if (word == "->" || word == "|")
            {
                MyFile << word;
            }
            else
            {
                if (non_terminal_map.find(word) != non_terminal_map.end())
                {
                    MyFile << non_terminal_map[word];
                }
                else if (terminal_map.find(word) != terminal_map.end())
                {
                    MyFile << terminal_map[word];
                }
            }
            // prod_rules.push_back(word);
        }
        MyFile << endl;
    }
    MyReadFile.close();
}