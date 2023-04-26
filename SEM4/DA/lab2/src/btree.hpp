#pragma once
#include <fstream>
#include "string.hpp"
#include "vector.hpp"


struct TBTreeNode {
private:
    TVector<TString> keys;
    TVector<unsigned long long> dataNode;
    TVector<TBTreeNode*> childs;
    int t;
    int keyCount;
    bool leaf;
public:
    TBTreeNode(int t, bool leaf);
    void Print();
    void Insert(TString& key, unsigned long long data);
    void Split(int i, TBTreeNode* node);
    bool IsFull();
    int FindKey(TString& key);
    void Delete(TString& key);
    void DeleteFromLeaf(int i);
    void DeleteNotLeaf(int i);
    TString GetPrev(int i);
    TString GetNext(int i);
    unsigned long long GetPrevData(int i);
    unsigned long long GetNextData(int i);
    void Fill(int i);
    void FromPrev(int i);
    void FromNext(int i);
    void Merge(int i);
    TBTreeNode* Search(TString& key);
    void WriteToFile(ofstream& File);
    friend class TBTree;
};

class TBTree {
private:
    TBTreeNode* root;
    int t;
public:
    TBTree(int t);
    void Print();
    bool Insert(TString& key, unsigned long long data);
    bool Delete(TString& key);
    TBTreeNode* Search(TString& key);
    bool Find(TString& key);
    unsigned long long operator [](TString& key);
    void ReadFromFile(ifstream& File);
    void WriteToFile(ofstream& File);
    void DeleteTree();
};


TBTreeNode::TBTreeNode(int t, bool leaf): t(t), leaf(leaf), keys(2 * t - 1), dataNode(2 * t - 1), childs(2 * t), keyCount(0) {
}

void TBTreeNode::Print() {
    int i;
    for(i = 0; i < keyCount; i++) {
        if(leaf == false)
            childs[i]->Print();
        cout << " " << keys[i] << ": " << dataNode[i] << '\n';
    }

    if(leaf == false)
        childs[i]->Print();
}
bool TBTreeNode::IsFull() {
    return this->keyCount == 2 * t - 1;
}

void TBTreeNode::Split(int i, TBTreeNode* y) {
    TBTreeNode* z = new TBTreeNode(y->t, y->leaf);
    z->keyCount = t - 1;

    for(int j = 0; j < t - 1; ++j) {
        z->keys[j] = y->keys[j + t];
        z->dataNode[j] = y->dataNode[j + t];
    }

    if(y->leaf == false) {
        for(int j = 0; j < t; ++j) {
            z->childs[j] = y->childs[j + t];
        }
    }

    y->keyCount = t - 1;
    for(int j = keyCount; j >= i + 1; j--)
        childs[j + 1] = childs[j];
    childs[i + 1] = z;

    for(int j = keyCount - 1; j >= i; --j) {
        keys[j + 1] = keys[j];
        dataNode[j + 1] = dataNode[j];
    }

    keys[i] = y->keys[t - 1];
    dataNode[i] = y->dataNode[t - 1];
    keyCount = keyCount + 1;
}

void TBTreeNode::Insert(TString& key, unsigned long long data) {
    int i = keyCount - 1;

    if(leaf == true) {
        while(i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            dataNode[i + 1] = dataNode[i];
            --i;
        }
        keys[i + 1] = key;
        dataNode[i + 1] = data;
        ++keyCount;
    } else {
        while(i >= 0 && keys[i] > key) {
            --i;
        }
        ++i;
        if(childs[i]->IsFull()) {
            Split(i, childs[i]);
            if(keys[i] < key) {
                ++i;
            }
        }
        childs[i]->Insert(key, data);
    }
}

TBTreeNode* TBTreeNode::Search(TString& key) {
    int i = 0;
    while(i < keyCount && key > keys[i]) {
        ++i;
    }
    if(i < keyCount && keys[i] == key)
        return this;
    if(leaf == true)
        return nullptr;
    return childs[i]->Search(key);
}

TBTree::TBTree(int t): t(t), root(nullptr) {

}

void TBTree::Print() {
    if(root != nullptr) {
        root->Print();
    }
}

TBTreeNode* TBTree::Search(TString& key) {
    return (root == nullptr) ? nullptr : root->Search(key);
}

bool TBTree::Insert(TString& key, unsigned long long data) {
    if(!Find(key)) {
        if(root == nullptr) {
            root = new TBTreeNode(t, true);
            root->keys[0] = key;
            root->dataNode[0] = data;
            root->keyCount = 1;
        } else {
            if(root->IsFull()) {
                TBTreeNode* tmp = new TBTreeNode(t, false);
                tmp->childs[0] = root;
                tmp->Split(0, root);
                tmp->Insert(key, data);
                root = tmp;
            } else {
                root->Insert(key, data);
            }
        }
        return true;
    } else {
        return false;
    }
}

int TBTreeNode::FindKey(TString& key) {
    int i = 0;
    while(i < keyCount && keys[i] < key) {
        ++i;
    }
    return i;
}

void TBTreeNode::Delete(TString& key) {
    int i = FindKey(key);

    if(i < keyCount && keys[i] == key) {
        if(leaf) {
            DeleteFromLeaf(i);
        } else {
            DeleteNotLeaf(i);
        }
    } else {
        if(leaf) {
            return;
        }
        bool flag = ((i == keyCount) ? true : false);

        if(childs[i]->keyCount < t) {
            Fill(i);
        }

        if(flag && i > keyCount) {
            childs[i - 1]->Delete(key);
        } else {
            childs[i]->Delete(key);
        }
    }
}

void TBTreeNode::DeleteFromLeaf(int i) {
    for(int j = i + 1; j < keyCount; ++j) {
        keys[j - 1] = keys[j];
        dataNode[j - 1] = dataNode[j];
    }

    --keyCount;
}

void TBTreeNode::DeleteNotLeaf(int i) {
    TString key = keys[i];
    if(childs[i]->keyCount >= t) {
        TString prev = GetPrev(i);
        unsigned long long prevData = GetPrevData(i);
        keys[i] = prev;
        dataNode[i] = prevData;
        childs[i]->Delete(prev);
    } else if(childs[i + 1]->keyCount >= t) {
        TString next = GetNext(i);
        unsigned long long nextData = GetNextData(i);
        keys[i] = next;
        dataNode[i] = nextData;
        childs[i + 1]->Delete(next);
    } else {
        Merge(i);
        childs[i]->Delete(key);
    }
}

TString TBTreeNode::GetPrev(int i) {
    TBTreeNode* cur = childs[i];
    while(!cur->leaf) {
        cur = cur->childs[cur->keyCount];
    }
    return cur->keys[cur->keyCount - 1];
}

TString TBTreeNode::GetNext(int i) {
    TBTreeNode* cur = childs[i + 1];
    while(!cur->leaf) {
        cur = cur->childs[0];
    }
    return cur->keys[0];
}

unsigned long long TBTreeNode::GetPrevData(int i) {
    TBTreeNode* cur = childs[i];
    while(!cur->leaf) {
        cur = cur->childs[cur->keyCount];
    }
    return cur->dataNode[cur->keyCount - 1];
}

unsigned long long TBTreeNode::GetNextData(int i) {
    TBTreeNode* cur = childs[i + 1];
    while(!cur->leaf) {
        cur = cur->childs[0];
    }
    return cur->dataNode[0];
}

void TBTreeNode::Fill(int i) {
    if(i != 0 && childs[i - 1]->keyCount >= t) {
        FromPrev(i);
    } else if(i != keyCount && childs[i + 1]->keyCount >= t) {
        FromNext(i);
    } else {
        if(i != keyCount) {
            Merge(i);
        } else {
            Merge(i - 1);
        }
    }
}

void TBTreeNode::FromPrev(int i) {
    TBTreeNode* child = childs[i];
    TBTreeNode* sibling = childs[i - 1];

    for(int j = child->keyCount - 1; j >= 0; --j) {
        child->keys[j + 1] = child->keys[j];
        child->dataNode[j + 1] = child->dataNode[j];
    }

    if(!child->leaf) {
        for(int j = child->keyCount; j >= 0; --j) {
            child->childs[j + 1] = child->childs[j];
        }
    }

    child->keys[0] = keys[i - 1];
    child->dataNode[0] = dataNode[i - 1];

    if(!child->leaf) {
        child->childs[0] = sibling->childs[sibling->keyCount];
    }

    keys[i - 1] = sibling->keys[sibling->keyCount - 1];
    dataNode[i - 1] = sibling->dataNode[sibling->keyCount - 1];

    ++child->keyCount;
    --sibling->keyCount;
}

void TBTreeNode::FromNext(int i) {
    TBTreeNode* child = childs[i];
    TBTreeNode* sibling = childs[i + 1];

    child->keys[child->keyCount] = keys[i];
    child->dataNode[child->keyCount] = dataNode[i];

    if(!(child->leaf)) {
        child->childs[child->keyCount + 1] = sibling->childs[0];
    }

    keys[i] = sibling->keys[0];
    dataNode[i] = sibling->dataNode[0];

    for(int j = 1; j < sibling->keyCount; ++j) {
        sibling->keys[j - 1] = sibling->keys[j];
        sibling->dataNode[j - 1] = sibling->dataNode[j];
    }

    if(!sibling->leaf) {
        for(int j = 1; j <= sibling->keyCount; ++j) {
            sibling->childs[j - 1] = sibling->childs[j];
        }
    }

    ++child->keyCount;
    --sibling->keyCount;
}

void TBTreeNode::Merge(int i) {
    TBTreeNode* child = childs[i];
    TBTreeNode* sibling = childs[i + 1];

    child->keys[t - 1] = keys[i];
    child->dataNode[t - 1] = dataNode[i];

    for(int j = 0; j < sibling->keyCount; ++j) {
        child->keys[j + t] = sibling->keys[j];
        child->dataNode[j + t] = sibling->dataNode[j];
    }

    if(!child->leaf) {
        for(int j = 0; j <= sibling->keyCount; ++j) {
            child->childs[j + t] = sibling->childs[j];
        }
    }

    for(int j = i + 1; j < keyCount; ++j) {
        keys[j - 1] = keys[j];
        dataNode[j - 1] = dataNode[j];
    }

    for(int j = i + 2; j <= keyCount; ++j) {
        childs[j - 1] = childs[j];
    }

    child->keyCount += sibling->keyCount + 1;
    --keyCount;
    delete sibling;
}


void TBTreeNode::WriteToFile(ofstream& File) {
    int i;

    for(i = 0; i < keyCount; i++) {
        if(leaf == false)
            childs[i]->WriteToFile(File);
        File.write(keys[i].CStr(), sizeof(char) * 257);
        File.write(reinterpret_cast<char*>(&dataNode[i]), sizeof(unsigned long long));
    }

    if(leaf == false)
        childs[i]->WriteToFile(File);
}
bool TBTree::Delete(TString& key) {
    if(Find(key)) {
        if(root == nullptr) {
            return false;
        }

        root->Delete(key);

        if(root->keyCount == 0) {
            TBTreeNode* tmp = root;
            if(root->leaf) {
                root = nullptr;
            } else {
                root = root->childs[0];
            }
            delete tmp;
        }
        return true;
    } else {
        return false;
    }
}

bool TBTree::Find(TString& key) {
    return (Search(key) == nullptr) ? false : true;
}

unsigned long long TBTree::operator [](TString& key) {
    TBTreeNode* tmp = Search(key);
    int i = tmp->FindKey(key);
    return tmp->dataNode[i];
}

void TBTree::DeleteTree() {
    while(root != nullptr) {
        Delete(root->keys[0]);
    }
}

void TBTree::WriteToFile(ofstream& File) {
    if(root != nullptr) {
        root->WriteToFile(File);
    }
    std::cout << "OK" << '\n';
}


void TBTree::ReadFromFile(ifstream& File) {
    char* key = new char[257];
    unsigned long long value;
    this->DeleteTree();
    while(File.read(key, sizeof(char) * 257)) {
        TString s(key);
        File.read(reinterpret_cast<char*>(&value), sizeof(unsigned long long));
        Insert(s, value);
    }
    delete[] key;
    std::cout << "OK" << '\n';
}
