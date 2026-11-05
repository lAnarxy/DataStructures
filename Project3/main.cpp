#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Stores pos, depth, left and right children, and dialogue
struct Node {
    int depth;
    int pos;
    Node* parent;
    vector<Node*> children;
    string responseKey;
    string dialogue;

    Node(int d, int p, const string& respKey, const string& dia) : depth(d), pos(p), parent(nullptr), responseKey(respKey), dialogue(dia) {}
};

inline ostream& operator<<(ostream& os, const Node* n);
Node* preToTree(vector<Node*> &nodes);
int nodeHeight(const Node* root);
bool isBalancedTree(const Node* root);
bool isPerfectTree(const Node* root, int depth, int level = 0);

// Dialogue tree importing and exploration
int main() {
    string filename;
    ifstream file;
    string outputName = "about_tree.txt";
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
    // cout << "Read node: depth=" << depth << ", pos=" << pos << ", responseKey=" << responseKey << ", dialogue=" << dialogue << endl;
    nodes.push_back(new Node(depth, pos, "", dialogue));

    // Read the rest of the nodes
    while (file >> depth >> pos >> responseKey) {
        file.ignore();
        getline(file, dialogue);
        // cout << "Read node: depth=" << depth << ", pos=" << pos << ", responseKey=" << responseKey << ", dialogue=" << dialogue << endl;
        nodes.push_back(new Node(depth, pos, responseKey, dialogue));
    }
    file.close();

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

    // Output file
    ofstream outputFile(outputName);

    // Tree Visualization
    outputFile << "Tree Visualization:" << endl;
    for (Node* node : nodes) {
        for (int i = 0; i < node->depth; ++i) {
            outputFile << "--";
        }
        if (!node->responseKey.empty()) {
            outputFile << "[" << node->responseKey << "] ";
        }
        outputFile << node->dialogue << endl;
    }

    // Tree properties
    int height = -1;
    bool bin = true;
    bool prop = true;
    vector<int> internalNodes;
    vector<int> externalNodes;
    // Counts internal and external nodes, and checks for Binary and Proper tree conditions
    for (const Node* node : nodes) {
        if (!node->children.empty()) {
            internalNodes.push_back(node->pos);
            if(node->children.size() == 1) {
                prop = false;
            }
            if (node->children.size() > 2) {
                bin = false;
                prop = false;
            }
        } else {
            externalNodes.push_back(node->pos);
        }
        height = max(height, node->depth);
    }

    // Prints calculated data
    outputFile << "\nTree Properties:" << endl;
    outputFile << " - " << root << endl;
    outputFile << " - Num Internal: " << internalNodes.size() << endl;
    outputFile << " - Num External: " << externalNodes.size() << endl;
    outputFile << " - Height: " << height + 1 << endl;
    outputFile << " - Internal Nodes: " ;
    for (int pos : internalNodes) { outputFile << pos << " "; }
    outputFile << endl;
    outputFile << " - External Nodes: " ;
    for (int pos : externalNodes) { outputFile << pos << " "; }
    outputFile << endl;
    outputFile << " - Is Binary: " << (bin ? "Yes" : "No") << endl;
    if (bin) {
        outputFile << " - Is Proper: " << (prop ? "Yes" : "No") << endl;
        outputFile << " - Is Perfect: " << (isPerfectTree(root, height) ? "Yes" : "No") << endl;
        outputFile << " - Is Balanced: " << (isBalancedTree(root) ? "Yes" : "No") << endl;
    }
    outputFile.close();

    // Tree Exploration
    cout << "\nWould you like to further explore the tree? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        int explorePos;
        string input;
        Node* exploreNode = nullptr;
        while (input != "exit") {
            cout << "\nWhich node would you like to explore (enter position or \"exit\"): ";
            if (cin >> explorePos) {
                exploreNode= nodes[explorePos - 1];
            } else {
                cin.clear();
                cin >> input;
                if (input == "exit") {
                    cout << "Goodbye!" << endl;
                    break;
                } else {
                    cout << "Invalid input. Please try again." << endl;
                    continue;
                }
            }
            if (explorePos < 0 || explorePos > nodes.size()) {
                cout << "Invalid input. Please try again." << endl;
                continue;
            }

            // Prints explored node
            cout << exploreNode << endl;

            // Prints one ancestor
            cout << "Ancestor: ";
            if (exploreNode->parent) {
                cout << exploreNode->parent << endl;
            } else {
                cout << "None" << endl;
            }

            // Prints one descendent
            cout << "Descendant: ";
            if (!exploreNode->children.empty()) {
                cout << exploreNode->children[0] << endl;
            } else {
                cout << "None" << endl;
            }

            // Prints one sibling
            cout << "Sibling: ";
            if (exploreNode->parent && exploreNode->parent->children.size() > 1) {
                Node* sibling = nullptr;
                for (const auto& child : exploreNode->parent->children) {
                    if (child != exploreNode) {
                        sibling = child;
                        break;
                    }
                }
                cout << sibling << endl;
            } else {
                cout << "None" << endl;
            }

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
            current->parent = parent;
        }
        // Push the current node onto the stack
        st.push(current);
    }

    return root;
}

// Checks if tree is perfect
bool isPerfectTree(const Node* root, int depth, int level) {
    // Empty tree is perfect
    if (!root) { return true; }
    // If current node is second to last level, it must have 2 children exactly.
    if (level == depth - 1) { return root->children.size() == 2; }
    bool leftPerfect = true;
    bool rightPerfect = true;
    if (root->children.size() == 2) {
        leftPerfect = isPerfectTree(root->children[0], depth, level + 1);
        rightPerfect = isPerfectTree(root->children[1], depth, level + 1);
    } else if (root->children.size() == 1) {
        leftPerfect = isPerfectTree(root->children[0], depth, level + 1);
        rightPerfect = true;
    }
    return leftPerfect && rightPerfect;
}

// Height checker for balance function
// Returns the height of the tree if child subtrees height differ by at most 1, returns -1 otherwise
int nodeHeight(const Node* root) {
    if (!root) return 0;
    int leftHeight = 0;
    int rightHeight = 0;
    if (root->children.size() == 2) {
        leftHeight = nodeHeight(root->children[0]);
        rightHeight = nodeHeight(root->children[1]);
    } else if (root->children.size() == 1) {
        leftHeight = nodeHeight(root->children[0]);
        rightHeight = 0;
    } 
    if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) {
        return -1;
    }
    return max(leftHeight, rightHeight) + 1;
}

// Checks if tree is balanced, returns -1 if not
bool isBalancedTree(const Node* root) {
    return nodeHeight(root) != -1;
}

// Operator overload for printing nodes.
inline ostream& operator<<(ostream& os, const Node* n) {
    if (n->depth == 0) {
        os << "Root Node: " << n->dialogue;
    } else {
        os << "Node at preorder position " << n->pos << ", depth " << n->depth << ". [" << n->responseKey << "] " << n->dialogue;
    }
    return os;
}