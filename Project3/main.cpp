#include <iostream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

// Stores pos, depth, left and right children, and dialogue
struct Node {
    int depth;
    int pos;
    vector<tuple<string, Node*>> children;
    string dialogue;

    Node(int d, int p, const string& dia) : depth(d), pos(p), dialogue(dia) {}
};

Node* preToTree(vector<Node*> &nodes);

// Dialogue tree importing and exploration
int main() {

}

// Converts a preorder traversal list of nodes to a tree structure
Node* preToTree(vector<Node*> &nodes) {
    // Base Case if no nodes
    if (nodes.empty()) return nullptr;
    int n = nodes.size();

    // Stack tracks ancestors
    stack<Node*> st;
    // Root is first node
    Node* root = nodes[0];
    st.push(root);


}