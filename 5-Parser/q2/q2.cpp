#include <bits/stdc++.h>
#include "../header/grammar.h"
#include "../header/sets.h"
#include "../header/top_down_parser.h"
#include "./lex/lex.h"

using namespace std;

void print_maps(string filename, map<string, string> m)
{
    ofstream MyFile(filename);
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        MyFile << it->first << "\t:\t" << it->second << endl;
    }
    MyFile << endl;
}

int main()
{

    map<string, string> terminal_map;
    map<string, string> r_terminal_map;
    map<string, string> non_terminal_map;
    map<string, string> r_non_terminal_map;
    string input_filename = "in/grammar2.txt";
    string output_filename = "out/t_grammar2.txt";

    transform_to_single_char_grammar(input_filename, output_filename, terminal_map, r_terminal_map, non_terminal_map, r_non_terminal_map);

    print_maps("out/term_map.txt", terminal_map);
    print_maps("out/non_term_map.txt", non_terminal_map);

    Grammar G = Grammar();
    // Step 1
    G.input_grammar("out/t_grammar2.txt");
    G.output_grammar("out/Grammar2.txt");

    transform_to_LL1(G);
    G.output_grammar("out/GrammarLL2.txt");

    // Step 2
    Sets S = Sets(G);
    map<string, set<string>> first_sets = S.compute_first_sets();
    map<string, set<string>> follow_sets = S.compute_follow_sets();
    S.print_sets("out/First-Follow2.txt");

    // Step 3
    Parser P = Parser(G, first_sets, follow_sets);
    vector<vector<string>> parsing_table = P.get_parsing_table();
    P.print_parsing_table("out/Parsing-Table2.txt");

    // Step 4
    char filename[] = "in/input1.txt";

    string tokenized_input = "";
    get_string(filename, tokenized_input, terminal_map);
    cout << tokenized_input << endl;

    if (tokenized_input == "ERROR$")
    {
        cout << "Rejected" << endl;
    }
    else
    {
        P.parse_input(tokenized_input);
    }

    return 0;
}
