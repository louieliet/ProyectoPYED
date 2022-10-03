#include <iostream>
using namespace std;

typedef struct NodeStruct* Node;

struct NodeStruct{
    int valor;
    struct NodeStruct* left;
    struct NodeStruct* right;
};

void Insert(int nValor, Node &raiz){
    if(raiz == NULL){
        Node newnode = new (struct NodeStruct);
        newnode->valor = nValor;
        newnode->left = NULL;
        newnode->right = NULL;
        raiz = newnode;
    }
    else{
        if(nValor < raiz->valor){
            Insert(nValor,raiz->left);
        }
        else if(nValor > raiz->valor){
            Insert(nValor, raiz->right);
        }
        else{
            cout << "Num repetido" << endl;
        }
    }
}

void Preorden(Node raiz){
    if(raiz != NULL){
        cout << raiz->valor << ", ";
        Preorden(raiz->left);
        Preorden(raiz->right);
    }
}

int main(){
    Node Arbol = NULL;
    Insert(1,Arbol);
    Insert(0,Arbol);
    Insert(10, Arbol);
    Insert(4, Arbol);
    Insert(5, Arbol);
    Preorden(Arbol);
}