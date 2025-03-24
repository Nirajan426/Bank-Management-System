# Bank Management System
A console-based banking application built in C.

## 📌 Overview
This project is a Bank Management System that simulates core banking operations like account creation, deposits, withdrawals, and fund transfers. It features a menu-driven interface, input validation, and transaction logging for secure banking operations.

## ✨ Features

### 🔐 Account Management
- ✅ **Create a new bank account** (with validation for username, password, email, etc.)
- 🔑 **Secure login** (Account Number + Username + Password)
- 👤 **View & Modify Profile** (Update password, email, phone number)

### 💰 Banking Operations
- 💵 **Deposit Money** (Add funds to account)
- 💸 **Withdraw Money** (Check balance before withdrawal)
- 🔄 **Transfer Money** (Send money to another account)
- 📜 **View Transaction History** (Check deposits, withdrawals, transfers)

### 🛡️ Security & Validation
- 🔒 **Password encryption** (hidden input with `*` masking)
- 📝 **Input validation** (Email, phone number, date format, password strength)
- 📂 **File-based storage** (User details & transactions stored in `.txt` files)

## 🛠️ How to Run

### Prerequisites
- A C compiler (e.g., GCC, Clang)
- Windows OS (uses `<windows.h>` for `Sleep()` and `system("cls")`)

### Compilation & Execution

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/bank-management-system.git
    cd bank-management-system
    ```

2. Compile the code:
    ```bash
    gcc bank_system.c -o bank_system
    ```

3. Run the program:
    ```bash
    ./bank_system
    ```

## 📂 File Structure
- `userdetail.txt` → Stores user account details
- `transaction_log.txt` → Records all transactions

## 📜 Code Structure
- `struct User` → Stores account details (username, password, balance, etc.)
- `main()` → Handles login, account creation, and main menu navigation
- Banking Functions → `depositMoney()`, `withdrawMoney()`, `transferMoney()`
- Validation Functions → `isValidEmail()`, `isValidPassword()`, etc.
- File Handling → `updateUserBalance()`, `logTransaction()`

## 🎥 Demo
(You can add GIFs/screenshots of the program running)

**Login Screen**
