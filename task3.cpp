/// @file
/// Task 3 does in order and pre order and post order traversals
///
/// Each traversal is written once with recursion and once with a stack
///
/// Each function adds its output to the string out

/// True if the node has no children
bool isLeaf(Node* n) {
    return n->left == NULL && n->right == NULL;
}

/// In order with brackets which gives back the infix formula
void inorderRec(Node* root, string& out) {
    if (root == NULL) return;
    if (isLeaf(root)) {
        out += root->val;
        return;
    }
    out += "(";
    inorderRec(root->left, out);
    out += root->val;
    inorderRec(root->right, out);
    out += ")";
}

/// In order with a stack
///
/// Every connective is visited three times so a second stack keeps the step
///
/// Step 0 prints the open bracket and goes left
///
/// Step 1 prints the connective and goes right
///
/// Step 2 prints the close bracket
void inorderIter(Node* root, string& out) {
    stack<Node*> nodes;
    stack<int> steps;
    nodes.push(root);
    steps.push(0);

    while (!nodes.empty()) {
        Node* cur = nodes.top();
        int step = steps.top();
        nodes.pop();
        steps.pop();

        if (isLeaf(cur)) {
            out += cur->val;
        }
        else if (step == 0) {
            out += "(";
            nodes.push(cur);
            steps.push(1);
            if (cur->left != NULL) {
                nodes.push(cur->left);
                steps.push(0);
            }
        }
        else if (step == 1) {
            out += cur->val;
            nodes.push(cur);
            steps.push(2);
            nodes.push(cur->right);
            steps.push(0);
        }
        else {
            out += ")";
        }
    }
}

/// Pre order visits node then left then right
void preorderRec(Node* root, string& out) {
    if (root == NULL) return;
    out += root->val + " ";
    preorderRec(root->left, out);
    preorderRec(root->right, out);
}

/// Pre order with a stack
///
/// Right is pushed first so that left comes out first
void preorderIter(Node* root, string& out) {
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* cur = st.top();
        st.pop();
        out += cur->val + " ";
        if (cur->right != NULL) st.push(cur->right);
        if (cur->left != NULL) st.push(cur->left);
    }
}

/// Post order visits left then right then node
void postorderRec(Node* root, string& out) {
    if (root == NULL) return;
    postorderRec(root->left, out);
    postorderRec(root->right, out);
    out += root->val + " ";
}

/// Post order with two stacks
///
/// The first stack gives node then right then left
///
/// Emptying the second stack reverses this into left then right then node
void postorderIter(Node* root, string& out) {
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* cur = s1.top();
        s1.pop();
        s2.push(cur);
        if (cur->left != NULL) s1.push(cur->left);
        if (cur->right != NULL) s1.push(cur->right);
    }
    while (!s2.empty()) {
        out += s2.top()->val + " ";
        s2.pop();
    }
}
