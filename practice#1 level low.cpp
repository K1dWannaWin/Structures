
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>


struct Person {
    std::string lastName;
    char gender;
    double height;
    std::string sport;
    time_t yearOfBirth;
};

struct Node {
    Person data;
    Node* next;
};

Node* head = nullptr;


void insertAtBegin(Person data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}

void removeFirst() {
    if (head == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
}

void displayList() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << "Last Name: " << current->data.lastName << std::endl;
        std::cout << "Gender: " << current->data.gender << std::endl;
        std::cout << "Height: " << current->data.height << std::endl;
        std::cout << "Sport: " << current->data.sport << std::endl;
        std::cout << "Year of Birth: " << current->data.yearOfBirth << std::endl;
        std::cout << "---" << std::endl;
        current = current->next;
    }
}

Node* search(Node* current) {

    time_t now;
    time(&now);
    tm* curyear = localtime(&now);
    if (current == nullptr) {
        std::cout << "No person found"<< std::endl;
    }
    while (current != nullptr) {
        if (curyear->tm_year + 1900 - current->data.yearOfBirth < 18 && curyear->tm_year + 1900 - current->data.yearOfBirth > 13) {
            std::cout << "Last Name: " << current->data.lastName << std::endl;
            std::cout << "Gender: " << current->data.gender << std::endl;
            std::cout << "Height: " << current->data.height << std::endl;
            std::cout << "Sport: " << current->data.sport << std::endl;
            std::cout << "Year of Birth: " << current->data.yearOfBirth << std::endl;
            std::cout << "---" << std::endl;
            current = current->next;
        }
        else {
            current = current->next;
        }
    }
    return nullptr;
}

Node* searchForSpec() {
    Node* current = head;
    Node* maxHeight=nullptr;
    double maxh=0;
    while (current != nullptr) {
        if (current->data.gender == 'M'&& current->data.sport=="swimming") {
            if (current->data.height > maxh) { 
                maxh = current->data.height;
                maxHeight = current;
            }
        
           
        }
        current = current->next;
    }
    return maxHeight;
}

void writeToBinaryFile() {
    std::ofstream file("people.bin", std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        file.write((char*)&current->data, sizeof(Person));
        current = current->next;
    }
    file.close();
}

void readFromBinaryFile() {
    std::ifstream file("people.bin", std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return;
    }
    head = new Node();
    if (head == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
    }
  
    while (file.read((char*)&head->data, sizeof(Person))) {
        Node* newNode = new Node();
        newNode->data = head->data;
        newNode->next = head;
        head = newNode;
        
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    file.close();

}
  

int main() {
    int choice;
    readFromBinaryFile();
    
    
    do {
        std::cout << "1. Add a person to the list" << std::endl;
        std::cout << "2. Remove the first person from the list" << std::endl;
        std::cout << "3. Display the list" << std::endl;
        std::cout << "4. Search for a person between 14-17 y.o." << std::endl;
        std::cout << "5. Exit(write to file)" << std::endl;
        std::cout << "6 Search for specific" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
        case 1: {
            Person data;
            std::cout << "Enter the last name: ";
            std::cin >> data.lastName;
            std::cout << "Enter the gender (M/F): ";
            std::cin >> data.gender;
            std::cout << "Enter the height: ";
            std::cin >> data.height;
            std::cout << "Enter the sport: ";
            std::cin >> data.sport;
            std::cout << "Enter the year of birth: ";
            std::cin >> data.yearOfBirth;
            insertAtBegin(data);
            break;
        }
        case 2: {
            removeFirst();
            break;
        }
        case 3: {
            displayList();
            break;
        }
        case 4: {
            Node* result;
            Node* current = head;
            result = search(current);
            break;
        }

        case 5: {
            writeToBinaryFile();
            break;
        }
        case 6: {
            Node* result;
            result=searchForSpec();
            if (result == nullptr) {
                std::cout << "Person not found." << std::endl;
                break;
            }
            else {
                std::cout << "Last Name: " << result->data.lastName << std::endl;
                std::cout << "Gender: " << result->data.gender << std::endl;
                std::cout << "Height: " << result->data.height << std::endl;
                std::cout << "Sport: " << result->data.sport << std::endl;
                std::cout << "Year of Birth: " << result->data.yearOfBirth << std::endl;
                std::cout << "---" << std::endl;
            }
            break;
        }
        default: {
            std::cout << "Invalid choice." << std::endl;
            break;
        }
        }
    } while (choice != 5);
    
    return 0;
}
