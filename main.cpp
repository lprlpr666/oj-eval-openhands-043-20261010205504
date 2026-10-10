#include <bits/stdc++.h>
using namespace std;

namespace LIST {
    struct Node {
        int val;
        Node* prev;
        Node* next;
        Node(int v) : val(v), prev(nullptr), next(nullptr) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int len = 0;

    void Pre() {
        head = tail = nullptr;
        len = 0;
    }

    // return pointer to node at index i (0-based). Assumes 0 <= i < len.
    Node* move(int i) {
        Node* cur = head;
        // Optimize: if i is closer to tail, start from tail.
        if (i > len / 2) {
            cur = tail;
            for (int idx = len - 1; idx > i; --idx) cur = cur->prev;
        } else {
            for (int idx = 0; idx < i; ++idx) cur = cur->next;
        }
        return cur;
    }

    void insert(int i, int x) {
        // i can be from 0 to len (inclusive). Insert before position i.
        Node* nd = new Node(x);
        if (len == 0) {
            head = tail = nd;
        } else if (i == 0) {
            nd->next = head;
            head->prev = nd;
            head = nd;
        } else if (i == len) {
            nd->prev = tail;
            tail->next = nd;
            tail = nd;
        } else {
            Node* cur = move(i); // node currently at position i
            nd->prev = cur->prev;
            nd->next = cur;
            cur->prev->next = nd;
            cur->prev = nd;
        }
        ++len;
    }

    void remove(int i) {
        if (len == 0) return; // should not happen per problem guarantees
        Node* cur = move(i);
        if (cur->prev) cur->prev->next = cur->next; else head = cur->next;
        if (cur->next) cur->next->prev = cur->prev; else tail = cur->prev;
        delete cur;
        --len;
    }

    int Get_length() {
        return len;
    }

    int Query(int i) {
        if (i < 0 || i >= len) return -1;
        Node* cur = move(i);
        return cur->val;
    }

    void Print() {
        if (len == 0) {
            cout << -1 << '\n';
            return;
        }
        Node* cur = head;
        bool first = true;
        while (cur) {
            if (!first) cout << ' ';
            cout << cur->val;
            first = false;
            cur = cur->next;
        }
        cout << '\n';
    }

    void Clear() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        len = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    LIST::Pre();
    for (int _ = 0; _ < n; ++_) {
        int op; cin >> op;
        if (op == 0) {
            cout << LIST::Get_length() << '\n';
        } else if (op == 1) {
            int p, x; cin >> p >> x;
            LIST::insert(p, x);
        } else if (op == 2) {
            int p; cin >> p;
            cout << LIST::Query(p) << '\n';
        } else if (op == 3) {
            int p; cin >> p;
            LIST::remove(p);
        } else if (op == 4) {
            LIST::Print();
        }
    }
    LIST::Clear();
    return 0;
}
