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

class Goat {
    public:
        /**
         * Initializes a goat with random age, color, and name
         */
        Goat() {
            age = MIN_AGE + (rand() % (MAX_AGE - MIN_AGE + 1)); //Initialize with random age between MIN_AGE and MAX_AGE
            name = names[rand() % NUM_NAMES];                   //Initialize name/color by retrieving a random element of their respective arrays
            color = colors[rand() % NUM_COLORS];
        }

        /**
         * Initializes goat with given age, name, and color
         */
        Goat(int age, string name, string color): age(age), color(color), name(name) { }

        /**
         * Output goat info formatted as [name] ([color], [age])
         * @note Does not output newlines
         */
        void Print() const{
            cout << name << " " << "(" << color << ", " << age << ")";
        }

        //Standard getters and setters
        void setAge(int age)        { this->age = age; }
        void setName(string name)   { this->name = name; }
        void setColor(string color) { this->color = color; }
        int getAge() const          { return age; }
        string getName() const      { return name; }
        string getColor() const     { return color; } 

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

const string Goat::names[NUM_NAMES] = {"Billy", "Nanny", "Gruff", "Daisy", "Clover", "Pepper", "Milo", "Hazel", "Willow", "Buck", "Luna", "Maple", "Oreo", "Mocha", "Finn"};
const string Goat::colors[NUM_COLORS] = {"Chestnut", "Mahogany", "Cinnamon", "Fawn", "Slate", "Ivory", "Onyx", "Copper", "Ash", "Ebony", "Silver", "Cream", "Tawny", "Umber", "Pearl"};

class DoublyLinkedList {
private:
    struct Node {
        Goat goat;
        Node* prev;
        Node* next;
        Node(Goat goat, Node* p = nullptr, Node* n = nullptr) {
            this->goat = goat; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    /**
     * Appends a new node to end of linked list
     * @param goat Goat to append
     */
    void push_back(Goat goat) {
        Node* newNode = new Node(goat);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    /**
     * Prepends a new node to front of linked list
     * @param goat Goat to prepend
     */
    void push_front(Goat goat) {
        Node* newNode = new Node(goat);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    /**
     * Inserts a goat after a specified position in the linked list
     * @param goat Goat to insert
     * @param position Position to insert goat after; must be greater than 0
     */
    void insert_after(Goat goat, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(goat);
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

    /**
     * Deletes the first node with matching goat name from linked list
     * @param goat Goat whose name should be deleted 
     */
    void delete_node(Goat goat) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->goat.getName() != goat.getName()) //search by goat name
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

    /**
     * Outputs linked list data in order, calling Goat::Print() for each object
     */
    void print() {
        Node* current = head;
        if (!current) { cout << "List is empty " << endl; return; }
        while (current) {
            //Output goat using Goat::Print()
            cout << '\t';
            current->goat.Print();
            cout << endl;

            current = current->next;
        }
    }

    /**
     * Outputs linked list data in reverse order, calling Goat::Print() for each object
     */
    void print_reverse() {
        Node* current = tail;
        if (!current) { cout << "List is empty " << endl; return; }
        while (current) {
            //Output goat using Goat::Print()
            cout << '\t';
            current->goat.Print();
            cout << endl;

            current = current->prev;
        }
    }

    //Deletes linked list nodes
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    //Seed random number for goat ages, names, and colors
    srand(time(0)); 

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    //Populate linked list with random goat information using Goat class default constructor
    for (int i = 0; i < size; ++i)
        list.push_back(Goat());

    //Output list contents
    cout << "List forward: " << endl;
    list.print();
    cout << "List backward: " << endl;
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}