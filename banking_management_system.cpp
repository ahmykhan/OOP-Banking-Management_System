


#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<string.h>
#include<ctime>
#include<fstream>
using namespace std;

const int maxuser = 600;
const int maxcomp = 200;
const int maxcards = 1200;
const int maxtrans = 8000;
const int maxadmin = 50;
const int maxemp = 2000;


class UserClient;
class CompanyClient;
class BankingEmployee;
class AccountType;
class Card;
class Transaction;


UserClient* users = nullptr;
CompanyClient* companies = nullptr;
BankingEmployee* admins = nullptr;
Card* cards = nullptr;
Transaction* transactions = nullptr;
string* empUserIds = nullptr;
string* empCompanyIds = nullptr;

int userCount = 0;
int companyCount = 0;
int cardCount = 0;
int transactionCount = 0;
int adminCount = 0;
int mapcount = 0;
int pendingCount = 0;

string userPendingPins[maxuser];
string pendingUserIds[maxuser];

// Help
bool isAllDigits(const string& s)
{
    if (s.length() == 0)
        return false;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

string todayDate()
{
    time_t t;
    time(&t);
    tm* lt = localtime(&t);
    char buf[12];
    int year = lt->tm_year + 1900;
    int mon = lt->tm_mon + 1;
    int day = lt->tm_mday;
    sprintf(buf, "%04d-%02d-%02d", year, mon, day);
    return string(buf);
}

void splitCSV(const string& line, string tokens[], int& count, int tokenmax)
{
    count = 0;
    string pre = "";
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == ',') {
            if (count < tokenmax)
            {
                tokens[count++] = pre;
            }
            pre.clear();
        }
        else
        {
            pre.push_back(c);
        }
    }
    if (count < tokenmax)
    {
        tokens[count++] = pre;
    }
}

bool strToBool(const string& s)
{
    return s == "1" || s == "true";
}

// Class
class User
{
private:
    string fullName;
    string address;
    string loginId;
    string password;
    string phone;
    string cnic;

public:
    User() : fullName(""), address(""), loginId(""), password(""), phone(""), cnic("") {}
    User(string name, string add, string Id, string pass, string phone, string cnic) : cnic(cnic)
    {
        fullName = name;
        address = add;
        loginId = Id;
        password = pass;
        this->phone = phone;
    }
    virtual ~User() {}

    void setFullName(string name)
    {
        fullName = name; 
    }
    void setAddress(string add) 
    {
        address = add; 
    }
    void setLoginId(string id) {
        loginId = id;
    }
    void setPassword(string pass) {
        password = pass; 
    }
    void setPhone(string phn) 
    {
        phone = phn;
    }
    void setCnic(string c) 
    {
        cnic = c; 
    }

    string getFullName() 
    {
        return fullName;
    }
    string getAddress()
    {
        return address; 
    }
    string getLoginId() 
    { 
        return loginId;
    }
    string getPassword()
    {
        return password; 
    }
    string getPhone() 
    { 
        return phone;
    }
    string getCnic() 
    {
        return cnic;
    }

    void displayInfo()
    {
        cout << "Full Name: " << fullName << endl;
        cout << "Login ID: " << loginId << endl;
        cout << "Address: " << address << endl;
        cout << "Phone Number: " << phone << endl;
        cout << "CNIC: " << cnic << endl;
    }
};

class AccountType
{
private:
    double withdralLimit;
    string accountTypeName;

public:
    AccountType() :withdralLimit(0), accountTypeName("") {}
    AccountType(double limit, string type) :withdralLimit(limit), accountTypeName(type) {}
    virtual ~AccountType() {}

    void setWithdrawlLimit(double limit)
    { 
        withdralLimit = limit;
    }
    void setAccountTypeName(string type) 
    { 
        accountTypeName = type;
    }
    double getWithdrawlLimit() 
    { 
        return withdralLimit;
    }
    string getAccountTypeName()
    { 
        return accountTypeName; 
    }
    virtual void displayAccountType() = 0;
};

class Bronze : public AccountType
{
public:
    Bronze(int limit, string type) :AccountType(limit, type) {}
    void displayAccountType()
    {
        cout << "Account type: " << getAccountTypeName() << endl;
        cout << "Withdrawal limit: " << getWithdrawlLimit() << endl;
    }
};

class Gold : public AccountType
{
public:
    Gold(int limit, string type) :AccountType(limit, type) {}
    void displayAccountType()
    {
        cout << "Account type: " << getAccountTypeName() << endl;
        cout << "Withdrawal limit: " << getWithdrawlLimit() << endl;
    }
};

class Business : public AccountType
{
public:
    Business(int limit, string type) :AccountType(limit, type) {}
    void displayAccountType()
    {
        cout << "Account type: " << getAccountTypeName() << endl;
        cout << "Withdrawal limit: " << getWithdrawlLimit() << endl;
    }
};

class Card
{
private:
    string clientUserId;
    string cardNumber;
    string cardPin;
    int falseAttempts;
    bool isBlocked;

public:
    Card() :clientUserId(""), cardNumber(""), cardPin(""), falseAttempts(0), isBlocked(0) {}
    Card(string clientId, string cardNum, string pin, int attempts, bool isBlocked) : isBlocked(isBlocked)
    {
        clientUserId = clientId;
        cardNumber = cardNum;
        cardPin = pin;
        falseAttempts = attempts;
    }

    void setClientUserId(string Id) { clientUserId = Id; }
    void setCardNumber(string card_num) { cardNumber = card_num; }
    void setCardPin(string card_pin) { cardPin = card_pin; }
    void setFailedAttempts(int attempts) { falseAttempts = attempts; }
    void setIsBlocked(bool isblock) { isBlocked = isblock; }

    string getClientUserId()
    {
        return clientUserId;
    }
    string getCardNumber() 
    {
        return cardNumber; 
    }
    string getCardPin() 
    { 
        return cardPin; 
    }
    int getFailedAttempts() 
    {
        return falseAttempts;
    }
    bool getIsBlocked()
    { 
        return isBlocked;
    }

    void displayInfo()
    {
        cout << "Client User ID: " << clientUserId << endl;
        cout << "Card Number: " << cardNumber << endl;
        cout << "Failed Attempts: " << falseAttempts << endl;
        cout << "Is Blocked: " << (isBlocked ? "Yes" : "No") << endl;
    }

    static void savecards(const string& fname = "cards.txt");
    static void loadcards(const string& fname = "cards.txt");
    static int findCardIndex(const string& cardNum);
    static bool verifypincard(const string& cardNum, const string& enteredPin, string& clientIdOut);
    static void listCardsForUser(const string& userLoginId);
};

class Transaction
{
private:
    string transactionDate;
    string clientUserId;
    double amount;
    string transactionType;
    string targetUserId;

public:
    Transaction() :transactionDate(""), clientUserId(""), amount(0), transactionType(""), targetUserId("") {}
    Transaction(string date, string userId, double amnt, string type, string targetUserId) : targetUserId(targetUserId)
    {
        transactionDate = date;
        clientUserId = userId;
        amount = amnt;
        transactionType = type;
    }

    void setTransactionDate(string date)
    {
        transactionDate = date; }
    void setClientUserId(string ID) 
    {
        clientUserId = ID; }
    void setAmount(double amnt) 
    {
        amount = amnt; }
    void setTransactionype(string type)
    { 
        transactionType = type; }
    void setTargetUserId(string ID)
    { 
        targetUserId = ID; }

    string getTransactionDate()
    {
        return transactionDate
        ; }
    string getClientUserId()
    {
        return clientUserId;
    }
    double getAmount()
    {
        return amount;
    }
    string getTransactionype()
    {
        return transactionType;
    }
    string getTargetUserId()
    {
        return targetUserId;
    }

    void displayInfo()
    {
        cout << "Transaction Date: " << transactionDate << endl;
        cout << "Client User ID: " << clientUserId << endl;
        cout << "Amount: " << amount << endl;
        cout << "Transaction type: " << transactionType << endl;
        if (targetUserId != "")
            cout << "Target User ID: " << targetUserId << endl;
    }

    static void recordtrans(const string& date, const string& clientId, double amount, const string& type, const string& target = "");
    static void savetrans(const string& fname = "transactions.txt");
    static void loadtrans(const string& fname = "transactions.txt");
    static double calculateDailySpent(const string& clientId, const string& date);
    static void displayTransactionHistory(const string& clientId);
};

class UserClient : public User
{
private:
    double accountBalance;
    AccountType* accountType;
    Card* cardsArray;
    int cardCountLocal;
    bool isApproved;
    bool isFrozen;

public:
    UserClient() : accountType(nullptr), cardsArray(nullptr), accountBalance(0), cardCountLocal(0), isApproved(0), isFrozen(0) {}
    ~UserClient()
    {
        if (accountType != nullptr)
            delete accountType;
        if (cardsArray != nullptr)
            delete[] cardsArray;
    }

    void setAccountBalance(double balance) 
    {
        accountBalance = balance; 
    }
    void setaccountType(AccountType* acctype)
    {
        accountType = acctype;
    }
    void setCards(Card* card)
    {
        cardsArray = card; 
    }
    void setisApproved(bool isapprove) 
    {
        isApproved = isapprove;
    }
    void setIsFrozen(bool isfrozen) 
    {
        isFrozen = isfrozen;
    }


    double getAccountBalance() 
    {
        return accountBalance; 
    }
    AccountType* getaccountType() 
    {
        return accountType;
    }
    Card* getCards()
    { 
        return cardsArray;
    }
    int getCardCount() 
    { 
        return cardCountLocal; 
    }
    bool getisApproved() 
    {
        return isApproved; 
    }
    bool getIsFrozen()
    {
        return isFrozen; 
    }

    double getWithdrawalLimit()
    {
        if (accountType != nullptr)
            return accountType->getWithdrawlLimit();
        return 100000.0;
    }

    bool checklimitfordaily(double amount)
    {
        string today = todayDate();
        double spent = Transaction::calculateDailySpent(getLoginId(), today);
        double limit = getWithdrawalLimit();
        return (spent + amount) <= limit;
    }

    static bool deposit(const string& loginId, double amount);
    static bool cardwithdraw(const string& cardNum, const string& pin, double amount);
    static bool transferTo(const string& cardNum, const string& pin, const string& toUserLogin, double amount);
    static void saveUsers(const string& fname = "users.txt");
    static void loadUsers(const string& fname = "users.txt");
    static int findUserByLogin(const string& loginId);
    static void listuser();
};

class CompanyClient : public User
{
private:
    string companyName;
    string taxNumber;
    double accountBalance;
    AccountType* accountType;
    string* employeeIDs;
    int employeeCount;
    bool isApproved;
    bool isFrozen;

public:
    CompanyClient() : accountBalance(0), employeeCount(0), isApproved(0), isFrozen(0)
    {
        companyName = "";
        taxNumber = "";
        accountType = nullptr;
        employeeIDs = nullptr;
    }
    ~CompanyClient()
    {
        if (accountType != nullptr)
            delete accountType;
        if (employeeIDs != nullptr)
            delete[] employeeIDs;
    }

    void setCompanyName(string name)
    {
        companyName = name; 
    }
    void setTaxNumber(string tax_num) 
    {
        taxNumber = tax_num;
    }
    void setAccountBalance(double balance)
    { 
        accountBalance = balance;
    }
    void setAccountType(AccountType* type) 
    {
        accountType = type;
    }
    void setEmployeeIDs(string* IDs)
    {
        employeeIDs = IDs;
    }
    void setEmployeeCount(int count)
    {
        employeeCount = count;
    }
    void setIsApprovd(bool isapprove) 
    {
        isApproved = isapprove; 
    }
    void setIsFrozen(bool isfrozen) 
    {
        isFrozen = isfrozen; 
    }

    string getCompanyName()
    {
        return companyName;
    }
    string getTaxNumber()
    {
        return taxNumber;
    }
    double getAccountBalance() 
    {
        return accountBalance;
    }
    AccountType* getAccountType() 
    {
        return accountType; 
    }
    string* getEmployeeIDs() 
    { 
        return employeeIDs; 
    }
    int getEmployeeCount()
    {
        return employeeCount;
    }
    bool getIsApprovd()
    { 
        return isApproved; 
    }
    bool getIsFrozen() 
    { 
        return isFrozen;
    }

    double getWithdrawalLimit()
    {
        if (accountType != nullptr)
            return accountType->getWithdrawlLimit();
        return 20000000.0;
    }

    bool checkDailyLimit(double amount)
    {
        string today = todayDate();
        double spent = Transaction::calculateDailySpent(getLoginId(), today);
        double limit = getWithdrawalLimit();
        return (spent + amount) <= limit;
    }

    void displayInfo()
    {
        cout << "Company name: " << companyName << endl;
        cout << "Tax number: " << taxNumber << endl;
        cout << "Account balance: " << accountBalance << endl;
        cout << "Employee count: " << employeeCount << endl;
        cout << "Is Approved: " << (isApproved ? "Yes" : "No") << endl;
        cout << "Is Frozen: " << (isFrozen ? "Yes" : "No") << endl;
    }

    static void saveCompanies(const string& fname = "companies.txt");
    static void loadCompanies(const string& fname = "companies.txt");
    static int findCompanyById(const string& companyId);
    static void listcomp();
    static void savecompanyemp(const string& fname = "companies_employees.txt");
    static void loadcompanyemp(const string& fname = "companies_employees.txt");
};

class BankingEmployee : public User
{
private:
    string employeeId;
    string designation;

public:
    BankingEmployee() :employeeId(""), designation("") {}

    void setEmployeeId(string ID) 
    { 
        employeeId = ID;
    }
    void setDesignation(string des) 
    {
        designation = des;
    }
    string getEmployeeId() 
    { 
        return employeeId;
    }
    string getDesignation()
    { 
        return designation;
    }

    static bool approveUser(const string& loginId);
    static bool declineuser(const string& loginId);
    static void viewAllUsers()
    { 
        UserClient::listuser();
    }
    static void viewAllCompanies()
    {
        CompanyClient::listcomp();
    }
    static void saveadmin(const string& fname = "admin.txt");
    static void loadadmin(const string& fname = "admin.txt");
    static bool loginadmin(const string& adminId, const string& password);
};

int UserClient::findUserByLogin(const string& loginId)
{
    for (int i = 0; i < userCount; ++i)
        if (users[i].getLoginId() == loginId)
            return i;
    return -1;
}

int CompanyClient::findCompanyById(const string& companyId)
{
    for (int i = 0; i < companyCount; ++i)
        if (companies[i].getLoginId() == companyId)
            return i;
    return -1;
}

int Card::findCardIndex(const string& cardNum)
{
    for (int i = 0; i < cardCount; ++i)
        if (cards[i].getCardNumber() == cardNum)
            return i;
    return -1;
}

double Transaction::calculateDailySpent(const string& clientId, const string& date)
{
    double total = 0.0;
    for (int i = 0; i < transactionCount; ++i)
    {
        if (transactions[i].getClientUserId() == clientId && transactions[i].getTransactionDate() == date)
        {
            string type = transactions[i].getTransactionype();
            if (type == "Withdraw" || type == "Transfer")
                total += transactions[i].getAmount();
        }
    }
    return total;
}

void Transaction::recordtrans(const string& date, const string& clientId, double amount, const string& type, const string& target)
{
    if (transactionCount < maxtrans)
    {
        transactions[transactionCount].setTransactionDate(date);
        transactions[transactionCount].setClientUserId(clientId);
        transactions[transactionCount].setAmount(amount);
        transactions[transactionCount].setTransactionype(type);
        transactions[transactionCount].setTargetUserId(target);
        ++transactionCount;
        Transaction::savetrans();
    }
}

bool UserClient::deposit(const string& loginId, double amount)
{
    if (amount <= 0.0)
        return false;

    int uidx = UserClient::findUserByLogin(loginId);
    if (uidx != -1)
    {
        double bal = users[uidx].getAccountBalance();
        users[uidx].setAccountBalance(bal + amount);
        Transaction::recordtrans(todayDate(), loginId, amount, "Deposit");
        UserClient::saveUsers();
        return true;
    }

    int cidx = CompanyClient::findCompanyById(loginId);
    if (cidx != -1)
    {
        double bal = companies[cidx].getAccountBalance();
        companies[cidx].setAccountBalance(bal + amount);
        Transaction::recordtrans(todayDate(), loginId, amount, "Deposit");
        CompanyClient::saveCompanies();
        return true;
    }
    return false;
}

bool Card::verifypincard(const string& cardNum, const string& enteredPin, string& clientIdOut)
{
    int ind = Card::findCardIndex(cardNum);
    if (ind == -1)
        return false;

    Card& c = cards[ind];
    clientIdOut = c.getClientUserId();

    if (c.getIsBlocked())
        return false;

    if (c.getCardPin() == enteredPin)
    {
        c.setFailedAttempts(0);
        Card::savecards();
        return true;
    }
    else
    {
        int fails = c.getFailedAttempts();
        fails++;
        c.setFailedAttempts(fails);

        if (fails >= 3)
        {
            c.setIsBlocked(true);
            int uidx = UserClient::findUserByLogin(c.getClientUserId());
            if (uidx != -1)
            {
                users[uidx].setIsFrozen(true);
                UserClient::saveUsers();
            }
        }
        Card::savecards();
        return false;
    }
}

bool UserClient::cardwithdraw(const string& cardNum, const string& pin, double amount)
{
    if (amount <= 0.0)
        return false;

    string clientId;
    if (!Card::verifypincard(cardNum, pin, clientId))
    {
        cout << "PIN verification failed or card blocked.\n";
        return false;
    }

    int uidx = UserClient::findUserByLogin(clientId);
    if (uidx == -1)
    {
        cout << "User not found for card owner.\n";
        return false;
    }

    UserClient& u = users[uidx];
    if (u.getIsFrozen())
    {
        cout << "Account is frozen.\n";
        return false;
    }

    if (!u.checklimitfordaily(amount))
    {
        cout << "Daily withdrawal limit exceeded.\n";
        return false;
    }

    if (amount > u.getAccountBalance())
    {
        cout << "Insufficient balance.\n";
        return false;
    }

    u.setAccountBalance(u.getAccountBalance() - amount);
    Transaction::recordtrans(todayDate(), clientId, amount, "Withdraw");
    UserClient::saveUsers();
    return true;
}

bool UserClient::transferTo(const string& cardNum, const string& pin, const string& toUserLogin, double amount)
{
    if (amount <= 0.0) return false;

    string clientId;
    if (!Card::verifypincard(cardNum, pin, clientId))
    {
        cout << "Card PIN verification failed.\n";
        return false;
    }

    int fromIdx = UserClient::findUserByLogin(clientId);
    if (fromIdx == -1)
    {
        cout << "Sender not found.\n";
        return false;
    }

    int toIdx = UserClient::findUserByLogin(toUserLogin);
    if (toIdx == -1)
    {
        cout << "Recipient user not found.\n";
        return false;
    }

    UserClient& sender = users[fromIdx];
    if (sender.getIsFrozen())
    {
        cout << "Sender account frozen.\n";
        return false;
    }

    if (!sender.checklimitfordaily(amount))
    {
        cout << "Daily limit exceeded.\n";
        return false;
    }

    if (amount > sender.getAccountBalance())
    {
        cout << "Insufficient balance.\n";
        return false;
    }

    sender.setAccountBalance(sender.getAccountBalance() - amount);
    users[toIdx].setAccountBalance(users[toIdx].getAccountBalance() + amount);
    Transaction::recordtrans(todayDate(), clientId, amount, "Transfer", toUserLogin);
    UserClient::saveUsers();
    return true;
}

void UserClient::saveUsers(const string& fname)
{
    ofstream file(fname.c_str());
    if (!file.is_open())
        return;

    for (int i = 0; i < userCount; ++i)
    {
        file << users[i].getLoginId() << "," << users[i].getFullName() << ",";
        file << users[i].getAddress() << "," << users[i].getCnic() << "," << users[i].getLoginId() << ",";
        file << users[i].getPassword() << "," << users[i].getAccountBalance() << "\n";
    }
    file.close();
}

void UserClient::loadUsers(const string& fname)
{
    userCount = 0;
    ifstream file(fname.c_str());
    if (!file.is_open())
        return;

    string line, toks[10];
    int tcount;

    while (getline(file, line))
    {
        if (line.size() == 0)
            continue;

        splitCSV(line, toks, tcount, 10);
        if (tcount < 7)
            continue;

        string loginId = toks[0];
        string fullname = toks[1];
        string address = toks[2];
        string cnic = toks[3];
        string password = toks[5];
        double balance = 0.0;

        try { balance = stod(toks[6]); }
        catch (...) { balance = 0.0; }

        if (userCount < maxuser)
        {
            users[userCount].setLoginId(loginId);
            users[userCount].setFullName(fullname);
            users[userCount].setAddress(address);
            users[userCount].setCnic(cnic);
            users[userCount].setPassword(password);
            users[userCount].setAccountBalance(balance);
            users[userCount].setisApproved(true);
            users[userCount].setIsFrozen(false);
            ++userCount;
        }
    }
    file.close();
}

void CompanyClient::saveCompanies(const string& fname)
{
    ofstream file(fname.c_str());
    if (!file.is_open())
        return;

    for (int i = 0; i < companyCount; ++i)
    {
        file << companies[i].getLoginId() << "," << companies[i].getCompanyName() << "," << companies[i].getAddress() << ",";
        file << companies[i].getTaxNumber() << "," << companies[i].getLoginId() << "," << companies[i].getPassword() << ",";
        file << companies[i].getAccountBalance() << "\n";
    }
    file.close();
}

void CompanyClient::loadCompanies(const string& fname)
{
    companyCount = 0;
    ifstream file(fname.c_str());
    if (!file.is_open())
        return;

    string line, toks[10];
    int tcount;

    while (getline(file, line))
    {
        if (line.size() == 0)
            continue;

        splitCSV(line, toks, tcount, 10);
        if (tcount < 7)
            continue;

        string companyId = toks[0];
        string name = toks[1];
        string address = toks[2];
        string tax = toks[3];
        string password = toks[5];
        double balance = 0.0;

        try { balance = stod(toks[6]); }
        catch (...) { balance = 0.0; }

        if (companyCount < maxcomp)
        {
            companies[companyCount].setLoginId(companyId);
            companies[companyCount].setCompanyName(name);
            companies[companyCount].setAddress(address);
            companies[companyCount].setTaxNumber(tax);
            companies[companyCount].setPassword(password);
            companies[companyCount].setAccountBalance(balance);
            companies[companyCount].setIsApprovd(true);
            companies[companyCount].setIsFrozen(false);
            ++companyCount;
        }
    }
    file.close();
}

void CompanyClient::savecompanyemp(const string& fname)
{
    ofstream file(fname.c_str());
    if (!file.is_open())
        return;

    for (int i = 0; i < mapcount; ++i)
    {
        file << empUserIds[i] << "," << empCompanyIds[i] << "\n";
    }
    file.close();
}

void CompanyClient::loadcompanyemp(const string& fname)
{
    mapcount = 0;
    ifstream file(fname.c_str());
    if (!file.is_open())
        return;

    string line, toks[5];
    int tcount;

    while (getline(file, line))
    {
        if (line.size() == 0)
            continue;

        splitCSV(line, toks, tcount, 5);
        if (tcount < 2)
            continue;

        if (mapcount < maxemp)
        {
            empUserIds[mapcount] = toks[0];
            empCompanyIds[mapcount] = toks[1];
            ++mapcount;
        }
    }
    file.close();
}

void Transaction::savetrans(const string& fname)
{
    ofstream fileo(fname.c_str());
    if (!fileo.is_open())
        return;

    for (int i = 0; i < transactionCount; ++i)
    {
        fileo << transactions[i].getTransactionDate() << "," << transactions[i].getClientUserId() << ","
            << transactions[i].getAmount() << "," << transactions[i].getTransactionype() << ","
            << transactions[i].getTargetUserId() << "\n";
    }
    fileo.close();
}

void Transaction::loadtrans(const string& fname)
{
    transactionCount = 0;
    ifstream filei(fname.c_str());
    if (!filei.is_open())
        return;

    string line, toks[8];
    int tcount;

    while (getline(filei, line))
    {
        if (line.size() == 0)
            continue;

        splitCSV(line, toks, tcount, 8);
        if (tcount < 4)
            continue;

        string date = toks[0];
        string uid = toks[1];
        double amnt = 0.0;

        try { amnt = stod(toks[2]); }
        catch (...) { amnt = 0.0; }

        string type = toks[3];
        string target = (tcount >= 5 ? toks[4] : "");

        if (transactionCount < maxtrans)
        {
            transactions[transactionCount].setTransactionDate(date);
            transactions[transactionCount].setClientUserId(uid);
            transactions[transactionCount].setAmount(amnt);
            transactions[transactionCount].setTransactionype(type);
            transactions[transactionCount].setTargetUserId(target);
            ++transactionCount;
        }
    }
    filei.close();
}

void Card::savecards(const string& fname)
{
    ofstream fileo(fname.c_str());
    if (!fileo.is_open())
        return;

    for (int i = 0; i < cardCount; ++i)
    {
        fileo << cards[i].getClientUserId() << "," << cards[i].getCardNumber() << ",";
        fileo << cards[i].getCardPin() << "," << cards[i].getFailedAttempts() << ",";
        fileo << (cards[i].getIsBlocked() ? "1" : "0") << "\n";
    }
    fileo.close();
}

void Card::loadcards(const string& fname)
{
    cardCount = 0;
    ifstream filei(fname.c_str());
    if (!filei.is_open())
        return;

    string line, toks[8];
    int tcount;

    while (getline(filei, line))
    {
        if (line.size() == 0)
            continue;

        splitCSV(line, toks, tcount, 8);
        if (tcount < 3)
            continue;

        string uid = toks[0];
        string cardnum = toks[1];
        string pin = toks[2];
        int fails = 0;
        bool blocked = false;

        if (tcount >= 4)
        {
            try { fails = stoi(toks[3]); }
            catch (...) { fails = 0; }
        }

        if (tcount >= 5)
            blocked = strToBool(toks[4]);

        if (cardCount < maxcards)
        {
            cards[cardCount].setClientUserId(uid);
            cards[cardCount].setCardNumber(cardnum);
            cards[cardCount].setCardPin(pin);
            cards[cardCount].setFailedAttempts(fails);
            cards[cardCount].setIsBlocked(blocked);
            ++cardCount;
        }
    }
    filei.close();
}

void Card::listCardsForUser(const string& userLoginId)
{
    cout << "Cards for " << userLoginId << ":\n";
    bool found = false;
    for (int i = 0; i < cardCount; ++i)
    {
        if (cards[i].getClientUserId() == userLoginId)
        {
            found = true;
            cout << "  Card Number: " << cards[i].getCardNumber();
            cout << " | Blocked: " << (cards[i].getIsBlocked() ? "Yes" : "No");
            cout << " | Failed Attempts: " << cards[i].getFailedAttempts() << "\n";
        }
    }
    if (!found)
        cout << "  No cards found for this user.\n";
}

void Transaction::displayTransactionHistory(const string& clientId)
{
    cout << "Transaction History for " << clientId << ":\n";
    bool found = false;
    for (int i = 0; i < transactionCount; ++i)
    {
        if (transactions[i].getClientUserId() == clientId)
        {
            found = true;
            cout << "  Date: " << transactions[i].getTransactionDate();
            cout << " | Type: " << transactions[i].getTransactionype();
            cout << " | Amount: " << transactions[i].getAmount();
            if (transactions[i].getTargetUserId() != "")
                cout << " | To: " << transactions[i].getTargetUserId();
            cout << "\n";
        }
    }
    if (!found)
        cout << "  No transactions found.\n";
}

void UserClient::listuser()
{
    cout << "\n=== USER CLIENTS ===\n";
    for (int i = 0; i < userCount; ++i)
    {
        cout << "ID: " << users[i].getLoginId();
        cout << " |/ Name: " << users[i].getFullName();
        cout << " |/ Balance: " << users[i].getAccountBalance();
        cout << " |/ Approved: " << (users[i].getisApproved() ? "Yes" : "No");
        cout << " |/ Frozen: " << (users[i].getIsFrozen() ? "Yes" : "No") << "\n";
    }
}

void CompanyClient::listcomp()
{
    cout << "\n___ COMPANY CLIENTS ___\n";
    for (int i = 0; i < companyCount; ++i)
    {
        cout << "ID: " << companies[i].getLoginId();
        cout << " |/ Name: " << companies[i].getCompanyName();
        cout << " |/ $Balance$: " << companies[i].getAccountBalance();
        cout << " |/ Approved: " << (companies[i].getIsApprovd() ? "Yes" : "No");
        cout << " |/ Frozen: " << (companies[i].getIsFrozen() ? "Yes" : "No") << "\n";
    }
}

void BankingEmployee::saveadmin(const string& fname)
{
    ofstream fileo(fname.c_str());
    if (!fileo.is_open())
        return;

    for (int i = 0; i < adminCount; ++i)
    {
        fileo << admins[i].getEmployeeId() << ",";
        fileo << admins[i].getPassword() << ",";
        fileo << admins[i].getDesignation() << "\n";
    }
    fileo.close();
}

void BankingEmployee::loadadmin(const string& fname)
{
    adminCount = 0;
    ifstream filei(fname.c_str());
    if (!filei.is_open())
        return;

    string line, toks[6];
    int tcount;

    while (getline(filei, line))
    {
        if (line.size() == 0)
            continue;

        splitCSV(line, toks, tcount, 6);
        if (tcount < 2)
            continue;

        if (adminCount < maxadmin)
        {
            admins[adminCount].setEmployeeId(toks[0]);
            admins[adminCount].setPassword(toks[1]);
            if (tcount >= 3)
                admins[adminCount].setDesignation(toks[2]);
            ++adminCount;
        }
    }
    filei.close();
}

bool BankingEmployee::loginadmin(const string& adminId, const string& password)
{
    for (int i = 0; i < adminCount; ++i)
    {
        if (admins[i].getEmployeeId() == adminId && admins[i].getPassword() == password)
            return true;
    }
    return false;
}

bool BankingEmployee::approveUser(const string& loginId)
{
    int idx = UserClient::findUserByLogin(loginId);
    if (idx == -1)
        return false;

    users[idx].setisApproved(true);

    // Generate random 16-digit card number
    string cardnum = "";
    for (int i = 0; i < 16; ++i)
        cardnum.push_back('0' + (rand() % 10));

    // Get PIN from pending array
    string userPin = "0000";
    for (int i = 0; i < pendingCount; ++i)
    {
        if (pendingUserIds[i] == loginId)
        {
            userPin = userPendingPins[i];
            break;
        }
    }

    // Create card
    if (cardCount < maxcards)
    {
        cards[cardCount].setClientUserId(loginId);
        cards[cardCount].setCardNumber(cardnum);
        cards[cardCount].setCardPin(userPin);
        cards[cardCount].setFailedAttempts(0);
        cards[cardCount].setIsBlocked(false);
        ++cardCount;
    }

    Card::savecards();
    UserClient::saveUsers();
    cout << "User " << loginId << " approved. Card: " << cardnum << "\n";
    return true;
}

bool BankingEmployee::declineuser(const string& loginId)
{
    int idx = UserClient::findUserByLogin(loginId);
    if (idx == -1)
        return false;

    // Remove user by shifting
    for (int i = idx; i < userCount - 1; ++i)
    {
        users[i] = users[i + 1];
    }
    --userCount;

    UserClient::saveUsers();
    cout << "User " << loginId << " declined and removed.\n";
    return true;
}

// HELPER FUNCTIONS FOR LOADING/SAVING ALL FILES
void saveAllFiles()
{
    UserClient::saveUsers();
    CompanyClient::saveCompanies();
    CompanyClient::savecompanyemp();
    Card::savecards();
    Transaction::savetrans();
    BankingEmployee::saveadmin();
}

void loadAllFiles()
{
    UserClient::loadUsers();
    CompanyClient::loadCompanies();
    CompanyClient::loadcompanyemp();
    Card::loadcards();
    Transaction::loadtrans();
    BankingEmployee::loadadmin();
}

// Add this main function to your V1.5.cpp file

int main()
{
    // Allocate dynamic memory for global arrays
    users = new UserClient[maxuser];
    companies = new CompanyClient[maxcomp];
    admins = new BankingEmployee[maxadmin];
    cards = new Card[maxcards];
    transactions = new Transaction[maxtrans];
    empUserIds = new string[maxemp];
    empCompanyIds = new string[maxemp];

    // Load all data from files
    loadAllFiles();

    bool running = true;
    while (running)
    {
        cout << "\n-------------------------------------->\n";
        cout << "     \n       [] PuranaPay []    \n";
        cout << "\n<--------------------------------------\n";
        cout << "1. Login\n";
        cout << "2. Signup\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        int mainChoice;
       /* cin >> mainChoice;*/
        if (!(cin >> mainChoice))
        {
            cout << " Invalid input. Please enter a number.\n";
            cin.clear();                // clears error flag
            cin.ignore(1000, '\n');     //  discards rest of the bad line
            continue;
        }
        if (mainChoice == 3)
        {
            cout << "Thank you for using ABC Bank. Goodbye!\n";
            running = false;
            break;
        }

       
        if (mainChoice == 1)
        {
            cout << "\n___ LOGIN ___\n";
            cout << "1. Banking Employee\n";
            cout << "2. User Client\n";
            cout << "3. Company Client\n";
            cout << "Enter your choice: ";

            int loginType;
            cin >> loginType;

          
            if (loginType == 1)
            {
                string empId, empPass;
                cout << "Enter Employee ID: ";
                cin >> empId;
                cout << "Enter Password: ";
                cin >> empPass;

                if (BankingEmployee::loginadmin(empId, empPass))
                {
                    cout << "\nLogin Successful! Welcome, Employee " << empId << " ***\n";

                    bool employeeSession = true;
                    while (employeeSession)
                    {
                        cout << "\n____ BANKING EMPLOYEE MENU ____\n";
                        cout << "1. View All Bank Clients\n";
                        cout << "2. Approve/Reject New Account Requests\n";
                        cout << "3. View Transaction History\n";
                        cout << "4. Freeze/Unfreeze Account\n";
                        cout << "5. Close Account\n";
                        cout << "6. View Cards for a User\n";
                        cout << "7. Logout\n";
                        cout << "Enter your choice: ";

                        int empChoice;
                        cin >> empChoice;

                        if (empChoice == 1)
                        {
                            cout << "\n1. View User Clients\n2. View Company Clients\n";
                            cout << "Enter your choice: ";
                            int viewChoice;
                            cin >> viewChoice;

                            if (viewChoice == 1)
                                UserClient::listuser();
                            else if (viewChoice == 2)
                                CompanyClient::listcomp();
                        }
                        else if (empChoice == 2)
                        {
                            cout << "\n____ Pending Account Requests ____\n";
                            cout << "User Clients:\n";
                            bool foundPending = false;
                            for (int i = 0; i < userCount; i++)
                            {
                                if (!users[i].getisApproved())
                                {
                                    foundPending = true;
                                    cout << "  ID: " << users[i].getLoginId()
                                        << " | Name: " << users[i].getFullName() << "\n";
                                }
                            }
                            if (!foundPending)
                                cout << "  No pending user requests.\n";

                            cout << "\nEnter 'User ID' to approve/reject  or 'skip' to skip: ";
                            string userId;
                            cin >> userId;

                            if (userId != "skip")
                            {
                                cout << "1. Approve\n2. Reject\nChoice: ";
                                int approveChoice;
                                cin >> approveChoice;

                                if (approveChoice == 1)
                                {
                                    if (BankingEmployee::approveUser(userId))
                                        cout << "User approved successfully!\n";
                                    else
                                        cout << "User not found.\n";
                                }
                                else if (approveChoice == 2)
                                {
                                    if (BankingEmployee::declineuser(userId))
                                        cout << "User rejected successfully!\n";
                                    else
                                        cout << "User not found.\n";
                                }
                            }
                        }
                        else if (empChoice == 3)
                        {
                            cout << "Enter Client ID: ";
                            string clientId;
                            cin >> clientId;
                            Transaction::displayTransactionHistory(clientId);
                        }
                        else if (empChoice == 4)
                        {
                            cout << "Enter Account ID: ";
                            string accId;
                            cin >> accId;
                            cout << "1. Freeze\n2. Unfreeze\nChoice: ";
                            int freezeChoice;
                            cin >> freezeChoice;

                            int uidx = UserClient::findUserByLogin(accId);
                            int cidx = CompanyClient::findCompanyById(accId);

                            if (uidx != -1)
                            {
                                users[uidx].setIsFrozen(freezeChoice == 1);
                                UserClient::saveUsers();
                                cout << "User account " << (freezeChoice == 1 ? "frozen" : "unfrozen") << "!\n";
                            }
                            else if (cidx != -1)
                            {
                                companies[cidx].setIsFrozen(freezeChoice == 1);
                                CompanyClient::saveCompanies();
                                cout << "Company account " << (freezeChoice == 1 ? "frozen" : "unfrozen") << "!\n";
                            }
                            else
                            {
                                cout << "Account not found.\n";
                            }
                        }
                        else if (empChoice == 5)
                        {
                            cout << "Enter Account ID to close: ";
                            string accId;
                            cin >> accId;

                            if (BankingEmployee::declineuser(accId))
                                cout << "Account closed successfully\n";
                            else
                                cout << "Account not found or already closed\n";
                        }
                        else if (empChoice == 6)
                        {
                            cout << "Enter User ID: ";
                            string userId;
                            cin >> userId;
                            Card::listCardsForUser(userId);
                        }
                        else if (empChoice == 7)
                        {
                            cout << "Logging out...\n";
                            employeeSession = false;
                        }
                    }
                }
                else
                {
                    cout << "Invalid credentials!\n";
                }
            }
           
            else if (loginType == 2)
            {
                string userId, userPass;
                cout << "Enter User ID: ";
                cin >> userId;
                cout << "Enter Password: ";
                cin >> userPass;

                int userIdx = UserClient::findUserByLogin(userId);
                if (userIdx != -1 && users[userIdx].getPassword() == userPass)
                {
                    if (!users[userIdx].getisApproved())
                    {
                        cout << "Your account is pending approval.\n";
                        continue;
                    }
                    if (users[userIdx].getIsFrozen())
                    {
                        cout << "Your account is frozen. Contact the bank.\n";
                        continue;
                    }

                    cout << "\nLogin Successful! Welcome, " << users[userIdx].getFullName() << " ***\n";

                    bool userSession = true;
                    while (userSession)
                    {
                        cout << "\n___USER CLIENT MENU ___\n";
                        cout << "1. Deposit Funds\n";
                        cout << "2. Withdraw Funds\n";
                        cout << "3. Transfer Funds\n";
                        cout << "4. View Balance\n";
                        cout << "5. View Transaction History\n";
                        cout << "6. View My Cards\n";
                        cout << "7. Logout\n";
                        cout << "Enter your choice: ";

                        int userChoice;
                        cin >> userChoice;

                        if (userChoice == 1)
                        {
                            double amount;
                            cout << "Enter amount to deposit: ";
                            cin >> amount;

                            if (UserClient::deposit(userId, amount))
                                cout << "Deposit successful! New balance: " << users[userIdx].getAccountBalance() << "\n";
                            else
                                cout << "Deposit failed.\n";
                        }
                        else if (userChoice == 2)
                        {
                            cout << "Enter card number: ";
                            string cardNum;
                            cin >> cardNum;
                            cout << "Enter card PIN: ";
                            string pin;
                            cin >> pin;
                            cout << "Enter amount to withdraw: ";
                            double amount;
                            cin >> amount;

                            if (UserClient::cardwithdraw(cardNum, pin, amount))
                                cout << "Withdrawal successful!\n";
                            else
                                cout << "Withdrawal failed.\n";
                        }
                        else if (userChoice == 3)
                        {
                            cout << "Enter card number: ";
                            string cardNum;
                            cin >> cardNum;
                            cout << "Enter card PIN: ";
                            string pin;
                            cin >> pin;
                            cout << "Enter recipient User ID: ";
                            string recipientId;
                            cin >> recipientId;
                            cout << "Enter amount to transfer: ";
                            double amount;
                            cin >> amount;

                            if (UserClient::transferTo(cardNum, pin, recipientId, amount))
                                cout << "Transfer successful!\n";
                            else
                                cout << "Transfer failed.\n";
                        }
                        else if (userChoice == 4)
                        {
                            cout << "\n--- Account Balance ---\n";
                            cout << "Name: " << users[userIdx].getFullName() << "\n";
                            cout << "ID: " << users[userIdx].getLoginId() << "\n";
                            cout << "Balance: PKR " << users[userIdx].getAccountBalance() << "\n";
                        }
                        else if (userChoice == 5)
                        {
                            Transaction::displayTransactionHistory(userId);
                        }
                        else if (userChoice == 6)
                        {
                            Card::listCardsForUser(userId);
                        }
                        else if (userChoice == 7)
                        {
                            cout << "Logging out...\n";
                            userSession = false;
                        }
                    }
                }
                else
                {
                    cout << "Invalid credentials!\n";
                }
            }
            else if (loginType == 3)
            {
                string compId, compPass;
                cout << "Enter Company ID: ";
                cin >> compId;
                cout << "Enter Password: ";
                cin >> compPass;

                int compIdx = CompanyClient::findCompanyById(compId);
                if (compIdx != -1 && companies[compIdx].getPassword() == compPass)
                {
                    if (!companies[compIdx].getIsApprovd())
                    {
                        cout << "Your company account is pending approval.\n";
                        continue;
                    }
                    if (companies[compIdx].getIsFrozen())
                    {
                        cout << "Your company account is frozen. Contact the bank.\n";
                        continue;
                    }

                    cout << "\n*** Login Successful! Welcome, " << companies[compIdx].getCompanyName() << " ***\n";

                    bool companySession = true;
                    while (companySession)
                    {
                        cout << "\n--- COMPANY CLIENT MENU ---\n";
                        cout << "1. Deposit Funds\n";
                        cout << "2. Withdraw Funds\n";
                        cout << "3. Transfer Funds to User\n";
                        cout << "4. View Balance\n";
                        cout << "5. View Transaction History\n";
                        cout << "6. Request Loan\n";
                        cout << "7. Logout\n";
                        cout << "Enter your choice: ";

                        int compChoice;
                        cin >> compChoice;

                        if (compChoice == 1)
                        {
                            double amount;
                            cout << "Enter amount to deposit: ";
                            cin >> amount;

                            if (UserClient::deposit(compId, amount))
                                cout << "Deposit successful! New balance: " << companies[compIdx].getAccountBalance() << "\n";
                            else
                                cout << "Deposit failed.\n";
                        }
                        else if (compChoice == 2)
                        {
                            double amount;
                            cout << "Enter amount to withdraw: ";
                            cin >> amount;

                            if (amount <= 0.0)
                            {
                                cout << "Invalid amount.\n";
                                continue;
                            }

                            if (companies[compIdx].getIsFrozen())
                            {
                                cout << "Account is frozen.\n";
                                continue;
                            }

                            if (!companies[compIdx].checkDailyLimit(amount))
                            {
                                cout << "Daily withdrawal limit exceeded.\n";
                                continue;
                            }

                            if (amount > companies[compIdx].getAccountBalance())
                            {
                                cout << "Insufficient balance.\n";
                                continue;
                            }

                            companies[compIdx].setAccountBalance(companies[compIdx].getAccountBalance() - amount);
                            Transaction::recordtrans(todayDate(), compId, amount, "Withdraw");
                            CompanyClient::saveCompanies();
                            cout << "Withdrawal successful!\n";
                        }
                        else if (compChoice == 3)
                        {
                            cout << "Enter recipient User ID: ";
                            string recipientId;
                            cin >> recipientId;
                            cout << "Enter amount to transfer: ";
                            double amount;
                            cin >> amount;

                            int toIdx = UserClient::findUserByLogin(recipientId);
                            if (toIdx == -1)
                            {
                                cout << "Recipient not found.\n";
                                continue;
                            }

                            if (amount <= 0.0)
                            {
                                cout << "Invalid amount.\n";
                                continue;
                            }

                            if (companies[compIdx].getIsFrozen())
                            {
                                cout << "Account is frozen.\n";
                                continue;
                            }

                            if (!companies[compIdx].checkDailyLimit(amount))
                            {
                                cout << "Daily limit exceeded.\n";
                                continue;
                            }

                            if (amount > companies[compIdx].getAccountBalance())
                            {
                                cout << "Insufficient balance.\n";
                                continue;
                            }

                            companies[compIdx].setAccountBalance(companies[compIdx].getAccountBalance() - amount);
                            users[toIdx].setAccountBalance(users[toIdx].getAccountBalance() + amount);
                            Transaction::recordtrans(todayDate(), compId, amount, "Transfer", recipientId);
                            CompanyClient::saveCompanies();
                            UserClient::saveUsers();
                            cout << "Transfer successful!\n";
                        }
                        else if (compChoice == 4)
                        {
                            cout << "\n--- Company Account Balance ---\n";
                            cout << "Company: " << companies[compIdx].getCompanyName() << "\n";
                            cout << "ID: " << companies[compIdx].getLoginId() << "\n";
                            cout << "Balance: PKR " << companies[compIdx].getAccountBalance() << "\n";
                        }
                        else if (compChoice == 5)
                        {
                            Transaction::displayTransactionHistory(compId);
                        }
                        else if (compChoice == 6)
                        {
                            double loanAmount;
                            cout << "Enter loan amount: ";
                            cin >> loanAmount;
                            cout << "Loan request submitted for approval. Check with banking employee.\n";
                            // Note: Loan approval logic should be implemented in banking employee section
                        }
                        else if (compChoice == 7)
                        {
                            cout << "Logging out...\n";
                            companySession = false;
                        }
                    }
                }
                else
                {
                    cout << "Invalid credentials!\n";
                }
            }
        }

        else if (mainChoice == 2)
        {
            cout << "\n_____SIGN UP ______\n";
            cout << "1- User Client-1\n";
            cout << "2- Company Client-2\n";
            cout << "Enter your choice: ";

            int signupType;
            cin >> signupType;

            // USER CLIENT SIGNUP 
            if (signupType == 1)
            {
                string name, address, phone, cnic, loginId, password, pin;
                double withdrawalLimit;

                cin.ignore();
                cout << "Enter Full Name: ";
                getline(cin, name);
                cout << "Enter Address: ";
                getline(cin, address);
                cout << "Enter Phone (11 digits, starting with 03): ";
                cin >> phone;
                cout << "Enter CNIC (13 digits): ";
                cin >> cnic;
                cout << "Enter Login ID: ";
                cin >> loginId;
                cout << "Enter Password: ";
                cin >> password;
                cout << "Enter Estimated Daily Withdrawal Limit (max 500000): ";
                cin >> withdrawalLimit;
                cout << "Enter 4-digit PIN for card: ";
                cin >> pin;

                // Validation
                if (phone.length() != 11 || !isAllDigits(phone) || phone.substr(0, 2) != "03")
                {
                    cout << "Invalid phone number format.\n";
                    continue;
                }
                if (cnic.length() != 13 || !isAllDigits(cnic))
                {
                    cout << "Invalid CNIC format.\n";
                    continue;
                }
                if (pin.length() != 4 || !isAllDigits(pin))
                {
                    cout << "PIN must be exactly 4 digits.\n";
                    continue;
                }
                if (withdrawalLimit <= 0 || withdrawalLimit > 500000)
                {
                    cout << "Withdrawal limit must be between 1 and 500,000 PKR.\n";
                    continue;
                }
                if (UserClient::findUserByLogin(loginId) != -1 || CompanyClient::findCompanyById(loginId) != -1)
                {
                    cout << "Login ID already exists.\n";
                    continue;
                }
                if (userCount >= maxuser)
                {
                    cout << "User limit reached.\n";
                    continue;
                }

                // Assign account type
                AccountType* accType;
                if (withdrawalLimit <= 100000)
                    accType = new Bronze(withdrawalLimit, "Bronze");
                else
                    accType = new Gold(withdrawalLimit, "Gold");

                // Create user
                users[userCount].setFullName(name);
                users[userCount].setAddress(address);
                users[userCount].setPhone(phone);
                users[userCount].setCnic(cnic);
                users[userCount].setLoginId(loginId);
                users[userCount].setPassword(password);
                users[userCount].setAccountBalance(0.0);
                users[userCount].setaccountType(accType);
                users[userCount].setisApproved(false);
                users[userCount].setIsFrozen(false);

                // Store PIN for later card creation
                pendingUserIds[pendingCount] = loginId;
                userPendingPins[pendingCount] = pin;
                pendingCount++;

                userCount++;
                UserClient::saveUsers();

                cout << "\n  Signup Successful!  \n";
                cout << "Your account is pending approval by a banking employee\n";
                cout << "You will receive your card details once approved.\n";
            }
           
            else if (signupType == 2)
            {
                string companyName, address, taxNumber, loginId, password;
                double withdrawalLimit;

                cin.ignore();
                cout << "Enter Company Name: ";
                getline(cin, companyName);
                cout << "Enter Company Address: ";
                getline(cin, address);
                cout << "Enter Tax Number: ";
                cin >> taxNumber;
                cout << "Enter Login ID: ";
                cin >> loginId;
                cout << "Enter Password: ";
                cin >> password;
                cout << "Enter Estimated Daily Withdrawal Limit (max 20000000): ";
                cin >> withdrawalLimit;

                // Validation
                if (withdrawalLimit <= 0 || withdrawalLimit > 20000000)
                {
                    cout << "Withdrawal limit must be between 1 and 20,000,000 PKR.\n";
                    continue;
                }
                if (UserClient::findUserByLogin(loginId) != -1 || CompanyClient::findCompanyById(loginId) != -1)
                {
                    cout << "Login ID already exists.\n";
                    continue;
                }
                if (companyCount >= maxcomp)
                {
                    cout << "Company limit reached.\n";
                    continue;
                }

                // Assign account type (Business only for companies)
                AccountType* accType = new Business(withdrawalLimit, "Business");

                // Create company
                companies[companyCount].setLoginId(loginId);
                companies[companyCount].setCompanyName(companyName);
                companies[companyCount].setAddress(address);
                companies[companyCount].setTaxNumber(taxNumber);
                companies[companyCount].setPassword(password);
                companies[companyCount].setAccountBalance(0.0);
                companies[companyCount].setAccountType(accType);
                companies[companyCount].setIsApprovd(true); // Auto-approve for now
                companies[companyCount].setIsFrozen(false);

                companyCount++;
                CompanyClient::saveCompanies();

                cout << "\n*** Company Signup Successful! ***\n";
                cout << "Your company account has been created.\n";
            }
        }
    }

    // Save all data before exit
    saveAllFiles();

    // Clean up dynamic memory
    delete[] users;
    delete[] companies;
    delete[] admins;
    delete[] cards;
    delete[] transactions;
    delete[] empUserIds;
    delete[] empCompanyIds;

    return 0;
}