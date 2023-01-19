// KALAM
# include <bits/stdc++.h>

# define debug(x) cerr << #x << " = " << x << endl

using namespace std;

const int N = 300000 + 77;

struct SplayTree {
    struct Node {
        Node* lc = nullptr;
        Node* rc = nullptr;
        Node* parent = nullptr;
        int idx = -1;
    };
    vector < Node* > nodes;
    Node* get_node(int x) { return nodes[x]; }
    int create() {
        Node* node = new Node();
        nodes.push_back(node);
        node->idx = nodes.size() - 1;
        return nodes.size() - 1;
    }
    void left_rotate(Node* p) {
        assert(p->rc != nullptr);
        Node* x = p->rc;
        p->rc = x->lc;
        if(p->rc != nullptr)
            p->rc->parent = p;
        x->parent = p->parent;
        if(p->parent != nullptr && p->parent->lc == p)
            p->parent->lc = x;
        else if(p->parent != nullptr && p->parent->rc == p)
            p->parent->rc = x;
        p->parent = x;
        x->lc = p;
    }
    void right_rotate(Node* p) {
        assert(p->lc != nullptr);
        Node* x = p->lc;
        p->lc = x->rc;
        if(p->lc != nullptr)
            p->lc->parent = p;
        x->parent = p->parent;
        if(p->parent != nullptr && p->parent->lc == p)
            p->parent->lc = x;
        else if(p->parent != nullptr && p->parent->rc == p)
            p->parent->rc = x;
        p->parent = x;
        x->rc = p;
    }
    void rotate_up(Node* x) {
        assert(x->parent != nullptr);
        if(x->parent->lc == x) right_rotate(x->parent);
        else left_rotate(x->parent);
    }
    void rotate(Node* x) {
        if(x->parent == nullptr) return ;
        if(x->parent->parent == nullptr) {
            rotate_up(x);
        } else if((x->parent->parent->lc == x->parent && x->parent->lc == x) || (x->parent->parent->rc == x->parent && x->parent->rc == x)) {
            rotate_up(x->parent);
            rotate_up(x);
        } else {
            rotate_up(x);
            rotate_up(x);
        }
    }
    void splay(Node* x) {
        while(x->parent != nullptr)
            rotate(x);
    }
    Node* get_right_most(Node* x) {
        splay(x);
        while(x->rc != nullptr)
            x = x->rc;
        splay(x);
        return x;
    }
    Node* get_left_most(Node* x) {
        splay(x);
        while(x->lc != nullptr)
            x = x->lc;
        splay(x);
        return x;
    }
    void join(Node* x , Node* y) { // MAX(X) < MIN(Y)
        splay(y);
        x = get_right_most(x);
        assert(x->rc == nullptr);
        x->rc = y;
        y->parent = x;
    }
    void split(Node* x) { // split V <= key(x) and V > key(x)
        splay(x);
        if(x->rc == nullptr) return ;
        x->rc->parent = nullptr;
        x->rc = nullptr;
    }
    int get_left_most(int x) { return get_left_most(nodes[x])->idx; }
    void splay(int x) { splay(nodes[x]); }
    void join(int x , int y) { join(nodes[x] , nodes[y]); }
    void split(int x) { split(nodes[x]); }
};

struct LinkCutTree {
    SplayTree splaytree;
    struct Node {
        Node* parent = nullptr;
        int idx = -1;
    };
    vector < Node* > nodes;
    int create() {
        Node* node = new Node();
        node->idx = splaytree.create();
        nodes.push_back(node);
        return node->idx;
    }
    void access(Node* x) {
        while(1) {
            splaytree.splay(x->idx);
            x = nodes[splaytree.get_left_most(x->idx)];
            if(x->parent == nullptr) break ;

            Node* y = x->parent;
            splaytree.split(y->idx);
            splaytree.join(y->idx , x->idx);
        }
    }
    int join(Node* x , Node* y) { // make x , (y's root)'s parent
        y = get_root(y);
        if(get_root(x) == y) return -1;
        y->parent = x;
        return y->idx;
    }
    void cut(Node* x) { // cut x from parent
        Node* p = x->parent;
        if(p == nullptr) return ;
        splaytree.split(p->idx);
        x->parent = nullptr;
    }

    Node* get_root(Node* x) {
        access(x);
        return nodes[splaytree.get_left_most(x->idx)];
    }

    void cut(int x) { cut(nodes[x]); }
    int join(int x,  int y) { return join(nodes[x] , nodes[y]); }
    void access(int x) { access(nodes[x]); }
    int get_root(int x) { return get_root(nodes[x])->idx; }
};



int main() {


   return 0;
}
