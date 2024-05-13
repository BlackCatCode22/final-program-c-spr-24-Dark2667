#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Contact {
private:
    string name;
    string phoneNumber;
    string email;

public:
    Contact(string name, string phoneNumber, string email)
    : name(move(name)), phoneNumber(move(phoneNumber)), email(move(email)) {}

    const string& getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    const string& getPhoneNumber() const {
        return phoneNumber;
    }

    void setPhoneNumber(const string& newPhoneNumber) {
        phoneNumber = newPhoneNumber;
    }

    const string& getEmail() const {
        return email;
    }

    void setEmail(const string& newEmail) {
        email = newEmail;
    }

    friend ostream& operator<<(ostream& os, const Contact& contact) {
        os << "Contact{name='" << contact.name << "', phoneNumber='" << contact.phoneNumber << "', email='" << contact.email << "'}";
        return os;
    }
};

// Linear Search Function with Iteration Count
int linearSearch(const vector<Contact>& contacts, const string& target) {
    int iterations = 0;
    for (size_t i = 0; i < contacts.size(); ++i) {
        iterations++;
        if (contacts[i].getName() == target) {
            cout << "Linear search iterations: " << iterations << endl;
            return i;
        }
    }
    cout << "Linear search iterations: " << iterations << endl;
    return -1;
}

// Recursive Binary Search Function with Iteration Count
int recursiveBinarySearch(const vector<Contact>& contacts, const string& target, int left, int right, int& iterations) {
    if (left <= right) {
        int mid = left + (right - left) / 2;
        iterations++;

        if (contacts[mid].getName() == target) {
            cout << "Recursive binary search iterations: " << iterations << endl;
            return mid;
        }

        if (contacts[mid].getName() < target) {
            return recursiveBinarySearch(contacts, target, mid + 1, right, iterations);
        } else {
            return recursiveBinarySearch(contacts, target, left, mid - 1, iterations);
        }
    }

    cout << "Recursive binary search iterations: " << iterations << endl;
    return -1;
}

int binarySearch(const vector<Contact>& contacts, const string& target) {
    int left = 0;
    int right = contacts.size() - 1;
    int iterations = 0;

    return recursiveBinarySearch(contacts, target, left, right, iterations);
}

void performSearch(const vector<Contact>& contacts, const string& target, const string& searchType) {
    auto start = high_resolution_clock::now();

    int result = (searchType == "linear") ? linearSearch(contacts, target) : binarySearch(contacts, target);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    if (result != -1) {
        cout << "Contact found by " << searchType << " search at index: " << result << endl;
    } else {
        cout << "Contact not found by " << searchType << " search." << endl;
    }

    cout << "Time taken by " << searchType << " search: " << duration.count() << " microseconds" << endl;
}

int main() {
    vector<Contact> contacts;
    contacts.emplace_back("Alice", "123-456-7890", "alice@email.com");
    contacts.emplace_back("Bob", "987-654-3210", "bob@email.com");
    contacts.emplace_back("Charlie", "456-789-1234", "charlie@email.com");

    string targetName;
    cout << "Enter the name to search: ";
    getline(cin, targetName);

    if (targetName.empty()) {
        cout << "Error: Empty input. Please enter a valid name." << endl;
        return 1;
    }

    cout << "\nTarget name is: " + targetName + "\n";

    // Perform Linear Search
    cout << "\nPerforming Linear Search:\n";
    performSearch(contacts, targetName, "linear");

    // Perform Binary Search
    cout << "\nPerforming Binary Search:\n";
    performSearch(contacts, targetName, "binary");

    return 0;
}
