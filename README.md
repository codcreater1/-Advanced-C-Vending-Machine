🥤 Advanced C++ Vending Machine

Single-file, menu-based, admin-panel supported vending machine system (C++17).

This project is an advanced vending machine simulation featuring user mode, admin panel, change calculation, stock management, and dynamic item add/remove functionality.

🚀 Features
👤 User Mode

View available products

Purchase items

Insufficient funds check

Automatic change calculation

Stock availability check (“Out of stock” warning)

🔐 Admin Mode

Default password: admin123

Add new items

Remove existing items

Update item stock and price

View detailed item list

Logs all admin actions

💰 Payment & Change System

Users pay in TL

Internally calculates in cents to avoid floating point errors

Insufficient funds are blocked

Automatic change returned

🛠️ Technical Details

Single source file (main.cpp)

Standard C++ (C++17)

STL containers: vector, string

Clean & structured menu system

Object-Oriented design

File-based persistent storage (items.txt)

Log file (log.txt) for transactions and admin actions

📦 Build & Run
Linux / macOS
g++ main.cpp -o vending -std=c++17
./vending

Windows (MinGW)
g++ main.cpp -o vending.exe -std=c++17
vending.exe

📁 Project Structure
/project
 ├── main.cpp   ← single-file C++ source code
 ├── items.txt  ← automatically created, stores products
 └── log.txt    ← automatically created, logs transactions

🧪 Example User Flow

Menu:

=== Vending Machine ===
1) User Mode
2) Admin Mode
3) Exit


User Mode:

Select item: 2
Price: 4.50 TL
Insert money: 5
Purchased: Cola
Change: 0.50 TL


Admin Mode:

Password: ****
1) Add item
2) Remove item
3) Update item
4) Add stock
5) List items
6) Exit admin
