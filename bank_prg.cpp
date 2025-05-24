#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Customer {
public:
    int id;
    string name;
    string email;

    Customer(int i, string n, string e) : id(i), name(n), email(e) {}

    void display() {
        cout << "Customer ID: " << id << "\nName: " << name << "\nEmail: " << email << "\n";
    }
};

class Account {
public:
    int accountNumber;
    int customerId;
    double balance;

    Account(int accNo, int custId, double bal) : accountNumber(accNo), customerId(custId), balance(bal) {}

    void display() {
        cout << "Account Number: " << accountNumber << "\nCustomer ID: " << customerId << "\nBalance: " << balance << "\n";
    }
};

class BankManagement {
private:
    vector<Customer> customers;
    vector<Account> accounts;
    int nextCustomerId = 1;
    int nextAccountNumber = 1001;

public:
    void addCustomer(string name, string email) {
        customers.push_back(Customer(nextCustomerId++, name, email));
        cout << "Customer added.\n";
    }

    Customer* findCustomer(int id) {
        for (auto &c : customers)
            if (c.id == id) return &c;
        return nullptr;
    }

    Account* findAccount(int accNo) {
        for (auto &a : accounts)
            if (a.accountNumber == accNo) return &a;
        return nullptr;
    }

    void createAccount(int customerId, double initialDeposit) {
        if (!findCustomer(customerId)) {
            cout << "Invalid customer ID.\n";
            return;
        }
        accounts.push_back(Account(nextAccountNumber++, customerId, initialDeposit));
        cout << "Account created.\n";
    }

    void deposit(int accountNumber, double amount) {
        Account* acc = findAccount(accountNumber);
        if (!acc) {
            cout << "Account not found.\n";
            return;
        }
        acc->balance += amount;
        cout << "Amount deposited.\n";
    }

    void withdraw(int accountNumber, double amount) {
        Account* acc = findAccount(accountNumber);
        if (!acc) {
            cout << "Account not found.\n";
            return;
        }
        if (acc->balance < amount) {
            cout << "Insufficient balance.\n";
            return;
        }
        acc->balance -= amount;
        cout << "Amount withdrawn.\n";
    }

    void displayCustomers() {
        cout << "Customers:\n";
        for (auto &c : customers) {
            c.display();
            cout << "----\n";
        }
    }

    void displayAccounts() {
        cout << "Accounts:\n";
        for (auto &a : accounts) {
            a.display();
            cout << "----\n";
        }
    }
};

void showMenu() {
    cout << "\n--- Bank Management System ---\n";
    cout << "1. Add Customer\n2. Create Account\n3. Deposit\n4. Withdraw\n5. Display Customers\n6. Display Accounts\n7. Exit\nEnter choice: ";
}

int main() {
    BankManagement bank;
    int choice;

    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 7) break;

        switch (choice) {
            case 1: {
                string name, email;
                cout << "Enter customer name: ";
                getline(cin, name);
                cout << "Enter email: ";
                getline(cin, email);
                bank.addCustomer(name, email);
                break;
            }
            case 2: {
                int custId;
                double deposit;
                cout << "Enter customer ID: ";
                cin >> custId;
                cout << "Enter initial deposit: ";
                cin >> deposit;
                cin.ignore();
                bank.createAccount(custId, deposit);
                break;
            }
            case 3: {
                int accNo;
                double amount;
                cout << "Enter account number: ";
                cin >> accNo;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                cin.ignore();
                bank.deposit(accNo, amount);
                break;
            }
            case 4: {
                int accNo;
                double amount;
                cout << "Enter account number: ";
                cin >> accNo;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                cin.ignore();
                bank.withdraw(accNo, amount);
                break;
            }
            case 5:
                bank.displayCustomers();
                break;
            case 6:
                bank.displayAccounts();
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }

    cout << "Exiting...\n";
    return 0;
}
