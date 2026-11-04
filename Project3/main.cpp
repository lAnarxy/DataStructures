#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;

// Stores pos, depth, left and right children, and dialogue
struct Node {
    int depth;
    int pos;
    vector<Node*> children;
    string responseKey;
    string dialogue;

    Node(int d, int p, const string& respKey, const string& dia) : depth(d), pos(p), responseKey(respKey), dialogue(dia) {}
};

Node* preToTree(vector<Node*> &nodes);

// Dialogue tree importing and exploration
int main() {
    string filename;
    ifstream file;
    // Prompt user for filename until a valid file is opened
    while (!file.is_open() || filename == "x") {
        file.clear();
        cout << "Enter the filename of the dialogue tree: " << endl;
        cin >> filename;
        file.open(filename);
    }
    // Read in the list of nodes from input
    vector<Node*> nodes;
    int depth, pos;
    string responseKey, dialogue;

    // Read the first node (root) separately
    file >> depth >> pos;
    file.ignore();
    getline(file, dialogue);
    cout << "Read node: depth=" << depth << ", pos=" << pos << ", responseKey=" << responseKey << ", dialogue=" << dialogue << endl;
    nodes.push_back(new Node(depth, pos, "", dialogue));

    // Read the rest of the nodes
    while (file >> depth >> pos >> responseKey) {
        file.ignore();
        getline(file, dialogue);
        cout << "Read node: depth=" << depth << ", pos=" << pos << ", responseKey=" << responseKey << ", dialogue=" << dialogue << endl;
        nodes.push_back(new Node(depth, pos, responseKey, dialogue));
    }

    // Sort by preorder positon then construct the tree
    sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) { return a->pos < b->pos; });
    Node* root = preToTree(nodes);

    // Dialogue exploration loop
    Node* current = root;
    while (current) {
        // Output the current dialogue
        cout << "\n"<< current->dialogue << endl;
        // Ends dialogue when there are no children left
        if (current->children.empty()) { break; }
        // Output possible responses
        for (size_t i = 0; i < current->children.size(); ++i) {
            cout << " - " << current->children[i]->responseKey << endl;
        }
        string choice;
        bool valid = false;
        // Gets repsponse until valid choice is made
        cin >> choice;
        while (!valid) {
            // Find the chosen child if it exists
            for (Node* child : current->children) {
                if (child->responseKey == choice) {
                    current = child;
                    valid = true;
                    break;
                }
            }
            // If it doesn't exist, prompt user to try again
            if (!valid) {
                cout << "Invalid choice. Please try again." << endl;
                cin >> choice;
            }
        }
    }

    // Tree Analysis
    cout << "\nWould you like to analyze the tree? (y/n): ";
    char analyzeChoice;
    cin >> analyzeChoice;
    if (analyzeChoice == 'y' || analyzeChoice == 'Y') {
        for (Node* node : nodes) {
            for (int i = 0; i < node->depth; ++i) {
                cout << "--";
            }
            if (!node->responseKey.empty()) {
                cout << "[" << node->responseKey << "] ";
            }
            cout << node->dialogue << endl;
        }
    }
}

// Converts a preorder traversal list of nodes to a tree structure
Node* preToTree(vector<Node*> &nodes) {
    // Base Case if no nodes
    if (nodes.empty()) return nullptr;
    int n = nodes.size();

    // Stack tracks ancestors
    stack<Node*> st;
    // Root is first node in list (pos 1, depth 0)
    Node* root = nodes[0];
    st.push(root);

    // Iterate through the rest of the nodes
    for (int i = 1; i < n; ++i) {
        Node* current = nodes[i];
        // Pop from stack until we find the parent of the current node
        while (!st.empty() && st.top()->depth >= current->depth) {
            st.pop();
        }
        // If stack is not empty, the top is the parent of the current node
        if (!st.empty()) {
            Node* parent = st.top();
            parent->children.push_back(current);
        }
        // Push the current node onto the stack
        st.push(current);
    }

    return root;
}