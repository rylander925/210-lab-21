/*
COMSC-210 | Lab 21 | Rylan Der
IDE Used: Visual Studio Code
*/

#include <iostream>
#include <string>
#include <fstream>
#include <istream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class Goat {
    public:
        /**
         * Initializes a goat with random age, color, and name
         */
        Goat() {

        }

        /**
         * Initializes goat with given age, name, and color
         */
        Goat(int age, string name, string color): age(age), color(color), name(name) { };

    private:
        static const int NUM_COLORS = 15;
        static const int NUM_NAMES = 15;
        static const int MIN_AGE = 1;
        static const int MAX_AGE = 20;
        static const string names[NUM_NAMES];
        static const string colors[NUM_COLORS];
        int age;
        string name;
        string color;
};


void ValidateFile(fstream *input, string filename);

const string Goat::names[NUM_NAMES] = {"Billy", "Nanny", "Gruff", "Daisy", "Clover", "Pepper", "Milo", "Hazel", "Willow", "Buck", "Luna", "Maple", "Oreo", "Mocha", "Finn"};
const string Goat::colors[NUM_COLORS] = {"Chestnut", "Mahogany", "Cinnamon", "Fawn", "Slate", "Ivory", "Onyx", "Copper", "Ash", "Ebony", "Silver", "Cream", "Tawny", "Umber", "Pearl"};

// Driver program
int main() {
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}

/**
 * Attempts to open a file, and throws an error if open operation failed
 * @param input File stream to open a file from
 * @param filename Name of the file to open
 */
void ValidateFile(ifstream* input, string filename) {
    input->open(filename);
    if (!input->is_open()) {
        cout << "ERROR: Could not open file \"" << filename << "\"" << endl;
        throw ios_base::failure("Invalid file name");
    }
}