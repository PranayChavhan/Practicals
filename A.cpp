#include<iostream>
#include<string>
using namespace std;


class Node{
public:
    string keyword;
    string meaning;
    int height;
    Node* left;
    Node* right;

    Node(string key, string val){
        keyword = key;
        meaning = val;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class Dictionary{
private:

    Node* root;

    int getHeight(Node* node){
        if(node == nullptr){
            return 0;
        }
        return node->height;

    }

    int getBalanceFactor(Node* node){
        if(node == nullptr){
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node* node){
        if(node == nullptr){
            return 0;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    Node* leftRotation(Node* x){
        Node* y = x->right;
        Node* T2 = y->left;

        y->left=x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* rightRotation(Node* y){
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(x)
        updateHeight(y)

        return x;
    }

    Node* balanceTree(Node* node, string key){
        updateHeight(node);

        int balanceFactor = getBalanceFactor(node);

        if(balanceFactor > 1 && key < node->left->keyword){
            return rightRotation(node);
        }
    }

}

int main(){

    return 0;
}