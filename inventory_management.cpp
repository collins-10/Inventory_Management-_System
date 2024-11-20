#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Class representing a single item in the inventory
class Item {
private:
    int itemId;
    string itemName;
    int stockQuantity;
    double unitPrice;

public:
    // Constructors
    Item() {}
    Item(int id, string name, int qty, double price)
        : itemId(id), itemName(name), stockQuantity(qty), unitPrice(price) {}

    // Display item details
    void showItem() const {
        cout << "ID: " << itemId << "\nName: " << itemName
             << "\nStock: " << stockQuantity << "\nUnit Price: $" << unitPrice << endl;
    }

    // Getters
    int getId() const { return itemId; }
    string getName() const { return itemName; }
    int getStock() const { return stockQuantity; }
    double getPrice() const { return unitPrice; }

    // Setters
    void setStock(int qty) { stockQuantity = qty; }
    void setPrice(double price) { unitPrice = price; }

    // File stream operators for reading and writing data
    friend ofstream &operator<<(ofstream &ofs, const Item &item);
    friend ifstream &operator>>(ifstream &ifs, Item &item);
};

// Overload file operators for writing and reading Item data
ofstream &operator<<(ofstream &ofs, const Item &item) {
    ofs << item.itemId << "\n" << item.itemName << "\n" << item.stockQuantity << "\n" << item.unitPrice << "\n";
    return ofs;
}

ifstream &operator>>(ifstream &ifs, Item &item) {
    ifs >> item.itemId;
    ifs.ignore();  // Ignore newline after ID
    getline(ifs, item.itemName);
    ifs >> item.stockQuantity >> item.unitPrice;
    return ifs;
}

// Class to handle inventory operations
class Inventory {
private:
    vector<Item> items;  // List of items in inventory
    const string filePath = "inventory_data.txt";

    // Load all items from file into items vector
    void loadItems() {
        ifstream inFile(filePath);
        if (inFile.is_open()) {
            Item item;
            while (inFile >> item) {
                items.push_back(item);
            }
            inFile.close();
        }
    }

    // Save all items from items vector into file
    void saveItems() const {
        ofstream outFile(filePath);
        for (const auto &item : items) {
            outFile << item;
        }
    }

public:
    Inventory() { loadItems(); }
    ~Inventory() { saveItems(); }

    // Add a new item to the inventory
    void addItem(const Item &item) {
        items.push_back(item);
        cout << "Item successfully added!\n";
    }

    // Display all items in inventory
    void displayAllItems() const {
        if (items.empty()) {
            cout << "No items in inventory.\n";
            return;
        }
        for (const auto &item : items) {
            item.showItem();
            cout << "----------------------\n";
        }
    }

    // Update an item's stock and price by ID
    void updateItem(int id, int newStock, double newPrice) {
        for (auto &item : items) {
            if (item.getId() == id) {
                item.setStock(newStock);
                item.setPrice(newPrice);
                cout << "Item updated successfully!\n";
                return;
            }
        }
        cout << "Item not found!\n";
    }

    // Remove an item from the inventory by ID
    void removeItem(int id) {
        auto it = items.begin();
        for (; it != items.end(); ++it) {
            if (it->getId() == id) {
                items.erase(it);
                cout << "Item deleted successfully!\n";
                return;
            }
        }
        cout << "Item not found!\n";
    }

    // Search for an item by ID
    void searchItem(int id) const {
        for (const auto &item : items) {
            if (item.getId() == id) {
                item.showItem();
                return;
            }
        }
        cout << "Item not found!\n";
    }
};

// Main function
int main() {
    Inventory inventory;
    int choice;

    do {
        cout << "\nInventory System\n";
        cout << "1. Add New Item\n";
        cout << "2. View All Items\n";
        cout << "3. Update Item\n";
        cout << "4. Delete Item\n";
        cout << "5. Search for Item\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, stock;
                string name;
                double price;
                cout << "Enter Item ID: ";
                cin >> id;
                cout << "Enter Item Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Stock Quantity: ";
                cin >> stock;
                cout << "Enter Unit Price: ";
                cin >> price;
                Item item(id, name, stock, price);
                inventory.addItem(item);
                break;
            }
            case 2:
                inventory.displayAllItems();
                break;
            case 3: {
                int id, newStock;
                double newPrice;
                cout << "Enter Item ID to update: ";
                cin >> id;
                cout << "Enter New Stock Quantity: ";
                cin >> newStock;
                cout << "Enter New Unit Price: ";
                cin >> newPrice;
                inventory.updateItem(id, newStock, newPrice);
                break;
            }
            case 4: {
                int id;
                cout << "Enter Item ID to delete: ";
                cin >> id;
                inventory.removeItem(id);
                break;
            }
            case 5: {
                int id;
                cout << "Enter Item ID to search: ";
                cin >> id;
                inventory.searchItem(id);
                break;
            }
            case 6:
                cout << "Exiting the program...\n";
                break;
            default:
                cout << "Invalid option! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}