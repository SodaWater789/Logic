/// @file
/// Task 4 finds the height of the parse tree
///
/// Height is the number of nodes on the longest path from the root to a leaf
///
/// A single atom has height 1

/// Height is 1 plus the bigger height of the two children
int heightRec(Node* root) {
    if (root == NULL) return 0;
    int l = heightRec(root->left);
    int r = heightRec(root->right);
    if (l > r) return l + 1;
    return r + 1;
}

/// Goes level by level with a queue and counts the levels
int heightIter(Node* root) {
    queue<Node*> q;
    q.push(root);
    int height = 0;
    while (!q.empty()) {
        // all nodes now in the queue are on the same level
        int size = q.size();
        height++;
        for (int i = 0; i < size; i++) {
            Node* cur = q.front();
            q.pop();
            if (cur->left != NULL) q.push(cur->left);
            if (cur->right != NULL) q.push(cur->right);
        }
    }
    return height;
}
