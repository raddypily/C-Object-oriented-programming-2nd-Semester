#include "iostream"
#include <string>
#include <map>

using namespace std;

struct node {
    char info;
    node *right, *left;
    node(char c, node *r, node *l) {
        info = c;
        right = r;
        left = l;
    }
};

void add_a_node(node *&root, node *& previous, char c, string pos) {
    node *p = new node(c, nullptr, nullptr);
    if(root != nullptr) {
        if(pos == "left") {
            previous->left = p;
            previous = p;
        }
        else    {
            previous->right = p;
            previous = p;
        }
    }
    else {
        root = p;
    }
}

void print(node *p) {
    if(p != nullptr) {
        cout << p->info << endl;
        print(p->left);
        print(p->right);
    }
}

void find_freq(node *p, map<char, int>& letters) {
    if(p != nullptr) {
        auto it = letters.find(p->info);

        if(it != letters.end()) {
            letters[p->info]++;
        }
        else {
            letters[p->info] = 1;
        }

        find_freq(p->left, letters);
        find_freq(p->right, letters);
    }
}

int main () {
    node *root = nullptr;

    add_a_node(root, root, 'a', "left");

    node * q = root;

    add_a_node(root, q, 'b', "left");

    node *term = q;

    add_a_node(root, term, 'c', "right");

    add_a_node(root, q, 'e', "left");

    node *term1 = q;

    add_a_node(root, term1, 'h', "right");

    add_a_node(root, q, 'f', "left");

    node *z = root;

    add_a_node(root, z, 'f', "right");

    node *t = z;

    add_a_node(root, t, 'e', "left");

    add_a_node(root, t, 'e', "right");

    add_a_node(root, z, 'b', "right");
    map<char, int> letters;

    find_freq(root, letters);

    for(auto &x:letters) {
        cout << x.first << " " << x.second << endl;
    }
}