# Library Management System

A comprehensive **C++ Library Management System** designed to streamline book borrowing, user management, and fine calculations. This project provides an efficient way to handle different user roles, ensuring smooth library operations with a structured permission system.

---

## 🔹 Key Features

✔️ **User Authentication** – Secure login for students, faculty, and librarians.  
✔️ **Book Management** – Easily add, remove, and view books in the system.  
✔️ **Borrow & Return System** – Track active loans, set due dates, and enforce borrowing limits.  
✔️ **Fine Calculation** – Automatic fine computation for overdue books.  
✔️ **Role-Based Access Control** – Define user-specific permissions for students, faculty, and librarians.  
✔️ **Data Persistence** – Store and retrieve book and user records from files.  
✔️ **C++ Object-Oriented Design** – Encapsulated logic for enhanced maintainability.

---

## 📂 Project Structure

```
library_management_system/
├── src/        # Source Code
│   ├── main.cpp
│   ├── User.cpp
│   ├── Book.cpp
│   ├── Account.cpp
│   ├── Student.cpp
│   ├── Faculty.cpp
│   ├── Librarian.cpp
│   └── Library.cpp
│
├── include/    # Header Files
│   ├── User.h
│   ├── Book.h
│   ├── Account.h
│   ├── Student.h
│   ├── Faculty.h
│   ├── Librarian.h
│   └── Library.h
│
├── data/       # Data Storage
│   ├── books.txt
│   └── users.txt
│
├── build/      # Compiled Files
├── CMakeLists.txt  # CMake Configuration
└── README.md       # Project Documentation
```

---

## 🔧 Prerequisites

To set up and run this project, ensure you have the following installed:

- **C++ Compiler** (e.g., MinGW-w64 for Windows, g++ for Linux/macOS)
- **CMake (v3.10 or newer)**
- **Windows/Linux Operating System** (Tested on Windows)

---

## 🏗️ Installation & Compilation Guide

Follow these steps to set up and run the system:

### 1️⃣ Clone the Repository

```sh
git clone https://github.com/anishsahu10/library_management_system.git
cd library_management_system
```

### 2️⃣ Build the Project

Create a build directory and generate the build files:

```sh
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

### 3️⃣ Run the Program

```sh
./lms.exe  # On Windows
./lms      # On Linux/macOS
```

---

## 🔑 Default Login Credentials

| Role          | IDs | Passwords                                   |
| ------------- | --- | ------------------------------------------- |
| **Student**   | 1-5 | pass111, pass222, pass333, pass444, pass555 |
| **Faculty**   | 6-8 | pass666, pass777, pass888                   |
| **Librarian** | 9   | pass999                                     |

---

## 👥 User Roles & Permissions

Each user type has specific privileges within the system:

### 🎓 Student

- View available books
- Borrow up to **3 books** at a time
- Return borrowed books
- Check loan details & fines
- Pay outstanding fines

### 🏛 Faculty

- View books
- Borrow up to **5 books**
- Return borrowed books
- Check current loans (No fines applicable)

### 📚 Librarian

- Add new books & users
- Remove books & users
- Manage the book catalog
- View all transactions
- Oversee the library system

---

## ⚙️ Technical Implementation

- **Language:** C++17
- **Build System:** CMake
- **Data Handling:** File-based persistence
- **Design:** Object-Oriented Programming (OOP)
- **Error Handling:** Robust exception handling
- **Time Management:** Calculates due dates & penalties dynamically

---

## 👨‍💻 Author

👨‍💻 Created by: **Anish Sahu**
🏫 Roll Number: **220148**
📅 Published: **March 10, 2025**

---

## 🎯 Future Enhancements

🔹 Implement a **Graphical User Interface (GUI)** using Qt or GTK.  
🔹 Improve **search and filter** functionality for book retrieval.  
🔹 Introduce a **reservation system** for books.  
🔹 Enhance **database integration** for scalability.
