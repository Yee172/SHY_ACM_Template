struct Trie {
    Trie* nxt[26];
    int value;
};

inline int get_trie_index(const char c) {
    return (int)(c - 'a');
}

inline Trie * new_Trie(bool clr = false) {
    static int top = 0;
    static const int trie = 100002;
    static Trie tries[trie];
    if (clr) {
        top = 0;
        memset(tries, 0, sizeof(tries));
        return nullptr;
    }
    return &tries[top++];
}

Trie * trie;

inline void insert(const char * s, int len = 0) {
    if (len == 0)
        len = strlen(s);
    if (trie == nullptr)
        trie = new_Trie();
    Trie * t = trie;
    for (int i = 0; i < len; ++i) {
        int c = get_trie_index(s[i]);
        if (t->nxt[c] == nullptr) {
            t->nxt[c] = new_Trie();
            t = t->nxt[c];
        } else
            t = t->nxt[c];
    }
    t->value = len;
}

bool path_in_trie(const char* s) {
    Trie *t = trie;
    if (t == nullptr)
        return false;
    for (int i = 0; s[i]; ++i) {
        int c = get_trie_index(s[i]);
        if (t->nxt[c] == nullptr)
            return false;
        t = t->nxt[c];
    }
    return true;
}

bool contains_in_trie(const char* s){
    Trie * t = trie;
    if (t == nullptr)
        return false;
    for (int i = 0; s[i]; ++i) {
        int c = get_trie_index(s[i]);
        if (t->nxt[c] == nullptr)
            return false;
        t = t->nxt[c];
    }
    return t->value != 0;
}
