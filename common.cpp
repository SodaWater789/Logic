/// @file
/// Libraries and the tree node used by every task

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

/// One node of the parse tree
///
/// An atom has no children
///
/// A not node keeps its only child in right
///
/// An and or implies node uses both children
struct Node {
    string val;
    Node* left;
    Node* right;
};

/// Makes a new node with no children
Node* newNode(string val) {
    Node* n = new Node;
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/// True if the token is one of the four connectives
bool isOp(string t) {
    return t == "~" || t == "+" || t == "*" || t == ">";
}

/// Joins tokens into one string with a space after each token
string join(vector<string>& v) {
    string s = "";
    for (int i = 0; i < (int)v.size(); i++) {
        s += v[i] + " ";
    }
    return s;
}

/// True when the output goes to a file
bool toFile = false;

/// Prints a label and a text
///
/// On the screen a very long text is cut but in a file the full text is written
void show(string label, string text) {
    if (!toFile && text.length() > 300) {
        text = text.substr(0, 300) + " and more";
    }
    cout << label << text << endl;
}
