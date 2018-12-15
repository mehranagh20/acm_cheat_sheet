struct trie {
    bool isWord;
    map<char, trie*> children;
    trie(): isWord(false){}
};

void trieInsert(trie *&root, string &str){
    trie* cur = root;
    for(auto &e: str){
        if(!cur->children.count(e)) cur->children[e] = new trie;
        cur = cur->children[e];
    }
    cur->isWord = true;
}

bool trieSearch(trie *&root, string &str){
    trie* cur = root;
    for(auto &e: str){
        if(!cur->children.count(e)) return false;
        cur = cur->children[e];
    }

    return cur->isWord;
}

// call with root. search for str before deletion
void trieDelete(trie *cur, string &str, int ind){
    trie *nxt = cur->children[str[ind]];
    if(ind == str.size() - 1){
        nxt->isWord = false; return;
    }
    trieDelete(nxt, str, ind + 1);

    if(nxt->children.empty()) {
        delete nxt; cur->children.erase(str[ind]);
    }
}

// inside main
trie *root = new trie;
