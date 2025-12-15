#include <iostream>
using namespace std;

class Stack {
private:
    char arr[100];
    int top;
public:
    Stack() { top = -1; }

    bool isEmpty() { return top == -1; }
    bool isFull()  { return top == 99; }

    void push(char x) {
        if (!isFull()) arr[++top] = x;
    }

    char pop() {
        if (!isEmpty()) return arr[top--];
        return '\0';
    }

    char peek() {
        if (!isEmpty()) return arr[top];
        return '\0';
    }
};

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool isOperand(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

string infixToPostfix(string infix) {
    Stack st;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (isOperand(c)) {
            postfix += c;
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (!st.isEmpty() && st.peek() != '(') {
                postfix += st.pop();
            }
            st.pop();
        }
        else if (isOperator(c)) {
            while (!st.isEmpty() && precedence(c) <= precedence(st.peek())) {
                postfix += st.pop();
            }
            st.push(c);
        }
    }

    while (!st.isEmpty()) {
        postfix += st.pop();
    }

    return postfix;
}

string reverseString(string s) {
    string r = "";
    for (int i = s.length() - 1; i >= 0; i--)
        r += s[i];
    return r;
}

string changeBrackets(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') s[i] = ')';
        else if (s[i] == ')') s[i] = '(';
    }
    return s;
}

string infixToPrefix(string infix) {
    string rev = reverseString(infix);
    rev = changeBrackets(rev);

    string post = infixToPostfix(rev);

    string prefix = reverseString(post);

    return prefix;
}

class IntStack {
private:
    int arr[100];
    int top;
public:
    IntStack() { top = -1; }

    void push(int x) { arr[++top] = x; }
    int pop() { return arr[top--]; }
    bool isEmpty() { return top == -1; }
};

int postfixEval(string exp) {
    IntStack st;

    for (int i = 0; i < exp.length(); i++) {
        char c = exp[i];

        if (isdigit(c)) {
            st.push(c - '0');
        }
        else if (isOperator(c)) {
            int b = st.pop();
            int a = st.pop();
            int result = 0;

            switch (c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }
            st.push(result);
        }
    }
    return st.pop();
}

int prefixEval(string exp) {
    IntStack st;

    for (int i = exp.length() - 1; i >= 0; i--) {
        char c = exp[i];

        if (isdigit(c)) {
            st.push(c - '0');
        }
        else if (isOperator(c)) {
            int a = st.pop();
            int b = st.pop();
            int result = 0;

            switch (c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }
            st.push(result);
        }
    }
    return st.pop();
}

int main() {
    string exp = "(A+B)*(C-D)";

    cout << "Infix   : " << exp << endl;
    cout << "Postfix : " << infixToPostfix(exp) << endl;
    cout << "Prefix  : " << infixToPrefix(exp) << endl;

    cout << "Postfix Eval 3 4 + 2 * : " << postfixEval("34+2*") << endl;
    cout << "Prefix Eval * + 3 4 2   : " << prefixEval("*+342") << endl;

    return 0;
}
