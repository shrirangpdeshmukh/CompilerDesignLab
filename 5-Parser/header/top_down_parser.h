#include <bits/stdc++.h>
using namespace std;

class Parser
{
private:
    Grammar grammar;
    map<string, set<string>> first_sets;
    map<string, set<string>> follow_sets;
    vector<vector<string>> parsing_table;
    map<string, int> row_index_map;
    map<string, int> col_index_map;

    set<string> get_first_set_of_rule(string str)
    {
        set<string> result, temp;
        string temp_str = "";
        bool non_epsilon_symbol = false;

        int j = 0;
        while (j < str.length())
        {
            string temp_str = "";
            temp_str += str[j];
            temp = first_sets[temp_str];
            if (temp.find("#") != temp.end())
            {
                for (auto it = temp.begin(); it != temp.end(); ++it)
                {
                    if ((*it) != "#")
                    {
                        result.insert((*it));
                    }
                }
            }
            else
            {
                result.insert(temp.begin(), temp.end());
                non_epsilon_symbol = true;
                break;
            }
            j++;
        }
        if (!non_epsilon_symbol)
        {
            result.insert("#");
        }

        return result;
    }

    void build_index_maps()
    {
        for (int i = 0; i < grammar.non_terminals.size(); i++)
        {
            row_index_map.insert(make_pair(grammar.non_terminals[i], i));
        }
        for (int i = 0; i < grammar.terminals.size(); i++)
        {
            col_index_map.insert(make_pair(grammar.terminals[i], i));
        }
        col_index_map.insert(make_pair("$", grammar.terminals.size()));
    }

    void build_parsing_table()
    {
        // create parsing_table
        vector<vector<string>> table(grammar.non_terminals.size(), vector<string>(grammar.terminals.size() + 1, ""));

        for (auto it = grammar.rules.begin(); it != grammar.rules.end(); ++it)
        {

            string non_term = it->first;

            for (auto it2 = 0; it2 < it->second.size(); ++it2)
            {
                string rule = it->second[it2];

                string first_symbol_in_rule = "";
                first_symbol_in_rule += rule[0];

                set<string> first_temp = get_first_set_of_rule(rule);
                set<string> follow_temp = follow_sets[non_term];
                string temp_str = rule;

                for (auto it3 = first_temp.begin(); it3 != first_temp.end(); ++it3)
                {

                    if ((*it3) != "#")
                    {
                        table[row_index_map[non_term]][col_index_map[*it3]] = temp_str;
                    }
                    else
                    {
                        for (auto it4 = follow_temp.begin(); it4 != follow_temp.end(); ++it4)
                        {
                            table[row_index_map[non_term]][col_index_map[*it4]] = temp_str;
                        }
                    }
                }
            }
        }

        parsing_table = table;
    }

public:
    Parser(Grammar &grammar, map<string, set<string>> first_sets, map<string, set<string>> follow_sets)
    {
        this->grammar = grammar;
        this->first_sets = first_sets;
        this->follow_sets = follow_sets;
        build_index_maps();
    }

    vector<vector<string>> get_parsing_table()
    {
        build_parsing_table();
        return parsing_table;
    }

    void print_parsing_table()
    {
        cout << endl;
        cout << "\t|";
        for (int i = 0; i < grammar.terminals.size(); ++i)
        {
            cout << grammar.terminals[i] << "\t|";
        }
        cout << "$" << endl;
        for (int i = 0; i < parsing_table.size(); ++i)
        {
            cout << grammar.non_terminals[i] << "\t|";
            for (int j = 0; j < parsing_table[i].size(); ++j)
            {

                cout << parsing_table[i][j] << "\t|";
            }

            cout << endl;
        }
    }

    void print_parsing_table(string filename)
    {
        ofstream MyFile(filename);
        MyFile << endl;
        MyFile << "\t|";
        for (int i = 0; i < grammar.terminals.size(); ++i)
        {
            MyFile << grammar.terminals[i] << "\t|";
        }
        MyFile << "$" << endl;
        for (int i = 0; i < parsing_table.size(); ++i)
        {
            MyFile << grammar.non_terminals[i] << "\t|";
            for (int j = 0; j < parsing_table[i].size(); ++j)
            {

                MyFile << parsing_table[i][j] << "\t|";
            }

            MyFile << endl;
        }
    }

    void parse_input(string tokenized_input)
    {
        stack<string> st;

        st.push("$");
        string start_symbol = grammar.start_symbol;
        st.push(start_symbol);

        bool flag = true;

        while (!(st.top() == "$" && tokenized_input == "$"))
        {

            string st_top = st.top();
            string lookahead = "";
            lookahead += tokenized_input[0];

            if (st_top == lookahead)
            {
                st.pop();
                tokenized_input.erase(tokenized_input.begin());
            }
            else
            {
                int r_ind = row_index_map[st_top];
                int c_ind = col_index_map[lookahead];

                string rule_to_be_applied = parsing_table[r_ind][c_ind];

                if (rule_to_be_applied == "")
                {
                    cout << "ERROR: Invalid rule search [" << st_top << "," << lookahead << "]" << endl;
                    cout << "Current state of unconsumed input is " << tokenized_input << endl;
                    cout << "Rejected !" << endl;
                    flag = false;
                    break;
                }

                st.pop();
                if (rule_to_be_applied != "#")
                {

                    for (int j = rule_to_be_applied.size() - 1; j >= 0; j--)
                    {
                        string temp = "";
                        temp += rule_to_be_applied[j];
                        st.push(temp);
                    }
                }
            }
        }

        if (flag)
        {
            printf("Accepted!");
        }
    }
};