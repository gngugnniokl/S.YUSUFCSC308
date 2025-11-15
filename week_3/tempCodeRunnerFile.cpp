#include <iostream>
#include <string>
#include <map>
#include <limits>

using namespace std;

struct Parcel {
    string id;
    string sender;
    string recipient;
    string address;
    double weight;
    int priority; // 1: high, 2: medium, 3: low
};

enum ActionType { ADD, REMOVE, UPDATE, DISPATCH };

struct Action {
    ActionType type;
    Parcel parcel;
    Parcel oldParcel; // Used only for UPDATE
};

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T d) : data(d), next(nullptr) {}
};

class Queue {
private:
    Node<Parcel>* front;
    Node<Parcel>* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}
    ~Queue() {
        while (front) {
            Node<Parcel>* temp = front;
            front = front->next;
            delete temp;
        }
    }
    void enqueue(const Parcel& p) {
        Node<Parcel>* newNode = new Node<Parcel>(p);
        if (rear) rear->next = newNode;
        else front = newNode;
        rear = newNode;
    }
    void enqueueFront(const Parcel& p) {
        Node<Parcel>* newNode = new Node<Parcel>(p);
        newNode->next = front;
        front = newNode;
        if (!rear) rear = front;
    }
    Parcel dequeue() {
        if (!front) {
            cout << "Queue empty!" << endl;
            Parcel empty;
            return empty;
        }
        Parcel p = front->data;
        Node<Parcel>* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return p;
    }
    bool isEmpty() const { return front == nullptr; }
    Parcel* find(const string& id) {
        Node<Parcel>* curr = front;
        while (curr) {
            if (curr->data.id == id) return &curr->data;
            curr = curr->next;
        }
        return nullptr;
    }
    bool remove(const string& id) {
        Node<Parcel>* curr = front;
        Node<Parcel>* prev = nullptr;
        while (curr) {
            if (curr->data.id == id) {
                if (prev) prev->next = curr->next;
                else front = curr->next;
                if (curr == rear) rear = prev ? prev : nullptr;
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }
    void getCountAndSum(int& count, double& sumWeight) const {
        count = 0;
        sumWeight = 0.0;
        Node<Parcel>* curr = front;
        while (curr) {
            count++;
            sumWeight += curr->data.weight;
            curr = curr->next;
        }
    }
};

class LinkedList {
private:
    Node<Parcel>* head;
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList() {
        while (head) {
            Node<Parcel>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void insert(const Parcel& p) {
        Node<Parcel>* newNode = new Node<Parcel>(p);
        newNode->next = head;
        head = newNode;
    }
    bool remove(const string& id) {
        Node<Parcel>* curr = head;
        Node<Parcel>* prev = nullptr;
        while (curr) {
            if (curr->data.id == id) {
                if (prev) prev->next = curr->next;
                else head = curr->next;
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }
    Parcel* find(const string& id) {
        Node<Parcel>* curr = head;
        while (curr) {
            if (curr->data.id == id) return &curr->data;
            curr = curr->next;
        }
        return nullptr;
    }
    int count() const {
        int c = 0;
        Node<Parcel>* curr = head;
        while (curr) {
            c++;
            curr = curr->next;
        }
        return c;
    }
    double sumWeight() const {
        double s = 0.0;
        Node<Parcel>* curr = head;
        while (curr) {
            s += curr->data.weight;
            curr = curr->next;
        }
        return s;
    }
    void printHistory() const {
        Node<Parcel>* curr = head;
        cout << "Delivery History:" << endl;
        while (curr) {
            cout << "ID: " << curr->data.id << ", Sender: " << curr->data.sender
                 << ", Recipient: " << curr->data.recipient << ", Address: " << curr->data.address
                 << ", Weight: " << curr->data.weight << ", Priority: " << curr->data.priority << endl;
            curr = curr->next;
        }
    }
    void printRouteSummary() const {
        map<string, int> routeCount;
        Node<Parcel>* curr = head;
        while (curr) {
            routeCount[curr->data.address]++;
            curr = curr->next;
        }
        cout << "Route Summary:" << endl;
        for (const auto& pair : routeCount) {
            cout << pair.first << ": " << pair.second << " parcels" << endl;
        }
    }
};

class Stack {
private:
    Node<Action>* top;
public:
    Stack() : top(nullptr) {}
    ~Stack() {
        clear();
    }
    void push(const Action& a) {
        Node<Action>* newNode = new Node<Action>(a);
        newNode->next = top;
        top = newNode;
    }
    Action pop() {
        if (!top) {
            cout << "Stack empty!" << endl;
            Action empty;
            return empty;
        }
        Action a = top->data;
        Node<Action>* temp = top;
        top = top->next;
        delete temp;
        return a;
    }
    bool isEmpty() const { return top == nullptr; }
    void clear() {
        while (top) {
            Node<Action>* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

// Global variables
Queue highQ, medQ, lowQ;
LinkedList delivered;
Stack undoStack, redoStack;

// Helper functions
Queue* getQueue(int priority) {
    if (priority == 1) return &highQ;
    if (priority == 2) return &medQ;
    if (priority == 3) return &lowQ;
    return nullptr;
}

Parcel* findParcel(const string& id) {
    Parcel* p = highQ.find(id);
    if (p) return p;
    p = medQ.find(id);
    if (p) return p;
    p = lowQ.find(id);
    if (p) return p;
    return nullptr;
}

bool removeParcel(const string& id) {
    if (highQ.remove(id)) return true;
    if (medQ.remove(id)) return true;
    if (lowQ.remove(id)) return true;
    return false;
}

void registerParcel() {
    Parcel newP;
    cout << "Enter Parcel ID: ";
    cin >> newP.id;
    if (findParcel(newP.id)) {
        cout << "Duplicate ID!" << endl;
        return;
    }
    cout << "Enter Sender: ";
    cin >> newP.sender;
    cout << "Enter Recipient: ";
    cin >> newP.recipient;
    cout << "Enter Weight: ";
    cin >> newP.weight;
    cout << "Enter Priority (1-high, 2-med, 3-low): ";
    cin >> newP.priority;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
    cout << "Enter Address: ";
    getline(cin, newP.address);

    Queue* q = getQueue(newP.priority);
    if (!q) {
        cout << "Invalid priority!" << endl;
        return;
    }
    q->enqueue(newP);
    Action act;
    act.type = ADD;
    act.parcel = newP;
    undoStack.push(act);
    redoStack.clear();
    cout << "Parcel registered." << endl;
}

void updateParcel() {
    string id;
    cout << "Enter Parcel ID to update: ";
    cin >> id;
    Parcel* p = findParcel(id);
    if (!p) {
        cout << "Parcel not found!" << endl;
        return;
    }
    Parcel oldP = *p;
    Parcel newP = oldP; // Start with current

    cout << "Enter new Sender (or press enter to keep): ";
    cin.ignore();
    string input;
    getline(cin, input);
    if (!input.empty()) newP.sender = input;

    cout << "Enter new Recipient (or press enter to keep): ";
    getline(cin, input);
    if (!input.empty()) newP.recipient = input;

    cout << "Enter new Address (or press enter to keep): ";
    getline(cin, input);
    if (!input.empty()) newP.address = input;

    cout << "Enter new Weight (or -1 to keep): ";
    double w;
    cin >> w;
    if (w != -1) newP.weight = w;

    cout << "Enter new Priority (or -1 to keep): ";
    int pri;
    cin >> pri;
    if (pri != -1) {
        if (pri < 1 || pri > 3) {
            cout << "Invalid priority!" << endl;
            return;
        }
        // If priority changes, need to remove from old queue and add to new
        if (pri != oldP.priority) {
            removeParcel(id);
            newP.priority = pri;
            Queue* newQ = getQueue(pri);
            newQ->enqueue(newP);
            *p = newP; // Update, but since removed and added, p invalid, but ok since new in queue
        } else {
            newP.priority = oldP.priority;
            *p = newP;
        }
    } else {
        newP.priority = oldP.priority;
        *p = newP;
    }

    Action act;
    act.type = UPDATE;
    act.parcel = newP; // new state
    act.oldParcel = oldP; // old state
    undoStack.push(act);
    redoStack.clear();
    cout << "Parcel updated." << endl;
}

void cancelParcel() {
    string id;
    cout << "Enter Parcel ID to cancel: ";
    cin >> id;
    Parcel* p = findParcel(id);
    if (!p) {
        cout << "Parcel not found!" << endl;
        return;
    }
    Parcel copy = *p;
    removeParcel(id);
    Action act;
    act.type = REMOVE;
    act.parcel = copy;
    undoStack.push(act);
    redoStack.clear();
    cout << "Parcel canceled." << endl;
}

void dispatchParcel() {
    Queue* q = &highQ;
    if (q->isEmpty()) q = &medQ;
    if (q->isEmpty()) q = &lowQ;
    if (q->isEmpty()) {
        cout << "No parcels to dispatch!" << endl;
        return;
    }
    Parcel p = q->dequeue();
    delivered.insert(p);
    Action act;
    act.type = DISPATCH;
    act.parcel = p;
    undoStack.push(act);
    redoStack.clear();
    cout << "Parcel dispatched: " << p.id << endl;
}

void undoAction() {
    if (undoStack.isEmpty()) {
        cout << "No actions to undo!" << endl;
        return;
    }
    Action act = undoStack.pop();
    if (act.type == ADD) {
        removeParcel(act.parcel.id);
    } else if (act.type == REMOVE) {
        Queue* q = getQueue(act.parcel.priority);
        q->enqueue(act.parcel);
    } else if (act.type == UPDATE) {
        Parcel* p = findParcel(act.parcel.id);
        if (p) *p = act.oldParcel;
    } else if (act.type == DISPATCH) {
        delivered.remove(act.parcel.id);
        Queue* q = getQueue(act.parcel.priority);
        q->enqueueFront(act.parcel);
    }
    redoStack.push(act);
    cout << "Action undone." << endl;
}

void redoAction() {
    if (redoStack.isEmpty()) {
        cout << "No actions to redo!" << endl;
        return;
    }
    Action act = redoStack.pop();
    if (act.type == ADD) {
        Queue* q = getQueue(act.parcel.priority);
        q->enqueue(act.parcel);
    } else if (act.type == REMOVE) {
        removeParcel(act.parcel.id);
    } else if (act.type == UPDATE) {
        Parcel* p = findParcel(act.oldParcel.id);
        if (p) *p = act.parcel;
    } else if (act.type == DISPATCH) {
        Queue* q = getQueue(act.parcel.priority);
        Parcel p = q->dequeue();
        delivered.insert(p);
    }
    undoStack.push(act);
    cout << "Action redone." << endl;
}

void generateReports() {
    int deliveredCount = delivered.count();
    cout << "Total parcels delivered: " << deliveredCount << endl;

    int pendingHigh, pendingMed, pendingLow;
    double sumHigh, sumMed, sumLow;
    highQ.getCountAndSum(pendingHigh, sumHigh);
    medQ.getCountAndSum(pendingMed, sumMed);
    lowQ.getCountAndSum(pendingLow, sumLow);

    int totalPending = pendingHigh + pendingMed + pendingLow;
    int totalRegistered = totalPending + deliveredCount;
    cout << "Total parcels registered: " << totalRegistered << endl;

    cout << "Parcels pending by priority:" << endl;
    cout << "High: " << pendingHigh << endl;
    cout << "Medium: " << pendingMed << endl;
    cout << "Low: " << pendingLow << endl;

    double totalSumWeight = sumHigh + sumMed + sumLow + delivered.sumWeight();
    double avgWeight = (totalRegistered > 0) ? totalSumWeight / totalRegistered : 0.0;
    cout << "Average parcel weight: " << avgWeight << endl;

    delivered.printHistory();
    delivered.printRouteSummary();
}

int main() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Register Parcel\n";
        cout << "2. Update Parcel\n";
        cout << "3. Cancel Parcel\n";
        cout << "4. Dispatch Next Parcel\n";
        cout << "5. Undo\n";
        cout << "6. Redo\n";
        cout << "7. Generate Reports\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerParcel(); break;
            case 2: updateParcel(); break;
            case 3: cancelParcel(); break;
            case 4: dispatchParcel(); break;
            case 5: undoAction(); break;
            case 6: redoAction(); break;
            case 7: generateReports(); break;
            case 8: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 8);

    return 0;
}

// This code was developed with the assistance of Grok AI, which provided guidance on the overall structure, logic for data structures (stacks, queues, linked lists), and implementation of undo/redo functionality. Specific code segments for menu handling, reports, and action processing were refined using AI suggestions, but all code was reviewed and adapted manually.