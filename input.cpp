/// @file
/// The two input methods
///
/// readInfix reads a formula typed in infix
///
/// readCNF reads a DIMACS cnf file and turns it into an infix formula

/// Reads one formula typed by the user
string readInfix() {
    string formula;
    cout << "Formula: ";
    cin >> ws;
    getline(cin, formula);
    return formula;
}

/// Joins items from lo to hi with the connective op as a balanced tree
///
/// This keeps the tree height small even for very big files
void joinBalanced(vector<string>& items, int lo, int hi, string op, string& out) {
    if (lo == hi) {
        out += items[lo];
        return;
    }
    int mid = (lo + hi) / 2;
    out += "(";
    joinBalanced(items, lo, mid, op, out);
    out += op;
    joinBalanced(items, mid + 1, hi, op, out);
    out += ")";
}

/// Reads a DIMACS cnf file and returns it as one infix formula
///
/// A line starting with c is a comment
///
/// The line p cnf V C gives the number of variables and clauses
///
/// Each clause is a list of numbers ending with 0
///
/// The number k means atom xk and minus k means not xk
///
/// Literals in a clause are joined with or and clauses are joined with and
string readCNF(string path) {
    ifstream file(path.c_str());
    vector<string> clauses;
    vector<string> literals;
    string word;
    int vars = 0;
    int count = 0;

    while (file >> word) {
        if (word == "c") {
            getline(file, word);
        }
        else if (word == "p") {
            file >> word >> vars >> count;
        }
        else if (word == "%") {
            // some benchmark files end with this mark
            break;
        }
        else {
            int x = atoi(word.c_str());
            if (x == 0) {
                string clause = "";
                joinBalanced(literals, 0, literals.size() - 1, "+", clause);
                clauses.push_back(clause);
                literals.clear();
            }
            else if (x > 0) {
                literals.push_back("x" + to_string(x));
            }
            else {
                literals.push_back("(~x" + to_string(-x) + ")");
            }
        }
    }

    cout << "Read " << vars << " variables and " << clauses.size() << " clauses" << endl;
    string formula = "";
    joinBalanced(clauses, 0, clauses.size() - 1, "*", formula);
    return formula;
}
