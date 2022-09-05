#include <bits/stdc++.h>
#include "../header/grammar.h"
#include "../header/sets.h"
#include "../header/top_down_parser.h"
#include "./lex/lex.h"

using namespace std;

int main()
{

    Grammar G = Grammar();
    // Step 1
    G.input_grammar("in/grammar1.txt");
    G.output_grammar("out/Grammar1.txt");

    transform_to_LL1(G);
    G.output_grammar("out/GrammarLL1.txt");

    // Step 2
    Sets S = Sets(G);
    map<string, set<string>> first_sets = S.compute_first_sets();
    map<string, set<string>> follow_sets = S.compute_follow_sets();
    S.print_sets("out/First-Follow1.txt");

    // Step 3
    Parser P = Parser(G, first_sets, follow_sets);
    vector<vector<string>> parsing_table = P.get_parsing_table();
    P.print_parsing_table("out/Parsing-Table1.txt");

    // Step 4
    char filename[] = "in/input1.txt";
    string tokenized_input;
    get_string(filename, tokenized_input);

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
