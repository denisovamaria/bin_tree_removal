#include <iostream>
#include <fstream>

using namespace std;

struct TreeNode {
    explicit TreeNode(int key) {
        this->key = key;
    }

    int key;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
};

class BinTree {
public:
    explicit BinTree() {
        root = nullptr;
    }

    void Insert(int a) {
        TreeNode **c = &root;
        while (*c) {
            TreeNode &n = **c;
            if (a < n.key) {
                c = &n.left;
            } else if (a > n.key) {
                c = &n.right;
            } else {
                return;
            }
        }
        *c = new TreeNode(a);
    }

    TreeNode *root;
};

void Travel(TreeNode *v, std::ofstream &out) {
    if (v) {
        out << v->key << '\n';
        Travel(v->left, out);
        Travel(v->right, out);
    }
}

TreeNode *Min_Node(TreeNode *v) {
    if (v->left != nullptr)
        return Min_Node(v->left);
    else return v;
}

TreeNode *Delete(int x, TreeNode *v) {
    if (v == nullptr)
        return nullptr;
    if (x < v->key) {
        v->left = Delete(x, v->left);
        return v;
    } else if (x > v->key) {
        v->right = Delete(x, v->right);
        return v;
    }
    if (v->left == nullptr) {
        return v->right;
    } else if (v->right == nullptr) {
        return v->left;
    } else {
        int min = Min_Node(v->right)->key;
        v->key = min;
        v->right = Delete(min, v->right);
    }
    return v;
}


int main() {
    ifstream in("input.txt");
    int a;
    BinTree tree;
    int x;
    in >> x;
    in.ignore();
    while (in >> a) {
        tree.Insert(a);
    }
    in.close();
    ofstream out("output.txt");
    tree.root = Delete(x, tree.root);
    Travel(tree.root, out);
    out.close();
}