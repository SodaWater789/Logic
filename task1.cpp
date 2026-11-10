/// @file
/// Task 1 splits the formula into tokens and converts infix to prefix

/// Splits the formula into tokens
///
/// An atom can have more than one letter like x12
vector<string> tokenize(string s) {
    vector<string> tokens;
    int n = s.length();
    int i = 0;
    while (i < n) {
        if (s[i] == ' ') {
            i++;
        }
        else if (isalnum(s[i])) {
            string atom = "";
            while (i < n && isalnum(s[i])) {
                atom += s[i];
                i++;
            }
            tokens.push_back(atom);
        }
        else {
            tokens.push_back(string(1, s[i]));
            i++;
        }
    }
    return tokens;
}

/// Converts infix tokens to prefix tokens
///
/// Step 1 reverse the tokens
///
/// Step 2 swap open and close brackets
///
/// Step 3 make postfix with a stack
///
/// Step 4 reverse the postfix to get prefix
///
/// No precedence rules are needed because the formula is fully bracketed
vector<string> infixToPrefix(vector<string> tokens) {
    reverse(tokens.begin(), tokens.end());

    for (int i = 0; i < (int)tokens.size(); i++) {
        if (tokens[i] == "(") tokens[i] = ")";
        else if (tokens[i] == ")") tokens[i] = "(";
    }

    stack<string> st;
    vector<string> result;
    for (int i = 0; i < (int)tokens.size(); i++) {
        string t = tokens[i];
        if (t == "(") {
            st.push(t);
        }
        else if (t == ")") {
            // pop connectives until the matching open bracket
            while (st.top() != "(") {
                result.push_back(st.top());
                st.pop();
            }
            st.pop();
        }
        else if (isOp(t)) {
            st.push(t);
        }
        else {
            result.push_back(t);
        }
    }
    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }

    reverse(result.begin(), result.end());
    return result;
}
