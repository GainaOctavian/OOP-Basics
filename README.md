
# Organization Management System - C++ Project

**Project by Aurelian-Octavian Găină**  
*Object-Oriented Programming (OOP) Project in C++*

## 📊 Overview

This project is a C++ application designed to manage an organization. It demonstrates advanced Object-Oriented Programming (OOP) concepts such as classes, inheritance, polymorphism, and encapsulation. The system handles various entities like employees, suppliers, and investors, supporting data persistence through file operations.

## 🚀 Features

- **Employee Management:** Add, modify, and display employee details.
- **Departmental Hierarchy:** Organize employees by departments and roles.
- **Supplier & Investor Tracking:** Manage suppliers and investors with relevant data.
- **File I/O:** Data persistence using text and binary files.
- **Dynamic Memory Management:** Effective use of pointers and dynamic allocation.

## 🛠️ Technologies Used

- **C++** (Core Language)
- **Standard Template Library (STL):** Vectors, maps, sets for efficient data management.
- **File Handling:** For reading and writing to text and binary files.

## 📂 Project Structure

```
OOP-Basics/
├── proiect.sln                # Visual Studio solution file
├── proiect/
│   ├── Source.cpp             # Main C++ source code
│   ├── angajati.txt           # Employee data
│   ├── furnizori.txt          # Supplier data
│   ├── investitori.txt        # Investor data
│   ├── produse.bin            # Product data in binary format
│   ├── furnizori.bin          # Supplier data in binary format
│   └── investitori.bin        # Investor data in binary format
└── Debug/                     # Compiled binaries
```

## ⚙️ How to Run

### Prerequisites
- **C++ Compiler (G++, MSVC, etc.)**
- **Visual Studio** (optional) for project management

### Running the Application

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/GainaOctavian/Proiect_POO.git
   cd Proiect_POO
   ```

2. **Open in Visual Studio:**
   - Open `proiect.sln` in Visual Studio.
   - Press `F5` to build and run the project.

   **OR** Compile via command line:
   ```bash
   g++ -o proiect proiect/Source.cpp
   ./proiect
   ```

## 📈 Key Functionalities

- Adding and managing employee information
- Displaying organizational hierarchy
- Managing suppliers and investors
- Reading and writing data to files
- Calculating salaries, bonuses, and reports

## 📈 Future Improvements

- Implement a GUI for better user interaction
- Add database integration for scalable data management
- Improve data validation and error handling

## 🙌 Credits

This project was developed by Aurelian-Octavian Găină as part of the Object-Oriented Programming (OOP) course to demonstrate practical application of OOP principles in C++.
