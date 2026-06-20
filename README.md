# OOP Banking Management System

A comprehensive, console-based Banking Management System implemented in C++ utilizing core Object-Oriented Programming (OOP) paradigms. This project was developed as part of the Object-Oriented Programming (CS) course at FAST-NUCES[cite: 1].

## 🏛️ Project Architecture & OOP Concepts
This system completely avoids hardcoding by leveraging advanced OOP relationships[cite: 1]:
* **Inheritance & Polymorphism:** Utilized to define Account tiers (`Bronze`, `Gold`, `Business`) dynamically restricting daily withdrawal limits depending on the client type[cite: 1].
* **Composition & Aggregation:** Modeled complex real-world relationships such as a `Company Client` containing multiple `User Client` employees, and accounts containing multiple credit `Cards`[cite: 1].
* **Encapsulation:** All stakeholder profiles and financial entities securely restrict direct data mutation through getters, setters, and class methods[cite: 1].

---

## 👥 Stakeholder Features

### 1. User Client (Individual Accounts)
* **Account Tiers:** Automated tier assignment (`Bronze` or `Gold`) depending on the customer's estimated daily withdrawal limit[cite: 1].
* **Card Management:** Generates a unique 16-digit card number and PIN upon manager approval[cite: 1]. Supports multiple cards per user[cite: 1].
* **Banking Operations:** Perform secure deposits, withdrawals, fund transfers, and view transaction history[cite: 1]. 
* **Security Guardrails:** Validates pin entries (3 failed attempts marks the account as fraudulent and freezes it)[cite: 1].

### 2. Company Client (Shared Accounts)
* **Corporate Management:** Authorized access for a Company's CEO to open shared accounts (`Gold` or `Business` tiers)[cite: 1].
* **Employee Access:** Maps corporate accounts to existing individual user accounts, giving employees appropriate shared operational access[cite: 1].
* **Loan Requests:** Allows corporate accounts to submit credit/loan requests to the bank administration[cite: 1].

### 3. Banking Employee (System Admin)
* Full control to approve/reject new account applications and loan requests[cite: 1].
* Ability to audit logs, view specific transaction histories, and freeze or close high-risk/fraudulent accounts[cite: 1].

---

## 💾 File Handling & Data Persistence
The system features flat-file data persistence to maintain systemic states across sessions using the following structures[cite: 1]:
* `users.txt` - Stores user credentials, metadata, and balances[cite: 1].
* `companies.txt` & `companies_employees.txt` - Tracks corporate groups and employee relationships[cite: 1].
* `admin.txt` - Verification file for bank staff logins[cite: 1].
* `transactions.txt` - Audit trail logging date, Client ID, transaction amount, type, and target recipient details[cite: 1].
* `cards.txt` - Links client records to generated card assets and security PINs[cite: 1].

---

## 🛠️ Tech Stack
* **Language:** C++ (Standard ISO/IEC 14882)
* **File I/O:** `fstream` standard library for relational text-database emulation[cite: 1]
* **Development Environment:** MinGW GCC Compiler / VS Code

---

## 💻 Setup and Run

1. Clone this repository to your local machine:
```bash
   git clone [https://github.com/your-username/oop-banking-management-system.git](https://github.com/your-username/oop-banking-management-system.git)
