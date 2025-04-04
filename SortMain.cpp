#include <bits/stdc++.h>
#include "SortingSystem.h"
using namespace std;
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define arr_in(arr,n) for (ui i = 0; i < (n); i++) cin >> (arr)[i]

int getNumberFromFile(ifstream &inFile, const string &prompt) {
    int number;
    string line;

    while (true) {
        cout << prompt;

        if (!getline(inFile, line)) {
            cout << "No more input in the file or failed to read.\n";
            exit(1);  // Stop the program if we run out of inputs
        }

        stringstream ss(line);
        ss >> number;

        if (ss.fail() || !ss.eof()) {
            cout << "Invalid input, Please enter a valid integer.\n";
        }
        else {
            break;
        }
    }
    return number;
}

int getNumberFromUser(string prompt) {
    int number;
    while (true) {
        cout << prompt;
        cin >> number;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            cout << "Invalid input, Please enter a valid integer.\n";
        } else {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            break;
        }
    }
    return number;
}

int main() {
    while (true) {
        int choice = 0;
        while (choice < 1 || choice > 3)
        choice = getNumberFromUser("choose the type of data:\n1:Integer\n2:Float\n3:String\n");
    
        cout << "Enter the file directory: ";
        string file_name; cin >> file_name;
        cout << endl;
        ifstream inFile(file_name);
        if (!inFile.is_open()) {
            cerr << "Failed to open input file.\n";
            return 1;
        }

        if (choice == 1) {
            SortingSystem<int> s(0, inFile);
            s.showMenu();
        }
        else if (choice == 2) {
            SortingSystem<double> s(1, inFile);
            s.showMenu();
        }
        else {
            SortingSystem<string> s(1, inFile);
            s.showMenu();
        }
        inFile.close();
        int cont = 0;
        while (cont < 1 && cont > 2)
            cin.ignore();
            cont = getNumberFromUser("Another Run?\n1:Yes\n2:No\n");
        if (cont == 2) break;
        else cout << "invalide choice\n";
    }
}
