#pragma once 

class Node {
    public:
        int valor;
        Node* next;

        Node(int valor) : valor(valor), next(nullptr) {}
        ~Node() {}
};