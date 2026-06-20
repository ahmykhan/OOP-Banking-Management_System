# OOP Banking Management System

A comprehensive, console-based Banking Management System implemented in C++ utilizing core Object-Oriented Programming (OOP) paradigms. This project was developed as part of the Object-Oriented Programming course at FAST-NUCES.

## 🏛️ Project Architecture & OOP Concepts
This system completely avoids hardcoding by leveraging advanced OOP relationships:
* **Inheritance & Polymorphism:** Utilized to define Account tiers (`Bronze`, `Gold`, `Business`) dynamically restricting daily withdrawal limits depending on the client type.
* **Composition & Aggregation:** Modeled complex real-world relationships such as a `Company Client` containing multiple `User Client` employees, and accounts containing multiple credit `Cards`.
* **Encapsulation:** All stakeholder profiles and financial entities securely restrict direct data mutation through getters, setters, and class methods.

---

## 👥 Stakeholder Features

### 1. User Client (Individual Accounts)
* **Account Tiers:** Automated tier assignment (`Bronze` or `Gold`) depending on the customer's estimated daily withdrawal limit.
* **Card Management:** Generates a unique 16-digit card number and PIN upon manager approval. Supports multiple cards per user.
* **Banking Operations:** Perform secure deposits, withdrawals, fund transfers, and view transaction history. 
* **Security Guardrails:** Validates pin entries (3 failed attempts marks the account as fraudulent and freezes it).

### 2. Company Client (Shared Accounts)
* **Corporate Management:** Authorized access for a Company's CEO to open shared accounts (`Gold` or `Business` tiers).
* **Employee Access:** Maps corporate accounts to existing individual user accounts, giving employees appropriate shared operational access.
* **Loan Requests:** Allows corporate accounts to submit credit/loan requests to the bank administration.

### 3. Banking Employee (System Admin)
* Full control to approve/reject new account applications and loan requests.
* Ability to audit logs, view specific transaction histories, and freeze or close high-risk/fraudulent accounts.

---

## 💾 File Handling & Data Persistence
The system features flat-file data persistence to maintain systemic states across sessions using the following structures:
* `users.txt` - Stores user credentials, metadata, and balances.
* `companies.txt` & `companies_employees.txt` - Tracks corporate groups and employee relationships.
* `admin.txt` - Verification file for bank staff logins.
* `transactions.txt` - Audit trail logging date, Client ID, transaction amount, type, and target recipient details.
* `cards.txt` - Links client records to generated card assets and security PINs.

---

## 🛠️ Tech Stack
* **Language:** C++
* **File I/O:** `fstream` standard library for relational text-database emulation
* **Development Tools:** MinGW GCC Compiler / Dev-C++ / VS Code

---

## 💻 How to Run
1. Open the project folder in your preferred C++ IDE (like Dev-C++, Visual Studio, or VS Code).
2. Make sure the code file and all the required `.txt` files are in the same folder.
3. Click the **Run** or **Compile and Run** button in your IDE to launch the application.
