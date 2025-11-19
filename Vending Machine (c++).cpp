#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>
using namespace std;

struct Item {
    int id;
    string name;
    int price; 
    int qty;
};

class VendingMachine {
private:
    vector<Item> items;
    const string itemFile = "items.txt";
    const string logFile = "log.txt";

public:
    VendingMachine() {
        loadItems();
        if (items.empty()) seedDefault();
    }

    void loadItems() {
        items.clear();
        ifstream f(itemFile);
        if (!f.is_open()) return;

        string line;
        while (getline(f, line)) {
            stringstream ss(line);
            Item it;
            ss >> it.id;
            ss.ignore();
            getline(ss, it.name, '|');
            ss >> it.price >> it.qty;
            items.push_back(it);
        }
        f.close();
    }

    void saveItems() {
        ofstream f(itemFile);
        for (auto& it : items) {
            f << it.id << " " << it.name << "|" << it.price << " " << it.qty << "\n";
        }
        f.close();
    }

    void log(const string& msg) {
        ofstream f(logFile, ios::app);
        f << msg << "\n";
        f.close();
    }

    void seedDefault() {
        items = {
            {1, "Water (500ml)", 250, 10},
            {2, "Cola 330ml", 450, 8},
            {3, "Chocolate Bar", 350, 5},
            {4, "Chips", 300, 6},
            {5, "Soda", 200, 12}
        };
        saveItems();
    }

    void showItems() {
        cout << "\n--- Items ---\n";
        cout << left << setw(4) << "ID"
            << setw(22) << "Name"
            << setw(10) << "Price"
            << "Qty\n";

        for (auto& it : items) {
            cout << setw(4) << it.id
                << setw(22) << it.name
                << setw(8) << (it.price / 100.0) << "TL  "
                << it.qty << "\n";
        }
    }

    Item* findItem(int id) {
        for (auto& it : items)
            if (it.id == id) return &it;
        return nullptr;
    }

    void buyItem() {
        showItems();
        cout << "Enter item ID: ";
        int id; cin >> id;

        Item* it = findItem(id);
        if (!it) { cout << "Invalid ID.\n"; return; }
        if (it->qty <= 0) { cout << "Out of stock.\n"; return; }

        cout << "Price: " << (it->price / 100.0) << " TL\n";
        cout << "Insert money (TL): ";
        double m; cin >> m;

        int paid = round(m * 100);
        if (paid < it->price) {
            cout << "Not enough money.\n";
            return;
        }

        it->qty--;
        int change = paid - it->price;
        saveItems();

        cout << "Purchased: " << it->name << "\n";
        if (change > 0)
            cout << "Change: " << (change / 100.0) << " TL\n";

        log("User bought: " + it->name);
    }

    void adminMenu() {
        const string password = "admin123";
        cout << "Enter admin password: ";
        string p; cin >> p;
        if (p != password) { cout << "Wrong password.\n"; return; }

        while (true) {
            cout << "\n--- ADMIN PANEL ---\n";
            cout << "1) Show items\n";
            cout << "2) Add item\n";
            cout << "3) Remove item\n";
            cout << "4) Update item\n";
            cout << "5) Exit admin\n";
            cout << "Choice: ";

            int c; cin >> c;

            if (c == 1) showItems();

            else if (c == 2) {
                Item it;
                it.id = items.empty() ? 1 : items.back().id + 1;
                cout << "Name: ";
                cin.ignore();
                getline(cin, it.name);
                cout << "Price (TL): ";
                double t; cin >> t;
                it.price = round(t * 100);
                cout << "Quantity: ";
                cin >> it.qty;
                items.push_back(it);
                saveItems();
                log("Admin added item: " + it.name);
                cout << "Item added.\n";
            }

            else if (c == 3) {
                cout << "Enter ID to remove: ";
                int id; cin >> id;
                auto it = remove_if(items.begin(), items.end(),
                    [&](const Item& i) { return i.id == id; });
                if (it != items.end()) {
                    log("Admin removed item ID: " + to_string(id));
                    items.erase(it, items.end());
                    saveItems();
                    cout << "Removed.\n";
                }
                else cout << "ID not found.\n";
            }

            else if (c == 4) {
                cout << "Enter item ID: ";
                int id; cin >> id;
                Item* it = findItem(id);
                if (!it) { cout << "Not found.\n"; continue; }

                cout << "New price (TL): ";
                double t; cin >> t;
                it->price = round(t * 100);
                cout << "New qty: ";
                cin >> it->qty;
                saveItems();
                log("Admin updated item ID: " + to_string(id));
                cout << "Updated.\n";
            }

            else break;
        }
    }

    void menu() {
        while (true) {
            cout << "\n=== VENDING MACHINE ===\n";
            cout << "1) User mode\n";
            cout << "2) Admin mode\n";
            cout << "3) Exit\n";
            cout << "Choice: ";
            int c; cin >> c;

            if (c == 1) buyItem();
            else if (c == 2) adminMenu();
            else break;
        }
    }
};

int main() {
    VendingMachine vm;
    vm.menu();
    return 0;
}
