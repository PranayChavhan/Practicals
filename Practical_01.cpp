#include<iostream>
using namespace std;


class node{
  public:
    int data;
    node* left;
    node* right;

  node(int d){
    this->data = d;
    this->left = NULL;
    this->right = NULL;
  }
};

node* insertBST(node *root, int val){

  if (root == NULL)
  {
    return new node(val);
  }
  
  if(val < root->data){
    root->left = insertBST(root->left, val);
  } else{
    root->right = insertBST(root->right, val);
  }

  return root;
}

void inorder(node *root){
  if (root == NULL)
  {
    return;
  }
  inorder(root->left);
  cout<<root->data<<" ";
  inorder(root->right);
  
}


node* searchInBST(node* root, int key){

  if (root == NULL)
  {
    return NULL;
  }
  

  if (root->data == key)
  {
    return root;
  }

  if (root->data > key)
  {
    return searchInBST(root->left, key);
  }
  return searchInBST(root->right, key);
  
}

node* inorderSucc(node* root){
  node* curr = root;
  while (curr && curr->left != NULL)
  {
    curr = curr->left;
  }
  return curr;
  
}

node* deleteInBST(node* root, int key){

  if(key < root->data){
    root->left = deleteInBST(root->left, key);
  } 
  else if(key > root->data){
    root->right = deleteInBST(root->right, key);
  }
  else{
    if(root->left == NULL){
      node* temp = root->right;
      free(root);
      return temp;
    }
    else if(root->right == NULL) {
      node* temp = root->left;
      free(root);
      return temp;
    }
    node* temp = inorderSucc(root->right);
    root->data = temp->data;
    root->right = deleteInBST(root->right, temp->data);
  }
  return root;
}

void swapInBST(node* data){
  if (data->left != NULL)
  {
    swapInBST(data->left);
  }
  if (data->right != NULL)
  {
    swapInBST(data->right);
  }

  node* temp = data->left;
  data->left = data->right;
  data->right = temp;


  
}

int main(){

  node *root = NULL;

  root = insertBST(root, 5);
  insertBST(root, 1);
  insertBST(root, 4);
  insertBST(root, 3);
  insertBST(root, 8);
  insertBST(root, 12);


  inorder(root);
  cout<<endl;

  // if ((searchInBST(root, 5)) == NULL){
  //   cout<< "Key doesn't exist";
  // } else{
  //   cout<< "key exist";
  // }

  // root = deleteInBST(root, 5);

  // inorder(root);
  // cout<<endl;

  //   if ((searchInBST(root, 5)) == NULL){
  //   cout<< "Key doesn't exist";
  // } else{
  //   cout<< "key exist";
  // }
  

  swapInBST(root);
  
  inorder(root);
  cout<<endl;

  return 0;
}