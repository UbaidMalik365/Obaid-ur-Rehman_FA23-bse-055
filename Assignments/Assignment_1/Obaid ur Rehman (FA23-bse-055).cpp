#include <iostream>
#include <string>
using namespace std;

struct Task {
    int id;
    string description;
    int priority;
    Task* next;
};

class TaskManager {
private:
    Task* head;

public:
    TaskManager() { head = nullptr; }

    void addTask(int id, string desc, int priority) {
        Task* newTask = new Task{id, desc, priority, nullptr};
        if (!head || head->priority < priority) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* temp = head;
            while (temp->next && temp->next->priority >= priority)
                temp = temp->next;
            newTask->next = temp->next;
            temp->next = newTask;
        }
        cout << "Task added successfully!\n";
    }

    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks to remove.\n";
            return;
        }
        Task* temp = head;
        head = head->next;
        cout << "Removed task with ID: " << temp->id << "\n";
        delete temp;
    }

    void removeTaskByID(int id) {
        if (!head) {
            cout << "No tasks to remove.\n";
            return;
        }
        if (head->id == id) {
            removeHighestPriorityTask();
            return;
        }
        Task* temp = head;
        while (temp->next && temp->next->id != id)
            temp = temp->next;
        if (!temp->next) {
            cout << "Task ID not found.\n";
            return;
        }
        Task* toDelete = temp->next;
        temp->next = temp->next->next;
        cout << "Removed task with ID: " << toDelete->id << "\n";
        delete toDelete;
    }

    void viewTasks() {
        if (!head) {
            cout << "No tasks available.\n";
            return;
        }
        Task* temp = head;
        while (temp) {
            cout << "ID: " << temp->id << ", Description: " << temp->description << ", Priority: " << temp->priority << "\n";
            temp = temp->next;
        }
    }

    ~TaskManager() {
        while (head)
            removeHighestPriorityTask();
    }
};

int main() {
    TaskManager tm;
    int choice, id, priority;
    string desc;

    do {
        cout << "\nTask Management System\n";
        cout << "1. Add Task\n2. View Tasks\n3. Remove Highest Priority Task\n4. Remove Task by ID\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: "; cin >> id;
                cin.ignore();
                cout << "Enter Description: "; getline(cin, desc);
                cout << "Enter Priority: "; cin >> priority;
                tm.addTask(id, desc, priority);
                break;
            case 2:
                tm.viewTasks();
                break;
            case 3:
                tm.removeHighestPriorityTask();
                break;
            case 4:
                cout << "Enter Task ID to remove: "; cin >> id;
                tm.removeTaskByID(id);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
