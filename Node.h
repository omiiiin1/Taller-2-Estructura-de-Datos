#pragma once 

class Node {
    public:
        int valor;
        int xPos;
        int yPos;
        Node* next;

        Node(int valor, int xPos, int yPos) : valor(valor), xPos(xPos), yPos(yPos), next(nullptr) {}
        ~Node() {}
};