#include <bits/stdc++.h>
using namespace std;

// Declaration of operators and symbols
#define UNION_OPERATOR '+'
#define KLEENE_CLOSURE_OPERATOR '*'
#define CONCATENATION_OPERATOR '.'
#define EPSILON_SYMBOL '$'
#define PHI_SYMBOL '%'
#define LEFT_PARENTHESIS '('
#define RIGHT_PARENTHESIS ')'

// ID to uniquely identify each node created in the process
int currentNodeCount = 0;

// Class representing node in the FSM
class Node {
   public:
    int data;
    vector<pair<Node *, char>> adjList;
    Node() {
        this->data = currentNodeCount++;
        vector<pair<Node *, char>> vec;
        this->adjList = vec;
    }
    void addTransition(Node *dst, char character) {
        if (dst == NULL) return;
        adjList.push_back(make_pair(dst, character));
    }

    void printEdges() {
        if (adjList.size() > 0) {
            for (auto const &adj : adjList) {
                printf("%c -> %d |\t ", adj.second, adj.first->data);
            }
        }
    }
};

// FSM to perform the operations
class FSM {
   public:
    Node *start;
    Node *end;
    vector<Node *> nodes;

    FSM() {
        this->start = NULL;
        this->end = NULL;
        this->nodes = vector<Node *>();
    }

    FSM(char character) {
        this->start = new Node();
        this->nodes = vector<Node *>{start};

        if (isalpha(character)) {
            this->end = new Node();
            nodes.push_back(end);
            start->addTransition(end, character);
        } else if (character == EPSILON_SYMBOL) {
            this->end = start;
        } else {
            this->end = NULL;
            nodes.push_back(end);
        }
    }

    void displayFSM() {
        printf("\n\tTransition Table \n");
        printf("_____________________________________\n");
        printf("Current State -\tInput -> Next State");
        printf("\n_____________________________________\n");

        printf("S %d |\t", start->data);
        start->printEdges();
        printf("\n");

        for (auto const &node : nodes) {
            if (node != start && node != end) {
                printf("I %d |\t", node->data);
                node->printEdges();
                printf("\n");
            }
        }
        if (end == NULL) {
            printf("No end node |\t\n");
        } else {
            printf("E %d |\t\n", end->data);
        }
    };

    void union_operation(FSM next) {
        // PHI machine is uniquely identified by its end being NULL
        // EPSILON machine is identified by its start = end

        // addition with phi		=> a + % = a
        if (end == NULL) {
            // current FSM is PHI
            // phi + next FSM is nextFSM
            start = next.start;
            end = next.end;

            // there must only one element i.e. the start, remove it and insert
            // all elements from next FSM
            nodes.pop_back();
            nodes.insert(nodes.end(), next.nodes.begin(), next.nodes.end());
        } else if (next.end == NULL) {
            // nextFSM is PHI
            // no need to change anything keep it as it is
        } else {
            Node *newStart = new Node();
            Node *newEnd = new Node();

            nodes.insert(nodes.end(), next.nodes.begin(), next.nodes.end());

            newStart->addTransition(start, '$');
            newStart->addTransition(next.start, '$');

            end->addTransition(newEnd, '$');
            next.end->addTransition(newEnd, '$');

            nodes.push_back(newStart);
            nodes.push_back(newEnd);

            start = newStart;
            end = newEnd;
        }
    };

    void concat_operation(FSM next) {
        // multiplication with phi		=> a.% = %
        // multiplication with epsilon	=> a.$ = a
        if (start == NULL && end == NULL) {
            start = next.start;
            nodes.insert(nodes.end(), next.nodes.begin(), next.nodes.end());
            end = next.end;
        } else if (start != NULL && end == NULL) {
            // phi.something = phi
            // no no need to anything
        } else if (next.start != NULL && next.end == NULL) {
            // something non_phi.phi = phi
            // make it phi

            start = next.start;
            nodes = next.nodes;
            end = next.end;
        } else if (next.start != NULL && next.end == next.start) {
            // something.epsilon = something
            // no need to anything
        } else if (start != NULL && start == end) {
            // epsilon*something = something
            start = next.start;
            nodes = next.nodes;
            end = next.end;
        } else {
            end->addTransition(next.start, '$');
            nodes.insert(nodes.end(), next.nodes.begin(), next.nodes.end());
            end = next.end;
        }
    };

    void kleene_closure_operation() {
        Node *newStart = new Node();
        Node *newEnd = new Node();

        newStart->addTransition(start, '$');
        newStart->addTransition(newEnd, '$');

        end->addTransition(start, '$');
        end->addTransition(newEnd, '$');

        nodes.push_back(newStart);
        nodes.push_back(newEnd);

        start = newStart;
        end = newEnd;
    };
};

// class for validating regex
class RegexValidator {
   private:
    string expr;

    bool areParenthesesBalanced() {
        stack<char> st;
        int l = expr.length();

        for (auto ch : expr) {
            if (ch == LEFT_PARENTHESIS) {
                st.push(ch);
            } else if (ch == RIGHT_PARENTHESIS) {
                if (!st.empty() && st.top() == LEFT_PARENTHESIS) {
                    st.pop();
                } else {
                    return false;
                }
            }
        }
        return st.empty();
    }

    bool validCharacterCheck(char ch) {
        return isalpha(ch) || ch == LEFT_PARENTHESIS ||
               ch == RIGHT_PARENTHESIS || ch == UNION_OPERATOR ||
               ch == CONCATENATION_OPERATOR || ch == KLEENE_CLOSURE_OPERATOR ||
               ch == EPSILON_SYMBOL || ch == PHI_SYMBOL;
    }

    bool operatorsCheck() {
        // + must be followed by (, alpha, % or $
        // . must be followed by (, alpha, % or $
        // ( must be followed by (, alpha, % or $

        /* 
			* must be followed by ., +,) 
			) must be followed by ., +,), or *
			alpha must be followed by ., +,), or *,
			$ must be followed by ., +,), or *,
			% must be followed by ., +,), or *,
		*/

        int l = expr.length();
        int i = 0;
        while (i < l) {
            char ch = expr[i];

            if (i == 0) {
                if (!(isalpha(ch) || ch == LEFT_PARENTHESIS ||
                      ch == EPSILON_SYMBOL || ch == PHI_SYMBOL)) {
                    return false;
                }
            }

            if (ch == UNION_OPERATOR || ch == CONCATENATION_OPERATOR ||
                ch == LEFT_PARENTHESIS) {
                if (i + 1 > l) return false;
                char nextChar = expr[i + 1];
                if (!(nextChar == LEFT_PARENTHESIS || nextChar == PHI_SYMBOL ||
                      nextChar == EPSILON_SYMBOL || isalpha(nextChar)))
                    return false;
            } else if (ch == KLEENE_CLOSURE_OPERATOR) {
                if (i + 1 < l) {
                    char nextChar = expr[i + 1];
                    if (!(nextChar == UNION_OPERATOR ||
                          nextChar == CONCATENATION_OPERATOR ||
                          nextChar == RIGHT_PARENTHESIS))
                        return false;
                }
            } else {
                if (i + 1 < l) {
                    char nextChar = expr[i + 1];
                    if (!(nextChar == UNION_OPERATOR ||
                          nextChar == CONCATENATION_OPERATOR ||
                          nextChar == RIGHT_PARENTHESIS ||
                          nextChar == KLEENE_CLOSURE_OPERATOR))
                        return false;
                }
            }
            i++;
        }

        return true;
    }

   public:
    RegexValidator(string expression) { this->expr = expression; }

    bool isRegexValid() {
        for (auto ch : expr) {
            if (!validCharacterCheck(ch)) {
                cout << "Invalid character " << ch << "in " << expr << endl;
                return false;
            }
        }

        if (!areParenthesesBalanced()) {
            cout << "Unbalanced parentheses in " << expr << endl;
            return false;
        }

        if (!operatorsCheck()) {
            cout << "Invalid operators in " << expr << endl;
            return false;
        }

        return true;
    }

    string preProcessRegex() {
        string result = "";
        int l = expr.length();
        int i = 0;
        while (i < l) {
            // eliminate %*and $*and replace them with % and % resp;
            result.push_back(expr[i]);
            if ((expr[i] == EPSILON_SYMBOL || expr[i] == PHI_SYMBOL) &&
                i + 1 < l && expr[i + 1] == KLEENE_CLOSURE_OPERATOR) {
                i++;
            }
            i++;
        }

        return result;
    }
};

FSM analyzeRegex(string expr) {
    cout << "Entering analyzeRegex with " << expr << endl;
    FSM final = FSM();
    int l = expr.length();
    int i = 0;
    while (i < l) {
        char current = expr[i];
        cout << current << " " << endl;
        if (current == LEFT_PARENTHESIS) {
            int k = i;
            int j = 0;
            while (expr[i++] != RIGHT_PARENTHESIS) j++;

            string sub = expr.substr(k + 1, j - 1);
            FSM internal = analyzeRegex(sub);
            if (i < l && expr[i] == '*') {
                internal.kleene_closure_operation();
                i++;
            }
            final.concat_operation(internal);
        } else if (current == KLEENE_CLOSURE_OPERATOR) {
            final.kleene_closure_operation();
            i++;
        } else if (current == CONCATENATION_OPERATOR) {
            char nextChar = expr[i + 1];
            if (nextChar == LEFT_PARENTHESIS) {
                int k = i;
                int j = 0;
                while (expr[i++] != RIGHT_PARENTHESIS) j++;

                string sub = expr.substr(k + 1, j - 1);
                FSM internal = analyzeRegex(sub);
                if (i < l && expr[i] == '*') {
                    internal.kleene_closure_operation();
                    i++;
                }
                final.concat_operation(internal);
            } else {
                FSM temp = FSM(nextChar);
                i++;
                if (i + 1 < l && expr[i + 1] == '*') {
                    temp.kleene_closure_operation();
                    i++;
                }
                final.concat_operation(temp);
            }
            i++;
        } else if (current == UNION_OPERATOR) {
            string sub = expr.substr(i + 1, l - i + 1);
            FSM internal = analyzeRegex(sub);
            final.union_operation(internal);
            i = l;
        } else if (isalpha(current) || current == EPSILON_SYMBOL ||
                   current == PHI_SYMBOL) {
            FSM temp = FSM(current);
            if (i + 1 < l && expr[i + 1] == '*') {
                temp.kleene_closure_operation();
                i++;
            }

            if (final.start == NULL) {
                final = temp;
            } else {
                final.concat_operation(temp);
            }
            i++;
        }
    }
    return final;
}

int main(int argc, char **argv) {
    cout << "Program to convert Regex to NFA" << endl;
    string expression;
    cin >> expression;
    RegexValidator regexValidator = RegexValidator(expression);

    bool isValid = regexValidator.isRegexValid();
    cout << (isValid ? "Valid Regex" : "Invalid Regex") << endl;
    if (!isValid) {
        return -1;
    }

    string expr = regexValidator.preProcessRegex();
    FSM finalFSM = analyzeRegex(expr);
    system("cls");
    cout << "Expression: " << expression << endl;
    cout << "Processed Expression: " << expr << endl;
    finalFSM.displayFSM();

    return 0;
}