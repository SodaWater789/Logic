/// @file
/// Task 5 evaluates the formula and makes the truth table

/// Finds the truth value of the tree bottom up
///
/// Both children are evaluated first and then the connective is applied
bool evaluate(Node* root, map<string, bool>& values) {
    if (root->val == "~") {
        return !evaluate(root->right, values);
    }
    if (root->val == "*" || root->val == "+" || root->val == ">") {
        bool a = evaluate(root->left, values);
        bool b = evaluate(root->right, values);
        if (root->val == "*") return a && b;
        if (root->val == "+") return a || b;
        return !a || b;
    }
    return values[root->val];
}

/// Puts the name of every atom in the tree into the set
void getAtoms(Node* root, set<string>& atoms) {
    if (root == NULL) return;
    if (!isOp(root->val)) atoms.insert(root->val);
    getAtoms(root->left, atoms);
    getAtoms(root->right, atoms);
}

/// Goes through all 2 power k rows and returns how many rows are true
///
/// Row number r is read in binary where bit 0 means T and bit 1 means F
///
/// So the first row is all T and the last row is all F
///
/// Rows are printed only when print is true
int truthTable(Node* root, vector<string>& atoms, bool print) {
    int k = atoms.size();
    int rows = 1 << k;
    int trueRows = 0;
    map<string, bool> values;

    if (print) {
        for (int j = 0; j < k; j++) cout << atoms[j] << " ";
        cout << "| Result" << endl;
    }

    for (int r = 0; r < rows; r++) {
        for (int j = 0; j < k; j++) {
            int bit = (r >> (k - 1 - j)) & 1;
            values[atoms[j]] = (bit == 0);
        }
        bool result = evaluate(root, values);
        if (result) trueRows++;

        if (print) {
            for (int j = 0; j < k; j++) {
                cout << (values[atoms[j]] ? "T" : "F") << string(atoms[j].length(), ' ');
            }
            cout << "| " << (result ? "T" : "F") << endl;
        }
    }
    return trueRows;
}
