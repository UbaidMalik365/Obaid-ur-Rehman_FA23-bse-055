#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Patient {
    string name;
    int emergencyLevel;

    // Higher emergencyLevel gets higher priority
    bool operator<(const Patient& other) const {
        return emergencyLevel < other.emergencyLevel;
    }
};

void displayMenu() {
    cout << "\n Patient Treatment Menu \n";
    cout << "1. Add Patient\n";
    cout << "2. Treat Next Patient\n";
    cout << "3. Show Waiting List\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

void printQueue(priority_queue<Patient> q) {
    cout << "\nCurrent Treatment Queue:\n";
    if (q.empty()) {
        cout << "No patients waiting.\n";
        return;
    }
    while (!q.empty()) {
        Patient p = q.top();
        q.pop();
        cout << "- " << p.name << " (Emergency Level: " << p.emergencyLevel << ")\n";
    }
}

int main() {
    priority_queue<Patient> treatmentQueue;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            Patient p;
            cout << "Enter patient's name: ";
            cin.ignore(); // clear newline from previous input
            getline(cin, p.name);
            cout << "Enter emergency level (1-10, where 10 is most severe): ";
            cin >> p.emergencyLevel;
            treatmentQueue.push(p);
            cout << p.name << " added to the queue.\n";
            break;
        }
        case 2: {
            if (!treatmentQueue.empty()) {
                Patient next = treatmentQueue.top();
                treatmentQueue.pop();
                cout << "Treating patient: " << next.name << " (Emergency Level: " << next.emergencyLevel << ")\n";
            } else {
                cout << "No patients to treat.\n";
            }
            break;
        }
        case 3: {
            printQueue(treatmentQueue);
            break;
        }
        case 4:
            cout << "Exiting application.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);
    return 0;
}
