#include <string>
#include <iostream>
using namespace std;


using namespace std;

class lexicon {
public:
    lexicon() : root(nullptr) {}

    ~lexicon() {
        purge_all(root);
    }

    void insert(const string &s) {
        if (root == nullptr) {
            root = new bst_node(s, 1);
            return;
        }

        bst_node *p = root;
        adding_leaf_book(p, s);
    }

    int lookup(const string &s) {
        bst_node *p = root;

        bst_node *q = finding_leaf_book(p, s);

        if (q == nullptr) {
            return 0;
        } else {
            return q->frequency;
        }
    }

    int depth(const string &s) {
        bst_node *p = root;

        bst_node *q = finding_leaf_book(p, s);

        if (q == nullptr) {
            return -1;
        } else {
            bst_node *z = root;

            return term_of_depth(z, s, 0);
        }

    }

    void replace(const string &s1, const string &s2) {
        bst_node *q = root;

        bst_node *q1 = finding_leaf_book(q, s1);

        if (q1 == nullptr) {
            return;
        } else {


            bst_node *g = root;

            purge(g, s1);

            bst_node *t = root;

            bst_node *y = finding_leaf_book(t, s2);

            if (y == nullptr) {
                bst_node *i = root;
                special1_adding_leaf_book(i, s2, q1->frequency);
            } else {
                y->frequency += q1->frequency;
            }
        }
    }

    friend ostream &operator<<(ostream &out, const lexicon &l) {
        bst_node *q = l.root;

        l.write_all(q, out);

        return out;
    }


private:
    struct bst_node {
        string name_of_book;
        int frequency;
        bst_node *left, *right;

        bst_node(const string &k, const int &v) :
                name_of_book(k), frequency(v), left(nullptr), right(nullptr) {}
    };

    bst_node *root;

    bst_node *adding_leaf_book(bst_node *p, const string &s) {
        if (p == nullptr) {
            return new bst_node(s, 1);
        }
        if (p->name_of_book < s) {
            p->right = adding_leaf_book(p->right, s);
        } else if (p->name_of_book > s) {
            p->left = adding_leaf_book(p->left, s);
        } else {
            p->frequency++;
        }

        return p;
    }

    bst_node *special1_adding_leaf_book(bst_node *p, const string &s, int t) {

        if (p == nullptr) {
            if (root == nullptr) {
                root = new bst_node(s, 1);
                return root;
            }
            return new bst_node(s, t);
        }
        if (p->name_of_book < s) {
            p->right = special1_adding_leaf_book(p->right, s, t);
        } else if (p->name_of_book > s) {
            p->left = special1_adding_leaf_book(p->left, s, t);
        }


        return p;
    }

    bst_node *finding_leaf_book(bst_node *p, const string &s) {

        if (p == nullptr) {
            return nullptr;
        }

        if (p->name_of_book < s) {
            return finding_leaf_book(p->right, s);
        } else if (p->name_of_book > s) {
            return finding_leaf_book(p->left, s);
        } else {
            return p;
        }
    }

    int term_of_depth(bst_node *p, const string &s, int depth) {
        if (p != nullptr) {
            if (p->name_of_book < s) {
                return term_of_depth(p->right, s, depth + 1);
            } else if (p->name_of_book > s) {
                return term_of_depth(p->left, s, depth + 1);
            } else {
                return depth;
            }
        } else {
            depth = 0;
        }
        return depth;
    }

    void purge(bst_node *p, const string &s) {

        if (root->name_of_book == s) {
            if (root->left != nullptr && root->right != nullptr) {
                bst_node *q = root;
                bst_node *q1 = root->left;

                root = q1;


                bst_node * w = q->left;
                while(w->right != nullptr) {
                    w = w->right;
                }

                w->right = q->right;
                delete q;

                return;
            }

            if (root->left == nullptr && root->right == nullptr) {
                bst_node *q = root;

                root = nullptr;

                delete q;

                return;
            }

            if (root->left == nullptr) {
                bst_node *q = root;

                root = q->right;

                delete q;

                return;
            }

            if (root->right == nullptr) {
                bst_node *q = root;

                root = q->left;

                return;
            }
        }
        if(p->left != nullptr) {
            if (p->left->name_of_book == s) {
                if (p->left->left != nullptr && p->left->right != nullptr) {
                    bst_node *q = p->left;

                    p->left = q->left;

                    bst_node *z = q->left;

                    while (z->right != nullptr) {
                        z = z->right;
                    }

                    z->right = q->right;

                    delete q;

                    return;
                }
                if (p->left->left == nullptr && p->left->right == nullptr) {
                    bst_node *q = p->left;

                    p->left = nullptr;

                    delete q;

                    return;
                }

                if (p->left->left == nullptr) {
                    bst_node *q = p->left;

                    p->left = q->right;

                    delete q;

                    return;
                }

                if (p->left->right == nullptr) {
                    bst_node *q = p->left;

                    p->left = q->left;

                    delete q;

                    return;
                }
            }
        }
        if(p->right != nullptr) {
            if (p->right->name_of_book == s) {

                if (p->right->left != nullptr) {
                    bst_node *q = p->right;

                    p->right = q->left;

                    bst_node *z = q->left;

                    while (z->right != nullptr) {
                        z = z->right;
                    }

                    z->right = q->right;

                    delete q;

                    return;
                }



                if (p->right->right == nullptr && p->right->left == nullptr) {

                    bst_node *q = p->right;

                    p->right = nullptr;

                    delete q;

                    return;
                }
                if (p->right->left == nullptr || p->right->right == nullptr) {
                    if (p->right->left == nullptr) {
                        bst_node *q = p->right;

                        p->right = p->right->right;

                        delete q;

                        return;
                    } else {
                        bst_node *q = p->right;

                        p->right = p->right->left;

                        delete q;

                        return;
                    }
                }
            }
        }
        if (p->name_of_book < s) {
            purge(p->right, s);
        } else if (p->name_of_book > s) {
            purge(p->left, s);
        }
    }


     void purge_all(bst_node * p) {
         if(p!=nullptr) {
             if(p->left!=nullptr) {
                 purge_all(p->left);
             }
             if(p->right!= nullptr) {
                 purge_all(p->right);
             }
             delete p;
         }
     }

    void write_all(bst_node * p, ostream & out) const {
        if(p!=nullptr) {
            write_all(p->left, out);
            out << p->name_of_book << " " << p->frequency << endl;
            write_all(p->right, out);
        }
    }

};

int main () {

}