#include <iostream>
using namespace std;

// 🌳 Node structure for BST
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

// 🔹 INSERT a value into the BST
Node* insert(Node* root, int value) {
    if (root == nullptr)
        return new Node(value);  // create new node if tree empty

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);

    // equal values are ignored (BST stores unique keys)
    return root;
}

// 🔹 SEARCH for a value in the BST
bool search(Node* root, int key) {
    if (root == nullptr)
        return false;

    if (root->data == key)
        return true;
    else if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// 🔹 FIND MINIMUM value node (used in delete)
Node* findMin(Node* root) {
    while (root && root->left != nullptr)
        root = root->left;
    return root;
}

// 🔹 DELETE a node from the BST
Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node found
        // Case 1 & 2: Node with 0 or 1 child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: Node with 2 children
        Node* temp = findMin(root->right); // inorder successor
        root->data = temp->data;           // copy successor's value
        root->right = deleteNode(root->right, temp->data); // delete successor
    }
    return root;
}

// 🔹 INORDER Traversal (Left, Root, Right)
void inorder(Node* root) {
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// 🔹 PREORDER Traversal (Root, Left, Right)
void preorder(Node* root) {
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// 🔹 POSTORDER Traversal (Left, Right, Root)
void postorder(Node* root) {
    if (root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// 🔹 MAIN
int main() {
    Node* root = nullptr;
    int choice, value;

    do {
        cout << "\n--- Binary Search Tree Menu ---\n";
        cout << "1. Insert\n2. Search\n3. Delete\n4. Inorder\n5. Preorder\n6. Postorder\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                root = insert(root, value);
                break;

            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                if (search(root, value))
                    cout << "Value found!\n";
                else
                    cout << "Value not found.\n";
                break;

            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                break;

            case 4:
                cout << "Inorder: ";
                inorder(root);
                cout << endl;
                break;

            case 5:
                cout << "Preorder: ";
                preorder(root);
                cout << endl;
                break;

            case 6:
                cout << "Postorder: ";
                postorder(root);
                cout << endl;
                break;

            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}
