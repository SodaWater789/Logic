/// @file
/// Task 2 builds the parse tree from the prefix tokens

/// Builds the parse tree and returns the root
///
/// Reads the prefix tokens from right to left with a stack of subtrees
///
/// An atom is pushed as a leaf
///
/// A not pops one subtree and keeps it in right
///
/// An and or implies pops the left subtree first and then the right subtree
Node* buildTree(vector<string>& prefix) {
    stack<Node*> st;
    for (int i = prefix.size() - 1; i >= 0; i--) {
        Node* n = newNode(prefix[i]);
        if (prefix[i] == "~") {
            n->right = st.top();
            st.pop();
        }
        else if (isOp(prefix[i])) {
            n->left = st.top();
            st.pop();
            n->right = st.top();
            st.pop();
        }
        st.push(n);
    }
    return st.top();
}

/// Draws the tree sideways with the root on the left
///
/// The right child is drawn above and the left child below
void printTree(Node* root, int depth) {
    if (root == NULL) return;
    printTree(root->right, depth + 1);
    cout << string(depth * 4, ' ') << root->val << endl;
    printTree(root->left, depth + 1);
}

/// Frees every node of the tree
void deleteTree(Node* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
