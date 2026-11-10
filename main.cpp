/// @file
/// Main file for CS F214 Assignment 1 Part A
///
/// It includes every task file so only this file needs to be compiled
///
/// Option 1 reads a formula typed in infix
///
/// Option 2 reads a DIMACS cnf file and turns it into infix
///
/// For option 2 the full output is saved in a file called output
///
/// Option 3 runs the ratio test for time complexity

#include "common.cpp"
#include "task1.cpp"
#include "task2.cpp"
#include "task3.cpp"
#include "task4.cpp"
#include "task5.cpp"
#include "input.cpp"
#include "task6.cpp"

int main() {
    srand(time(0));
    cout << "CS F214 Assignment 1 Part A" << endl;
    cout << "1 Type a formula" << endl;
    cout << "2 Read a cnf file" << endl;
    cout << "3 Ratio test for time complexity" << endl;
    cout << "Choice: ";
    int choice;
    cin >> choice;

    if (choice == 3) {
        ratioTest();
        return 0;
    }

    string formula;
    ofstream outFile;
    streambuf* screen = cout.rdbuf();
    if (choice == 1) {
        formula = readInfix();
    }
    else {
        string path;
        cout << "File path: ";
        cin >> ws;
        getline(cin, path);
        formula = readCNF(path);

        // from here all output goes to output txt instead of the screen
        cout << "All output is saved in output.txt" << endl;
        outFile.open("output.txt");
        cout.rdbuf(outFile.rdbuf());
        toFile = true;
    }

    cout << endl << "Task 1 Infix to Prefix" << endl;
    start();
    vector<string> tokens = tokenize(formula);
    vector<string> prefix = infixToPrefix(tokens);
    stop("Task 1 infix to prefix");
    show("Infix  : ", formula);
    show("Prefix : ", join(prefix));

    cout << endl << "Task 2 Parse Tree" << endl;
    start();
    Node* root = buildTree(prefix);
    stop("Task 2 build tree");
    int nodes = prefix.size();
    cout << "Nodes : " << nodes << endl;
    cout << "Root  : " << root->val << endl;
    if (nodes <= 30) {
        cout << "Tree drawn sideways with the root on the left" << endl;
        printTree(root, 0);
    }

    cout << endl << "Task 3 Traversals" << endl;
    string a = "", b = "", c = "", d = "", e = "", f = "";
    start(); inorderRec(root, a);    stop("Task 3 in order rec");
    start(); inorderIter(root, b);   stop("Task 3 in order iter");
    start(); preorderRec(root, c);   stop("Task 3 pre order rec");
    start(); preorderIter(root, d);  stop("Task 3 pre order iter");
    start(); postorderRec(root, e);  stop("Task 3 post order rec");
    start(); postorderIter(root, f); stop("Task 3 post order iter");
    show("In order   rec  : ", a);
    show("In order   iter : ", b);
    show("Pre order  rec  : ", c);
    show("Pre order  iter : ", d);
    show("Post order rec  : ", e);
    show("Post order iter : ", f);
    cout << "Recursive and iterative give the same output : " << (a == b && c == d && e == f ? "yes" : "no") << endl;

    cout << endl << "Task 4 Height" << endl;
    start(); int h1 = heightRec(root);  stop("Task 4 height rec");
    start(); int h2 = heightIter(root); stop("Task 4 height iter");
    cout << "Height rec  : " << h1 << endl;
    cout << "Height iter : " << h2 << endl;

    cout << endl << "Task 5 Evaluation and Truth Table" << endl;
    set<string> s;
    getAtoms(root, s);
    vector<string> atoms(s.begin(), s.end());
    show("Atoms : ", join(atoms));

    map<string, bool> values;
    if (!toFile && atoms.size() <= 15) {
        cout << "Enter 1 for true and 0 for false" << endl;
        for (int i = 0; i < (int)atoms.size(); i++) {
            int v;
            cout << atoms[i] << " = ";
            cin >> v;
            values[atoms[i]] = (v == 1);
        }
    }
    else {
        cout << "Random values are used" << endl;
        for (int i = 0; i < (int)atoms.size(); i++) {
            values[atoms[i]] = (rand() % 2 == 1);
        }
    }
    start();
    bool result = evaluate(root, values);
    stop("Task 5 evaluate");
    cout << "Value : " << (result ? "T" : "F") << endl;

    if (atoms.size() <= 15) {
        cout << endl << "Truth table" << endl;
        start();
        int trueRows = truthTable(root, atoms, true);
        stop("Task 5 truth table");
        int rows = 1 << atoms.size();
        cout << "True in " << trueRows << " of " << rows << " rows so the formula is ";
        if (trueRows == rows) cout << "valid" << endl;
        else if (trueRows == 0) cout << "unsatisfiable" << endl;
        else cout << "satisfiable but not valid" << endl;
    }
    else {
        cout << "Truth table skipped because 2 power " << atoms.size() << " rows is too many" << endl;
    }

    cout << endl << "Task 6 Time and Memory" << endl;
    printTimes();
    cout << "Tokens : " << tokens.size() << endl;
    cout << "Tree memory : " << nodes << " nodes x " << sizeof(Node) << " bytes = " << nodes * sizeof(Node) << " bytes" << endl;
    cout << "Use option 3 to see the time complexity with the ratio test" << endl;

    deleteTree(root);

    // send output back to the screen before the file is closed
    cout.rdbuf(screen);
    if (toFile) cout << "Done" << endl;
    return 0;
}
