#include<iostream>
#include<fstream>
#include<unordered_map>
using namespace std;

class Account{
    int accountNumber;
    string firstName, lastName;
    double balance;

    static int accountNumberGenerator;

    friend ostream &operator<<(ostream &os, Account &acc);
    friend ifstream &operator>>(ifstream &ifs, Account &acc);
    friend ofstream &operator<<(ofstream &ofs, Account &acc);

    public:
        Account(){}
        Account(string &fn, string &ln, double &bal){
            firstName = fn;
            lastName = ln;
            balance = bal;
            accountNumber = ++accountNumberGenerator;
        }
        int getAccNo(){
            return accountNumber;
        }
        void deposit(double &amount){
            balance += amount;
        }
        void withdraw(double &amount){
            if(balance - amount < 0) cout << endl << "No enough balance..!" << endl;
            else balance -= amount;
        }
        static void setAccountGenerator(int val){
            accountNumberGenerator = val;
        }
};

int Account::accountNumberGenerator = 0;

ostream &operator<<(ostream &os, Account &acc){
    os << endl;
    os << "Account Number: " << acc.accountNumber << endl;
    os << "Name: " << acc.firstName << " " << acc.lastName << endl;
    os << "Balance: " << acc.balance << endl;
    return os;
}

ifstream &operator>>(ifstream &ifs, Account &acc){
    ifs >> acc.accountNumber;
    ifs >> acc.firstName;
    ifs >> acc.lastName;
    ifs >> acc.balance;
    return ifs;
}

ofstream &operator<<(ofstream &ofs, Account &acc){
    ofs << acc.accountNumber << endl;
    ofs << acc.firstName << endl;
    ofs << acc.lastName << endl;
    ofs << acc.balance << endl;
    return ofs;
}

class Bank{
    unordered_map<int, Account> accounts;
    
    public:
        Bank(){
            ifstream impot;
            impot.open("database.txt");
            Account account;
            while (impot >> account) {
                if (account.getAccNo() != 0) {
                    accounts.insert({ account.getAccNo(), account });
                    Account::setAccountGenerator(account.getAccNo());
                }
            }
            impot.close();
        }

        Account createAccount(string &firstName, string &lastName, double &amount){
            Account account {firstName, lastName, amount};
            accounts.insert({account.getAccNo(), account});
            return account;
        }
        bool accountDetail(int &accountNumber){
            auto it = accounts.find(accountNumber);
            if(it == accounts.end()) return false;
            cout << it->second;
            return true;
        }
        bool deposit(int &accountNumber , double &amount){
            auto it = accounts.find(accountNumber);
            if(it == accounts.end()) return false;
            it->second.deposit(amount);
            cout << it->second;
            return true;
        }
        bool withdraw(int &accountNumber ,double &amount){
            auto it = accounts.find(accountNumber);
            if(it == accounts.end()) return false;
            it->second.withdraw(amount);
            cout << it->second;
            return true;
        }
        bool deleteAccount(int &accountNumber){
            if(accounts.find(accountNumber) == accounts.end()) return false;
            accounts.erase(accountNumber);
            return true;
        }
        bool all(){
            if(accounts.empty()) return false;
            for(auto it = accounts.begin(); it != accounts.end(); it++){
                cout << it->second << endl;
            }
            return true;
        }
        ~Bank(){
            ofstream expot;
            expot.open("database.txt");
            for(auto it = accounts.begin(); it != accounts.end(); it++){
                expot << it->second;
            }
            expot.close();
        }
};

int main()
{
    while(true){
        cout << "=========================" << endl;
        cout << "1 - Create Account" << endl;
        cout << "2 - View Account Detail" << endl;
        cout << "3 - Deposit" << endl;
        cout << "4 - Withdraw" << endl;
        cout << "5 - Close Account" << endl;
        cout << "6 - All Accounts" << endl;
        cout << "7 - Exit" << endl;
        cout << "=========================" << endl;
        cout << endl;

        cout << "Enter digit: ";
        int choice; cin >> choice;

        string firstName, lastName;
        int accountNumber;
        double amount; 
        Bank bank;
        Account acc;

        switch(choice){
            case 1:
                cout << "Enter your First Name: ";
                cin >> firstName;
                cout << "Enter your Last Name: ";
                cin >> lastName;
                cout << "Enter amount: ";
                cin >> amount;
                acc = bank.createAccount(firstName, lastName, amount);
                cout << "\nAccount Created Successfully!" << endl;
                cout << acc << endl;
                break;

            case 2:
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                if(!bank.accountDetail(accountNumber))
                    cout << "Enter valid account number..!" << endl;
                break;

            case 3:
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Amount: ";
                cin >> amount;
                if(!bank.deposit(accountNumber ,amount))
                    cout << "Enter valid account number..!" << endl;
                break;

            case 4:
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Amount: ";
                cin >> amount;
                if(!bank.withdraw(accountNumber ,amount))
                    cout << "Enter valid account number..!" << endl;
                break;

            case 5:
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                if(!bank.deleteAccount(accountNumber)) 
                    cout << "Enter valid account number..!" << endl;
                else cout << "Account Deleted Successfully!" << endl;
                break;

            case 6:
                if(!bank.all()) cout << "No data..!" << endl;
                break;
            case 7:
                exit(0);
            default:
                cout << "Please, Enter valid Number..!" << endl;
        }
    }
    return 0;
}