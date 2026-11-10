/// @file
/// Task 6 measures the time of every task
///
/// The ratio test finds the time complexity
///
/// It runs every task on a formula of size n and then on size 10n
///
/// If the time also grows about 10 times the task is order n
///
/// For the truth table one atom is added each time
///
/// If the time grows about 2 times the truth table is order 2 power k

vector<string> names;
vector<double> times;
double startTime = 0;

/// Current time in milliseconds
double now() {
    return clock() * 1000.0 / CLOCKS_PER_SEC;
}

/// Call before a task
void start() {
    startTime = now();
}

/// Call after a task to save its name and time
void stop(string name) {
    names.push_back(name);
    times.push_back(now() - startTime);
}

/// Prints the saved time of every task
void printTimes() {
    for (int i = 0; i < (int)names.size(); i++) {
        cout << left << setw(32) << names[i] << right << setw(10) << fixed << setprecision(1) << times[i] << " ms" << endl;
    }
}

/// Makes a test formula with c clauses and about 5c nodes
///
/// Only 100 atoms are used so the number of atoms does not change with c
string makeFormula(int c) {
    vector<string> parts;
    for (int i = 0; i < c; i++) {
        string a = "x" + to_string(i % 100 + 1);
        string b = "x" + to_string((i + 1) % 100 + 1);
        parts.push_back("(" + a + "+(~" + b + "))");
    }
    string f = "";
    joinBalanced(parts, 0, c - 1, "*", f);
    return f;
}

/// Runs every task on the formula without printing and saves the times
///
/// Returns the number of nodes
int timeAll(string formula) {
    names.clear();
    times.clear();

    start();
    vector<string> tokens = tokenize(formula);
    vector<string> prefix = infixToPrefix(tokens);
    stop("Task 1 infix to prefix");

    start();
    Node* root = buildTree(prefix);
    stop("Task 2 build tree");

    string a = "", b = "", c = "", d = "", e = "", f = "";
    start(); inorderRec(root, a);   stop("Task 3 in order rec");
    start(); inorderIter(root, b);  stop("Task 3 in order iter");
    start(); preorderRec(root, c);  stop("Task 3 pre order rec");
    start(); preorderIter(root, d); stop("Task 3 pre order iter");
    start(); postorderRec(root, e); stop("Task 3 post order rec");
    start(); postorderIter(root, f); stop("Task 3 post order iter");

    start(); heightRec(root);  stop("Task 4 height rec");
    start(); heightIter(root); stop("Task 4 height iter");

    set<string> s;
    getAtoms(root, s);
    map<string, bool> values;
    for (string x : s) values[x] = true;
    start(); evaluate(root, values); stop("Task 5 evaluate");

    deleteTree(root);
    return prefix.size();
}

/// Runs the ratio test and prints the results
void ratioTest() {
    int c = 50000;

    int n1 = timeAll(makeFormula(c));
    vector<double> t1 = times;
    int n2 = timeAll(makeFormula(10 * c));
    vector<double> t2 = times;

    cout << endl << "Ratio test for n = " << n1 << " nodes and 10n = " << n2 << " nodes" << endl;
    cout << left << setw(32) << "Task" << right << setw(10) << "n" << setw(10) << "10n" << setw(10) << "ratio" << endl;
    for (int i = 0; i < (int)names.size(); i++) {
        cout << left << setw(32) << names[i] << right << fixed << setprecision(1)
             << setw(10) << t1[i] << setw(10) << t2[i] << setw(10) << t2[i] / t1[i] << endl;
    }
    cout << "Times are in ms and a ratio near 10 means the task is O(n)" << endl;

    cout << endl << "Truth table test where one atom is added each time" << endl;
    cout << setw(6) << "k" << setw(12) << "rows" << setw(12) << "time" << setw(10) << "ratio" << endl;
    double last = 0;
    for (int k = 12; k <= 18; k++) {
        vector<string> atoms;
        for (int i = 1; i <= k; i++) atoms.push_back("x" + to_string(i));
        string formula = "";
        joinBalanced(atoms, 0, k - 1, "+", formula);
        vector<string> prefix = infixToPrefix(tokenize(formula));
        Node* root = buildTree(prefix);

        double s = now();
        truthTable(root, atoms, false);
        double t = now() - s;

        cout << setw(6) << k << setw(12) << (1 << k) << setw(12) << t;
        if (last > 0) cout << setw(10) << t / last;
        cout << endl;
        last = t;
        deleteTree(root);
    }
    cout << "Times are in ms and a ratio near 2 means the truth table is O(2 power k times n)" << endl;
}
