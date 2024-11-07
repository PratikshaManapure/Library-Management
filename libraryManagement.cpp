#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Book class to represent a book in the library
class Book {
private:
    int bookID;
    string title;
    string author;

public:
    Book() {}
    
    Book(int id, string t, string a) {
        bookID = id;
        title = t;
        author = a;
    }

    void setBookDetails(int id, string t, string a) {
        bookID = id;
        title = t;
        author = a;
    }

    void displayBook() {
        cout << "Book ID: " << bookID << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
    }

    int getBookID() {
        return bookID;
    }

    // To save book details into a file
    void saveToFile() {
        ofstream file;
        file.open("books.txt", ios::app);
        file << bookID << "\n" << title << "\n" << author << "\n";
        file.close();
    }
    
    // To read and display book details from file
    static void displayAllBooks() {
        ifstream file;
        file.open("books.txt");
        if (!file) {
            cout << "No books available in the library.\n";
            return;
        }
        
        int id;
        string title, author;
        while (file >> id) {
            file.ignore();  // to ignore the newline character after integer input
            getline(file, title);
            getline(file, author);
            cout << "Book ID: " << id << endl;
            cout << "Title: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "----------------------------" << endl;
        }
        
        file.close();
    }

    // To search for a book by ID
    static void searchBookByID(int searchID) {
        ifstream file;
        file.open("books.txt");
        if (!file) {
            cout << "No books available in the library.\n";
            return;
        }

        int id;
        string title, author;
        bool found = false;
        
        while (file >> id) {
            file.ignore();
            getline(file, title);
            getline(file, author);
            if (id == searchID) {
                cout << "Book Found:\n";
                cout << "Book ID: " << id << endl;
                cout << "Title: " << title << endl;
                cout << "Author: " << author << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "No book found with ID " << searchID << endl;
        }
        
        file.close();
    }

    // To delete a book by ID
    static void deleteBookByID(int deleteID) {
        ifstream file;
        file.open("books.txt");
        if (!file) {
            cout << "No books available in the library.\n";
            return;
        }

        ofstream temp;
        temp.open("temp.txt", ios::app);

        int id;
        string title, author;
        bool found = false;

        while (file >> id) {
            file.ignore();
            getline(file, title);
            getline(file, author);
            if (id == deleteID) {
                found = true;
                cout << "Book with ID " << id << " deleted successfully.\n";
            } else {
                temp << id << "\n" << title << "\n" << author << "\n";
            }
        }

        if (!found) {
            cout << "No book found with ID " << deleteID << endl;
        }

        file.close();
        temp.close();
        
        remove("books.txt");
        rename("temp.txt", "books.txt");
    }
};

// Menu function
void menu() {
    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. View All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Delete Book by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string title, author;
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore(); // ignore newline character
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                Book newBook(id, title, author);
                newBook.saveToFile();
                cout << "Book added successfully.\n";
                break;
            }
            case 2:
                Book::displayAllBooks();
                break;
            case 3: {
                int searchID;
                cout << "Enter Book ID to search: ";
                cin >> searchID;
                Book::searchBookByID(searchID);
                break;
            }
            case 4: {
                int deleteID;
                cout << "Enter Book ID to delete: ";
                cin >> deleteID;
                Book::deleteBookByID(deleteID);
                break;
            }
            case 5:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
}

// Main function
int main() {
    menu();
    return 0;
}

