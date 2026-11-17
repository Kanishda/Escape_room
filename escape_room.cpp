// Escape Room Chain - prototype using a Singly Linked List
// Each room is a node. The "next" pointer is the door to the next room.

#include <iostream>
#include <string>
using namespace std;

// 1. The node: one room
struct Node {
    string roomName;
    string clue;
    string answer;
    Node* next;
};

Node* head = NULL;   // points to the first room

// 2. Insertion: add a room at the END of the chain
void insertRoom(string name, string clue, string answer) {
    Node* newRoom = new Node;
    newRoom->roomName = name;
    newRoom->clue = clue;
    newRoom->answer = answer;
    newRoom->next = NULL;

    if (head == NULL) {            // list is empty
        head = newRoom;
        return;
    }
    Node* curr = head;
    while (curr->next != NULL) {   // walk to the last room
        curr = curr->next;
    }
    curr->next = newRoom;          // link it
}

// 3. Display: show all rooms in order
void showRooms() {
    if (head == NULL) {
        cout << "No rooms yet.\n";
        return;
    }
    Node* curr = head;
    int n = 1;
    while (curr != NULL) {
        cout << n << ". " << curr->roomName << "\n";
        curr = curr->next;
        n++;
    }
}

// 4. Deletion: remove a room by name
void deleteRoom(string name) {
    if (head == NULL) {
        cout << "No rooms to delete.\n";
        return;
    }
    // case 1: the room is the first one
    if (head->roomName == name) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Deleted " << name << ".\n";
        return;
    }
    // case 2: find the room BEFORE the one we want to delete
    Node* curr = head;
    while (curr->next != NULL && curr->next->roomName != name) {
        curr = curr->next;
    }
    if (curr->next == NULL) {
        cout << "Room not found.\n";
        return;
    }
    Node* temp = curr->next;
    curr->next = temp->next;       // skip the deleted room
    delete temp;
    cout << "Deleted " << name << ".\n";
}

// 5. Traversal: the game itself
void playGame() {
    if (head == NULL) {
        cout << "Add some rooms first!\n";
        return;
    }
    Node* curr = head;
    while (curr != NULL) {
        cout << "\n=== " << curr->roomName << " ===\n";
        cout << "Clue: " << curr->clue << "\n";

        string guess;
        do {
            cout << "Your answer: ";
            getline(cin, guess);
            if (guess != curr->answer) {
                cout << "Wrong, try again.\n";
            }
        } while (guess != curr->answer);

        cout << "The door opens!\n";
        curr = curr->next;         // move to the next room
    }
    cout << "\nYou escaped! Congratulations!\n";   // curr is NULL
}

int main() {
    // Starter rooms so the game works straight away
    insertRoom("Library", "I have keys but open no locks. What am I?", "keyboard");
    insertRoom("Kitchen", "What has hands but cannot clap?", "clock");
    insertRoom("Vault", "The more you take, the more you leave behind. What am I?", "footsteps");

    int choice;
    do {
        cout << "\n--- ESCAPE ROOM MENU ---\n";
        cout << "1. Play\n2. Add a room\n3. Delete a room\n4. Show rooms\n5. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();              // clear the Enter key

        if (choice == 1) {
            playGame();
        } else if (choice == 2) {
            string n, c, a;
            cout << "Room name: ";  getline(cin, n);
            cout << "Clue: ";       getline(cin, c);
            cout << "Answer: ";     getline(cin, a);
            insertRoom(n, c, a);
        } else if (choice == 3) {
            string n;
            cout << "Room to delete: ";
            getline(cin, n);
            deleteRoom(n);
        } else if (choice == 4) {
            showRooms();
        }
    } while (choice != 5);

    cout << "Goodbye!\n";
    return 0;
}
