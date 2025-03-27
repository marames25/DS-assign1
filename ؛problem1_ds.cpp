#include <iostream>
#include <algorithm>

using namespace std;

class guest {
private:
    string name;
    string contact;
    string iftar_date;

public:
    guest() {} // Constructor for dynamic allocation

    guest(string name, string contact, string iftar_date) {
        this->name = name;
        this->contact = contact;
        this->iftar_date = iftar_date;
    }

    string getName() const {
        return name;
    }
    string getContact() const {
        return contact;
    }
    string getIftarDate() const {
        return iftar_date;
    }

    void display_guest() const {
        cout << "Guest: " << name << ", Contact: " << contact
             << ", Iftar Date: " << iftar_date << endl;
    }

    void update_invitation(string new_date) {
        iftar_date = new_date;
    }
};

class IftarManager {
private:
    guest* guest_list;
    int size;
    int no_guests;

public:
    int get_no_guests() {
        return no_guests;
    }

    IftarManager(int max_size) {
        size = max_size;
        no_guests = 0;
        guest_list = new guest[size];
    }

    ~IftarManager() {
        delete[] guest_list;
    }

    void add_guest(const guest& g) {
        if (no_guests >= size) {
            cout << "Guest list is full\n";
            return;
        }
        guest_list[no_guests++] = g;
        cout << "Guest added successfully\n";
    }

    void update_guest_invitation(string name, string new_date) {
        bool found = false;
        for (int i = 0; i < no_guests; i++) {
            if (guest_list[i].getName() == name) {
                guest_list[i].update_invitation(new_date);
                cout << "Invitation for " << name << " updated to " << new_date << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Guest with name " << name << " not found\n";
        }
    }

    void remove_guest(string name) {
        bool found = false;
        for (int i = 0; i < no_guests; i++) {
            if (guest_list[i].getName() == name) {
                found = true;
                for (int j = i; j < no_guests - 1; j++) {
                    guest_list[j] = guest_list[j + 1];
                }
                no_guests--;
                cout << "Guest " << name << " removed successfully\n";
                return;
            }
        }
        if (!found) {
            cout << "Guest with name " << name << " not found\n";
        }
    }

    void display_all_guests() const {
        if (no_guests == 0) {
            cout << "No guests available\n";
            return;
        }
        for (int i = 0; i < no_guests; i++) {
            guest_list[i].display_guest();
        }
    }

    void send_reminders(string date) {
        bool reminderSent = false;
        for (int i = 0; i < no_guests; i++) {
            if (guest_list[i].getIftarDate() == date) {
                cout << "Reminder sent to " << guest_list[i].getContact()
                     << ": Your Iftar invitation is on " << date << "!\n";
                reminderSent = true;
            }
        }
        if (!reminderSent) {
            cout << "No guests found for Iftar on " << date << endl;
        }
    }

    void sort_guest_list() {
        cout << "Sorting Guest list by Iftar date...\n";
        sort(guest_list, guest_list + no_guests, [](const guest& a, const guest& b) {
            return a.getIftarDate() < b.getIftarDate();
        });
        cout << "Guest list sorted successfully!\n";
    }
};

int main() {
    int MaxGuests;
    cout << "Enter maximum number of guests: ";
    cin >> MaxGuests;
    cin.ignore();

    IftarManager manager(MaxGuests);

    while (true) {
        cout << "\n====== Iftar Manager ======\n";
        cout << "1. Add Guest\n";
        cout << "2. Remove Guest\n";
        cout << "3. Show Guest List\n";
        cout << "4. Send Reminder\n";
        cout << "5. Update Guest Invitation\n";
        cout << "6. Sort Guest List by Date\n";
        cout << "7. Exit\n";
        cout << "Select an option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                if (manager.get_no_guests() >= MaxGuests) {
                    cout << "Guest list is full!\n";
                    break;
                }
                string name, contact, iftar_date;
                cout << "Enter guest name: ";
                getline(cin, name);
                cout << "Enter contact number: ";
                getline(cin, contact);
                cout << "Enter Iftar date (YYYY-MM-DD): ";
                getline(cin, iftar_date);

                manager.add_guest(guest(name, contact, iftar_date));
                break;
            }
            case 2: {
                string name;
                cout << "Enter guest name to remove: ";
                getline(cin, name);
                manager.remove_guest(name);
                break;
            }
            case 3:
                manager.display_all_guests();
                break;
            case 4: {
                string date;
                cout << "Enter date (YYYY-MM-DD) to send reminders: ";
                getline(cin, date);
                manager.send_reminders(date);
                break;
            }
            case 5: {
                string name, new_date;
                cout << "Enter guest name to update invitation: ";
                getline(cin, name);
                cout << "Enter new Iftar date (YYYY-MM-DD): ";
                getline(cin, new_date);
                manager.update_guest_invitation(name, new_date);
                break;
            }
            case 6:
                manager.sort_guest_list();
                break;
            case 7:
                cout << "Exiting program\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again\n";
        }
    }
}
