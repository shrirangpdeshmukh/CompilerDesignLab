#include <bits/stdc++.h>
using namespace std;

class Sets
{
private:
    map<string, set<string>> first_sets;
    map<string, set<string>> follow_sets;
    map<string, bool> follow_set_being_computed;
    bool need_to_run_again = false;
    bool is_first_run = true;
    vector<size_t> occurrences(string rule, string non_terminal)
    {
        vector<size_t> positions; // holds all the positions that sub occurs within str

        size_t pos = rule.find(non_terminal, 0);
        while (pos != string::npos)
        {
            positions.push_back(pos);
            pos = rule.find(non_terminal, pos + 1);
        }
        return positions;
    }

    bool is_non_terminal(string str)
    {
        auto it = find(grammar.non_terminals.begin(), grammar.non_terminals.end(), str);
        return it != grammar.non_terminals.end();
    }

    void compute_first_set(string symbol)
    {
        map<string, vector<string>> rules = grammar.rules;

        set<string> result;
        if (is_non_terminal(symbol))
        {
            vector<string> prod_rules = rules[symbol];
            for (int i = 0; i < prod_rules.size(); ++i)
            {
                if (prod_rules[i] != "#")
                {
                    bool non_epsilon_symbol = false;
                    set<string> temp;
                    int j = 0;
                    while (j < prod_rules[i].length())
                    {
                        string temp_str = "";
                        temp_str += prod_rules[i][j];
                        temp = get_first_set(temp_str);
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
                }
                else
                {
                    result.insert("#");
                }
            }
        }
        else
        {
            result.insert(symbol);
        }

        first_sets.insert(make_pair(symbol, result));
    }

    set<string> get_first_set(string symbol)
    {

        auto it = first_sets.find(symbol);
        if (it == first_sets.end())
        {
            compute_first_set(symbol);
            return first_sets[symbol];
        }
        else
        {
            return it->second;
        }
    }

    // set<string> get_follow_set(string symbol)
    // {

    //     auto it = follow_sets.find(symbol);
    //     if (it == follow_sets.end())
    //     {
    //         compute_follow_set(symbol);
    //         return follow_sets[symbol];
    //     }
    //     else
    //     {
    //         return it->second;
    //     }
    // }

    set<string> get_first_set_of_string(string str)
    {
        set<string> result, temp;
        string temp_str = "";
        bool non_epsilon_symbol = false;

        int j = 0;
        while (j < str.length())
        {
            string temp_str = "";
            temp_str += str[j];
            temp = get_first_set(temp_str);
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

    set<string> follow(string symbol)
    {
        map<string, vector<string>> rules = grammar.rules;
        set<string> result;
        // cout << "Called for " << symbol << endl;

        if (follow_set_being_computed.find(symbol) != follow_set_being_computed.end() && follow_set_being_computed[symbol])
        {
            need_to_run_again = true;
            return follow_sets[symbol];
        }
        else
        {
            follow_set_being_computed[symbol] = true;
            if (is_first_run)
                follow_sets.insert(make_pair(symbol, result));
        }

        string start_symbol = grammar.start_symbol;
        if (symbol == start_symbol)
        {
            follow_sets[symbol].insert("$");
        }

        for (auto it = rules.begin(); it != rules.end(); ++it)
        {
            vector<string> prod_rules = it->second;

            for (int i = 0; i < prod_rules.size(); ++i)
            {
                string rule = prod_rules[i];

                vector<size_t> occurred_positions = occurrences(rule, symbol);
                for (auto j = 0; j < occurred_positions.size(); ++j)
                {
                    size_t index = occurred_positions[j];

                    // A -> pBq
                    if (index < (rule.length() - 1))
                    {

                        int temp_id = index + 1;
                        string temp_str = rule.substr(index + 1, rule.length() - index);
                        set<string> temp_first = get_first_set_of_string(temp_str);
                        follow_sets[symbol].insert(temp_first.begin(), temp_first.end());
                        if (temp_first.find("#") != temp_first.end())
                        {
                            result.erase("#");
                            if (it->first != symbol)
                            {
                                set<string> temp_follow = follow(it->first);

                                follow_sets[symbol].insert(temp_follow.begin(), temp_follow.end());
                            }
                        }
                    }

                    else if (index == (rule.length() - 1))
                    {
                        if (it->first != symbol)
                        {
                            set<string> temp_follow = follow(it->first);
                            follow_sets[symbol].insert(temp_follow.begin(), temp_follow.end());
                        }
                    }
                }
            }
        }

        // follow_sets.insert(make_pair(symbol, result));
        // cout << "Done for " << demo++ << endl;
        return follow_sets[symbol];
    }

    // void compute_follow_set(string symbol)
    // {
    //     map<string, vector<string>> rules = grammar.rules;
    //     set<string> result;
    //     if (follow_set_being_computed.find(symbol) != follow_set_being_computed.end() && follow_set_being_computed[symbol])
    //     {
    //         need_to_run_again = true;
    //         return;
    //     }
    //     else
    //     {
    //         follow_set_being_computed[symbol] = true;
    //     }
    //     // cout << "Called for " << symbol << endl;

    //     string start_symbol = grammar.start_symbol;
    //     if (symbol == start_symbol)
    //     {
    //         result.insert("$");
    //     }

    //     for (auto it = rules.begin(); it != rules.end(); ++it)
    //     {
    //         vector<string> prod_rules = it->second;

    //         for (int i = 0; i < prod_rules.size(); ++i)
    //         {
    //             string rule = prod_rules[i];

    //             vector<size_t> occurred_positions = occurrences(rule, symbol);
    //             for (auto j = 0; j < occurred_positions.size(); ++j)
    //             {
    //                 size_t index = occurred_positions[j];

    //                 // A -> pBq
    //                 if (index < (rule.length() - 1))
    //                 {

    //                     int temp_id = index + 1;
    //                     string temp_str = rule.substr(index + 1, rule.length() - index);
    //                     set<string> temp_first = get_first_set_of_string(temp_str);
    //                     result.insert(temp_first.begin(), temp_first.end());
    //                     if (temp_first.find("#") != temp_first.end())
    //                     {
    //                         result.erase("#");
    //                         if (it->first != symbol)
    //                         {
    //                             set<string> temp_follow = get_follow_set(it->first);

    //                             result.insert(temp_follow.begin(), temp_follow.end());
    //                         }
    //                     }
    //                 }

    //                 else if (index == (rule.length() - 1))
    //                 {
    //                     if (it->first != symbol)
    //                     {
    //                         set<string> temp_follow = get_follow_set(it->first);
    //                         result.insert(temp_follow.begin(), temp_follow.end());
    //                     }
    //                 }
    //             }
    //         }
    //     }

    //     follow_sets.insert(make_pair(symbol, result));
    //     // cout << "Done for " << demo++ << endl;
    // }

public:
    Grammar grammar;

    Sets(Grammar grammar)
    {
        this->grammar = grammar;
    }

    map<string, set<string>> compute_first_sets()
    {

        set<string> temp;
        string str;
        for (auto it = 0; it < grammar.terminals.size(); it++)
        {

            str = grammar.terminals[it];
            temp = get_first_set(str);
        }
        get_first_set("#");

        for (auto it = 0; it < grammar.non_terminals.size(); it++)
        {

            str = grammar.non_terminals[it];
            temp = get_first_set(str);
        }

        return first_sets;
    }

    map<string, set<string>> compute_follow_sets()
    {
        set<string> temp;
        string str;
        for (auto it = 0; it < grammar.non_terminals.size(); it++)
        {

            str = grammar.non_terminals[it];
            temp = follow(str);
        }
        if (need_to_run_again)
        {
            is_first_run = false;
            follow_set_being_computed.clear();
            for (auto it = 0; it < grammar.non_terminals.size(); it++)
            {

                str = grammar.non_terminals[it];
                temp = follow(str);
            }
        }

        return follow_sets;
    }

    void print_sets(map<string, set<string>> sets)
    {
        for (auto it = sets.begin(); it != sets.end(); ++it)
        {
            cout << it->first << " : ";
            cout << "{ ";
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                cout << (*it2) << ",";
            }
            cout << " }" << endl;
        }
    }

    void print_sets(string filename)
    {
        ofstream MyFile(filename);
        MyFile << "First Sets " << endl;
        for (auto it = first_sets.begin(); it != first_sets.end(); ++it)
        {
            MyFile << it->first << " : ";
            MyFile << "{ ";
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                MyFile << (*it2) << ",";
            }
            MyFile << " }" << endl;
        }

        MyFile << "Follow Sets " << endl;
        for (auto it = follow_sets.begin(); it != follow_sets.end(); ++it)
        {
            MyFile << it->first << " : ";
            MyFile << "{ ";
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                MyFile << (*it2) << ",";
            }
            MyFile << " }" << endl;
        }
    }
};