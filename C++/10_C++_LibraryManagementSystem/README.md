# C++ Library Management System

This repository contains the implementation of a simple **Library Management System** in C++ using Object-Oriented Programming (OOP). The project defines two classes: `Book` and `Author`, following the given specifications.

## 📂 Project Structure

- `Book.h` - Header file defining the `Book` class.
- `Author.h` - Header file defining the `Author` class.
- `Book.cpp` - Implementation file for the `Book` class.
- `Author.cpp` - Implementation file for the `Author` class.
- `main.cpp` - Test file to demonstrate the functionality of the system.

## 📌 Class Specifications

### **Book**
- **Attributes**:
  - `name` (string)
  - `author` (Author)
  - `value` (double)
  - `stockQuantity` (int)
- **Methods**:
  - Constructor
  - `setName()`, `getName()`
  - `setAuthor()`, `getAuthor()`
  - `setValue()`, `getValue()`
  - `setStockQuantity()`, `getStockQuantity()`

### **Author**
- **Attributes**:
  - `name` (string)
  - `email` (string)
  - `gender` (char)
- **Methods**:
  - `setName()`, `getName()`

## 🚀 How to Compile and Run
To compile and execute the program, use the following commands in a terminal:

```sh
g++ -o library main.cpp Book.cpp Author.cpp
./library