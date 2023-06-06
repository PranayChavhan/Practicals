#include<iostream>
using namespace std;


class BinarySearchTree{
private:

    struct Node{
        int data;
        Node* left;
        Node* right;
    };

    Node* root;

    Node* insertNode(Node* root, int value){

        if(root == NULL){
            Node* newNode = new Node;
            newNode->data = value;
            newNode->left = NULL;
            newNode->right = NULL;
            return newNode;
        }

        if(value < root->data){
            root->left = insertNode(root->left, value);
        }
        else{
            root->right = insertNode(root->right, value);
        }
        return root;
    }

    int findMaxDepth(Node* root){
        if(root == NULL){
            return 0;
        }
        int leftDepth = findMaxDepth(root->left);
        int rightDepth = findMaxDepth(root->right);
        return max(leftDepth, rightDepth) + 1;
    }

    int findMinValue(Node* root){
        it(root == NULL){
            return 0;
        }
        if(root->left == NULL){
            return root->data;
        }
        return findMinValue(root->left);
    }

    int findMaxValue(Node* root){
        if(root == NULL){
            return 0;
        }
        if(root->right == NULL){
            return root->data;
        }
        return findMaxValue(root->right);
    }

    void swapLeftRight(Node* root){
        if(root == NULL){
            return;
        }

        swapLeftRight(root->left);
        swapLeftRight(root->right);

        Node* temp = root->left;
        root->left = root->right;
        root->right = temp;
    }

    bool searchElement(Node* root, int value){
        if(root == NULL){
            return false;
        }

        if(root->data == value){
            return true;
        }

        if(value < root->data){
            return searchElement(root->left, value);
        }
        else{
            return searchElement(root->right, value);
        }
    }

    Node* findMinNode(Node* root){
        while(root->left != NULL){
            root = root->left;
        }
        return root;
    }

    Node* deleteNode(Node* root, int value){
        if(root == NULL){
            return NULL:
        }

        if(value < root->data){
            root->left = deleteNode(root->left, value);
        }else if(value > root->right){
            root->right = deleteNode(root->right, value);
        }else{
            if(root->left == NULL && root->right == NULL){
                delete root;
                root = NULL;
            }
            else if(root->left == NULL){
                Node* temp = root;
                root = root->right;
                delete temp;
            }
            else if(root->right == NULL){
                Node* temp = root;
                root = root->left;
                delete temp;
            }
            else{
                Node* temp = findMinNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }
    }



public:
    BinarySearchTree(){
        root = NULL;
    }

    void insert(int value){
        root = insertNode(root, value);
    }

    int getMaxDepth(){
        return findMaxDepth(root);
    }
};


int main(){
    BinarySearchTree tree;
     int value;
cout << "Enter the value to insert: ";
cin >> value;

int maxDepth = tree.getMaxDepth();

cout << "The maximum depth of the tree is " << maxDepth << endl;

    return 0;
}