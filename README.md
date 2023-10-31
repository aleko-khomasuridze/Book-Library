# Library Management System

This C++ program is a simple library management system that allows you to manage a collection of books. It provides functionality for adding, removing, and searching for books in a library. Additionally, it includes custom exception classes for handling specific book-related errors.

## Table of Contents
- [Features](#features)
- [Prerequisites](#prerequisites)
- [How to Use](#how-to-use)
- [Code Explanation](#code-explanation)
- [License](#license)

## Features
- Add books to the library, with ISBN validation to prevent duplicates.
- Remove books from the library.
- Search for books by their unique ID.
- Custom exception classes for handling errors:
  - `BookNotFoundException` for when a book is not found.
  - `ExistingBookISBNException` for when a book with the same ISBN already exists.

## Prerequisites
- This program is written in C++. You'll need a C++ compiler to build and run it. If you don't have one installed, you can use a popular compiler like [g++](https://gcc.gnu.org/).

## How to Use
1. Clone this repository or download the source code.
2. Open a terminal and navigate to the directory containing the source code.
3. Compile the program using a C++ compiler. For example, using g++, you can run:
   ```sh
   g++ library_management.cpp -o library_management
