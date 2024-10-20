#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
using namespace std;
#ifdef _WIN32
#include <windows.h>
#endif

class Account
{
private:
    string AccountNo, Password;
    int Balance;

public:
    Account() : AccountNo(""), Password(""), Balance(0) {}
    void setAccountNo(string id)
    {
        AccountNo = id;
    }
    void setPassword(string pw)
    {
        Password = pw;
    }
    void setBalance(int balance)
    {
        Balance = balance;
    }
    string getAccountNo()
    {
        return AccountNo;
    }
    string getPassword()
    {
        return Password;
    }
    int getBalance()
    {
        return Balance;
    }
};

void openAccount(Account user)
{
// Platform-specific screen clearing
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    string id, pw;
    cout << "\tEnter Account No: ";
    cin >> id;
    user.setAccountNo(id);
    cout << "\tEnter A Strong Password: ";
    cin >> pw;
    user.setPassword(pw);
    user.setBalance(0);

    ofstream outfile("/home/iman/Documents/account.txt", ios::app);
    if (!outfile)
    {
        cout << "\tError: File Can't Open!" << endl;
    }
    else
    {
        outfile << user.getAccountNo() << " : " << user.getPassword() << " : " << user.getBalance() << endl;
        cout << "\tAccount Created Successfully!" << endl;
    }
    outfile.close();
    usleep(5000000); // Wait for 5 seconds
}

void addcash()
{
// Platform-specific screen clearing
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    string id;
    cout << "\tEnter Account No: ";
    cin >> id;

    ifstream infile("/home/iman/Documents/account.txt");
    ofstream outfile("/home/iman/Documents/account_temp.txt");

    if (!infile || !outfile)
    {
        cout << "\tError: File Can't Open!" << endl;
    }
    string line;
    bool found = false;
    while (getline(infile, line))
    {
        stringstream ss;
        ss << line;
        string userId, UserPW;
        int UserBalance;
        char delimiter;

        ss >> userId >> delimiter >> UserPW >> delimiter >> UserBalance;
        if (id == userId)
        {
            found = true;
            int cash;
            cout << "\tEnter Cash: ";
            cin >> cash;
            int newBalance = UserBalance + cash;
            UserBalance = newBalance;
            outfile << userId << " : " << UserPW << " : " << UserBalance << endl;
            cout << "\tNew Balance Is: " << UserBalance << endl;
        }
        else
        {
            outfile << line << endl;
        }
    }
    if (!found)
    {
        cout << "\tEnter Valid Account No!" << endl;
    }
    outfile.close();
    infile.close();

    // File operations
    if (remove("/home/iman/Documents/account.txt") != 0)
        perror("Error deleting file");
    if (rename("/home/iman/Documents/account_temp.txt", "/home/iman/Documents/account.txt") != 0)
        perror("Error renaming file");

    usleep(5000000); // Wait for 5 seconds
}

void withdraw()
{
    string id, pw;
    cout << "\tEnter Account No: ";
    cin >> id;
    cout << "\tEnter Password: ";
    cin >> pw;

    ifstream infile("/home/iman/Documents/account.txt");
    ofstream outfile("/home/iman/Documents/account_temp.txt");

    if (!infile || !outfile)
    {
        cout << "\tError: File Can't Open!" << endl;
    }
    string line;
    bool found = false;
    while (getline(infile, line))
    {
        stringstream ss;
        ss << line;
        string UserId, UserPW;
        int UserBalance;
        char delimiter;

        ss >> UserId >> delimiter >> UserPW >> delimiter >> UserBalance;
        if (id == UserId && pw == UserPW)
        {
            found = true;
            int cash;
            cout << "\tEnter Cash: ";
            cin >> cash;
            if (cash <= UserBalance)
            {
                int newBalance = UserBalance - cash;
                UserBalance = newBalance;
                outfile << UserId << " : " << UserPW << " : " << UserBalance << endl;
                cout << "\tTransaction Was Successful!" << endl;
                cout << "\tRemaining Balance: " << UserBalance << endl;
            }
            else
            {
                cout << "\tLow Balance!" << endl;
                outfile << UserId << " : " << UserPW << " : " << UserBalance << endl;
            }
        }
        else
        {
            outfile << line << endl;
        }
    }
    outfile.close();
    infile.close();

    // File operations
    if (remove("/home/iman/Documents/account.txt") != 0)
        perror("Error deleting file");
    if (rename("/home/iman/Documents/account_temp.txt", "/home/iman/Documents/account.txt") != 0)
        perror("Error renaming file");

    usleep(5000000); // Wait for 5 seconds
}

int main()
{
    Account user;
    bool exit = false;
    while (!exit)
    {
// Platform-specific screen clearing
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        int val;
        cout << "\t\t\t\t\t\t\t\tWelcome To Bank Account Management System" << endl;
        cout << "\t----------------------------------------------------------" << endl;
        cout << "\t1. Open New Account." << endl;
        cout << "\t2. Add Cash." << endl;
        cout << "\t3. Withdraw Cash." << endl;
        cout << "\t4. Exit." << endl;
        cout << "\tEnter Your Choice: ";
        cin >> val;

        if (val == 1)
        {
            openAccount(user);
        }
        else if (val == 2)
        {
            addcash();
        }
        else if (val == 3)
        {
            withdraw();
        }
        else if (val == 4)
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            exit = true;
            cout << "\tGood Luck!" << endl;
            usleep(2000000); // Wait for 2 seconds
        }
        usleep(3000000); // Wait for 3 seconds
    }
    return 0;
}
