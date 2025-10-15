#include "SparseMatrix.h"

SparseMatrix::SparseMatrix() {
    start = nullptr;
}

void SparseMatrix::add(int value, int xPos, int yPos) {
    if(xPos<0 || yPos<0) { return; }

    Node* actual = start;
    Node* anterior = nullptr;

    while(actual != nullptr){
        if(actual->xPos == xPos && actual->yPos == yPos){
            if (value == 0)
            {
                remove(xPos, yPos);
            }
            else
            {
                actual->valor = value;
            }
            return;
            
        }
        if(actual->xPos > xPos || (actual->xPos == xPos && actual->yPos > yPos)){
            break;
        }

        anterior = actual;
        actual = actual->next;  
    }
    if (value == 0)
    {
        return;
    }

    Node* nuevo = new Node(value, xPos, yPos);
    if (anterior == nullptr)
    {
        nuevo->next = start;
        start = nuevo;
    }
    else
    {
        anterior->next = nuevo;
        nuevo->next = actual;
    }
}

int SparseMatrix::get(int xPos, int yPos) {
    Node* actual = start;

    while(actual != nullptr){
        if(actual->xPos == xPos && actual->yPos == yPos){
            return actual->valor;
        }
        if(actual->xPos > xPos || (actual->xPos == xPos && actual->yPos > yPos)){
            break;
        }
        actual = actual->next;  
    }
    return 0;
    
}

void SparseMatrix::remove(int xPos, int yPos) {
   
}

void SparseMatrix::printStoredValues() {
    
}

int SparseMatrix::density() {
   
}

SparseMatrix* SparseMatrix::multiply(SparseMatrix* second) {
    
}

SparseMatrix::~SparseMatrix() {
   
}
