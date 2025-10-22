#pragma once
#include "Node.h"

class SparseMatrix {
    private:
        Node* start;
        bool modoPrueba;

        public:
        SparseMatrix();
        void setModoPrueba(bool state);
        void add (int value, int xPos, int yPos);
        int get(int xPos, int yPos);
        void remove(int xPos, int yPos);
        void printStoredValues();
        int density();
        SparseMatrix* multiply(SparseMatrix* second);
        ~SparseMatrix();

};