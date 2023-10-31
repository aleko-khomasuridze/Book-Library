#include <iostream>
#include <string>
#include <exception>
#include <vector>

using namespace std;

/*
    Library Management System

    This C++ program implements a simple library management system. It allows you to manage a collection of books,
    providing features such as adding, removing, and searching for books in a library. Custom exception classes are
    included for handling specific book-related errors.

    Table of Contents:
    - Features
    - Prerequisites
    - How to Use
    - Code Explanation

    Features:
    - Add books to the library, with ISBN validation to prevent duplicates.
    - Remove books from the library.
    - Search for books by their unique ID.
    - Custom exception classes for handling errors:
        - `BookNotFoundException` for when a book is not found.
        - `ExistingBookISBNException` for when a book with the same ISBN already exists.

    Prerequisites:
    - This program is written in C++. You'll need a C++ compiler to build and run it. If you don't have one installed,
      you can use a popular compiler like g++ (https://gcc.gnu.org/).

    How to Use:
    1. Clone this repository or download the source code.
    2. Open a terminal and navigate to the directory containing the source code.
    3. Compile the program using a C++ compiler. For example, using g++, you can run:
       ```
       g++ library_management.cpp -o library_management
       ```
    4. Run the compiled program:
       ```
       ./library_management
       ```
    5. Follow the on-screen instructions to add, remove, and search for books.

    Code Explanation:
    - The C++ code is structured into classes: `Book`, `Library`, and custom exception classes.
    - `Book` class represents a book and includes attributes like title, author, ID, and ISBN.
    - `Library` class manages a collection of books and provides methods to interact with them.
    - Custom exception classes `BookNotFoundException` and `ExistingBookISBNException` handle specific error cases.
    - In the `main()` function, you can see an example of how to use the library management system with error handling.

    @author -> Aleko Khomasuridze
    @date -> October 31, 2023
*/


// Abstract base class for custom exception messages
class IBookExceptions {
    virtual string getMsg() = 0;
};

// Exception for when a book is not found in the library
class BookNotFoundException : public exception, public IBookExceptions {
private:
    string msg;  // Custom error message
    int id;      // ID of the book that was not found
public:
    BookNotFoundException(const char* msg, int id) : exception(msg) {
        this->id = id;
        this->msg = msg;
    }

    // Override the getMsg method to include the book's ID
    string getMsg() override {
        return this->msg + " " + to_string(this->id);
    }
};

// Exception for when a book with the same ISBN already exists in the library
class ExistingBookISBNException : public exception, public IBookExceptions {
private:
    string msg;  // Custom error message
    int ISBN;    // ISBN of the existing book
public:
    ExistingBookISBNException(const char* msg, int ISBN) : exception(msg) {
        this->ISBN = ISBN;
        this->msg = msg;
    }

    // Override the getMsg method to include the existing book's ISBN
    string getMsg() override {
        return this->msg + " " + to_string(this->ISBN);
    }
};

// Class representing a book
class Book {
private:
    string title;
    string author;
    int id;
    int ISBN;

public:
    Book(string title, string author, int id, int ISBN) {
        this->id = id;
        this->author = author;
        this->title = title;
        this->ISBN = ISBN;
    }

    // Setters and getters for book attributes
    void setId(int id)              { this->id = id; }
    void setTitle(string title)     { this->title = title; }
    void setAuthor(string author)   { this->author = author; }
    void setISBN(int ISBN)          { this->ISBN = ISBN; }
    string getAuthor()             { return this->author; }
    string getTitle()              { return this->title; }
    int getId()                    { return this->id; }
    int getISBN()                  { return this->ISBN; }

    // Overload the equality operator to compare books based on attributes
    bool operator == (const Book& book) {
        if (id == book.id && author == book.author && title == book.title && ISBN == book.ISBN) {
            return true;
        }
        return false;
    }
};

// Class representing a library
class Library {
private:
    vector<Book> books;  // Vector to store books

public:
    // Remove a book from the library
    void RemoveBook(Book book) {
        auto bookToErase = find(books.begin(), books.end(), book);
        if (bookToErase != books.end()) {
            books.erase(bookToErase);
        }
    }

    // Add a book to the library, throwing an exception if the ISBN already exists
    void AddBook(Book book) {
        for (auto& existingBook : books)
            if (existingBook.getISBN() == book.getISBN())
                throw ExistingBookISBNException(
                    "ExistingBookISBNException Error: book by this ISBN already exists in this library!",
                    book.getISBN()
                );
        books.push_back(book);
    }

    // Search for a book by ID in the library, throwing an exception if not found
    Book SearchBookById(int id) {
        for (Book b : books) 
            if (b.getId() == id) 
                return b;
        throw BookNotFoundException("BookNotFoundException Error: Could not find any book by the ID:", id);
    }
};

int main() {
    Library library;  // Create a library object
    Book book1("Book 1", "Author 1", 1, 57439);  // Create two book objects
    Book book2("Book 2", "Author 2", 2, 57439);

    try {
        library.AddBook(book1);  // Try to add book1 to the library
        library.AddBook(book2);  // Try to add book2 to the library
    }
    catch (ExistingBookISBNException ex) {
        cout << ex.getMsg() << endl;  // Handle the exception if ISBN already exists
    }

    Book foundBook = book1;  // Create a book object for searching

    try {
        foundBook = library.SearchBookById(5);  // Try to search for a book by ID
    }
    catch (BookNotFoundException ex) {
        cout << ex.getMsg() << endl;  // Handle the exception if the book is not found
    }

    return 0;
}
