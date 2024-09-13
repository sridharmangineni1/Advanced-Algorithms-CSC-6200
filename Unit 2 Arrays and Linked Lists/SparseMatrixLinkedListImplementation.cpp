#include <iostream>

struct Node {
    int row;
    int col;
    int value;
    Node* next;

    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    Node* head;

public:
    SparseMatrix() : head(nullptr) {}

    void insert(int row, int col, int value) {
        if (value == 0) return;

        Node* newNode = new Node(row, col, value);

        if (!head || (row < head->row) || (row == head->row && col < head->col)) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && (current->next->row < row ||
            (current->next->row == row && current->next->col < col))) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    void display() {
        Node* current = head;
        std::cout << "Sparse Matrix Representation (Row, Col, Value):" << std::endl;
        while (current) {
            std::cout << "(" << current->row << ", " << current->col
                << ", " << current->value << ")" << std::endl;
            current = current->next;
        }
    }

    ~SparseMatrix() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    int rows, cols, value;

    std::cout << "Enter the number of rows in the matrix: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns in the matrix: ";
    std::cin >> cols;

    SparseMatrix sm;

    std::cout << "Enter the elements of the matrix row by row (input zero for empty values):" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << "Element at position (" << i << ", " << j << "): ";
            std::cin >> value;
            sm.insert(i, j, value);
        }
    }

    sm.display();

    return 0;
}
