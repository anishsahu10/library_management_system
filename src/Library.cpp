#include "Library.h"
#include <fstream>
#include <iostream>
#include <sstream>

Library::Library() : nextBookId(1), nextUserId(1)
{
    loadData();
}

Library::~Library()
{
    saveData();
}

bool Library::addBook(const string &title, const string &author,
                      const string &publisher, int year, const string &isbn)
{
    auto book = make_unique<Book>(nextBookId++, title, author);
    books[book->getBookID()] = move(book);
    saveData();
    return true;
}

bool Library::removeBook(int bookId)
{
    if (books.find(bookId) != books.end())
    {
        books.erase(bookId);
        saveData();
        return true;
    }
    return false;
}

Book *Library::getBook(int bookId)
{
    auto it = books.find(bookId);
    return it != books.end() ? it->second.get() : nullptr;
}

void Library::displayAllBooks() const
{
    cout << "\n.... | LIBRARY BOOKS COLLECTION | ....\n";
    for (const auto &pair : books)
    {
        cout << "Book ID: " << pair.second->getBookID() << "\n"
             << "Title of the Book: " << pair.second->getTitle() << "\n"
             << "Author Name: " << pair.second->getAuthor() << "\n"
             << "Current Status: " << (pair.second->isBookAvailable() ? "Available" : "Borrowed") << "\n"
             << "-------------------\n";
    }
}

bool Library::addStudent(const string &name, const string &password)
{
    auto student = make_unique<Student>(nextUserId++, name, password);
    users[student->getID()] = move(student);
    saveData();
    return true;
}

bool Library::addFaculty(const string &name, const string &password)
{
    auto faculty = make_unique<Faculty>(nextUserId++, name, password);
    users[faculty->getID()] = move(faculty);
    saveData();
    return true;
}

bool Library::addLibrarian(const string &name, const string &password)
{
    auto librarian = make_unique<Librarian>(nextUserId++, name, password);
    users[librarian->getID()] = move(librarian);
    saveData();
    return true;
}

bool Library::removeUser(int userId)
{
    if (users.find(userId) != users.end())
    {
        users.erase(userId);
        saveData();
        return true;
    }
    return false;
}

User *Library::getUser(int userId)
{
    auto it = users.find(userId);
    return it != users.end() ? it->second.get() : nullptr;
}

void Library::displayAllUsers() const
{
    cout << "\n.... | LIBRARY USERS LIST | ....\n";
    for (const auto &pair : users)
    {
        pair.second->showUserDetails();
        cout << "-------------------\n";
    }
}

bool Library::borrowBook(int userId, int bookId)
{
    auto user = getUser(userId);
    auto book = getBook(bookId);

    if (!user || !book)
        return false;
    if (!user->isAllowedToBorrow())
        return false;
    if (!book->isBookAvailable())
        return false;

    Student *student = dynamic_cast<Student *>(user);
    Faculty *faculty = dynamic_cast<Faculty *>(user);

    int maxDays = 0;

    if (student)
    {
        if (student->getAccount().getTotalFine() > 0)
            return false;
        maxDays = 15;
        student->getAccount().borrowBook(bookId, maxDays);
    }
    else if (faculty)
    {
        maxDays = 30;
        faculty->getAccount().borrowBook(bookId, maxDays);
    }
    else
    {
        return false;
    }

    book->setAvailability(false);
    saveData();
    return true;
}

bool Library::returnBook(int userId, int bookId)
{
    auto user = getUser(userId);
    auto book = getBook(bookId);

    if (!user || !book)
        return false;
    if (book->isBookAvailable())
        return false;

    Student *student = dynamic_cast<Student *>(user);
    Faculty *faculty = dynamic_cast<Faculty *>(user);

    if (student)
    {
        student->getAccount().returnBook(bookId);
    }
    else if (faculty)
    {
        faculty->getAccount().returnBook(bookId);
    }
    else
    {
        return false;
    }

    book->setAvailability(true);
    saveData();
    return true;
}

double Library::calculateFine(int userId)
{
    auto user = getUser(userId);
    if (!user)
        return 0.0;

    Student *student = dynamic_cast<Student *>(user);
    if (student)
    {
        return student->getAccount().getTotalFine();
    }
    return 0.0;
}

bool Library::payFine(int userId)
{
    auto user = getUser(userId);
    if (!user)
        return false;

    Student *student = dynamic_cast<Student *>(user);
    if (student)
    {
        student->getAccount().payFine();
        saveData();
        return true;
    }
    return false;
}

void Library::loadData()
{

    ifstream bookFile("data/books.txt");
    if (bookFile.is_open())
    {
        string line;
        while (getline(bookFile, line))
        {
            auto book = make_unique<Book>(Book::fromString(line));
            books[book->getBookID()] = move(book);
            if (book->getBookID() >= nextBookId)
            {
                nextBookId = book->getBookID() + 1;
            }
        }
        bookFile.close();
    }

    ifstream userFile("data/users.txt");
    if (userFile.is_open())
    {
        string line;
        while (getline(userFile, line))
        {
            stringstream ss(line);
            string role, userData;
            getline(ss, role, '|');
            getline(ss, userData);

            unique_ptr<User> user;
            if (role == "Student")
            {
                user = make_unique<Student>(0, "", "");
            }
            else if (role == "Faculty")
            {
                user = make_unique<Faculty>(0, "", "");
            }
            else if (role == "Librarian")
            {
                user = make_unique<Librarian>(0, "", "");
            }

            if (user)
            {
                users[user->getID()] = move(user);
                if (user->getID() >= nextUserId)
                {
                    nextUserId = user->getID() + 1;
                }
            }
        }
        userFile.close();
    }
}

void Library::saveData() const
{
    ofstream bookFile("data/books.txt");
    if (bookFile.is_open())
    {
        for (const auto &pair : books)
        {
            bookFile << pair.second->toString() << "\n";
        }
        bookFile.close();
    }

    ofstream userFile("data/users.txt");
    if (userFile.is_open())
    {
        for (const auto &pair : users)
        {
            userFile << pair.second->getUserType() << "|";
            userFile << "\n";
        }
        userFile.close();
    }
}

void Library::initializeWithSampleData()
{
    addBook("Computer Organization", "Carl Hamacher", "", 0, "");
    addBook("Data Science", "John D. Kelleher", "", 0, "");
    addBook("The Art of Computer Programming", "Donald Knuth", "", 0, "");
    addBook("Digital Image Processing", "Rafael C. Gonzalez", "", 0, "");
    addBook("Big Data", "Viktor Mayer-Schönberger", "", 0, "");
    addBook("The Elements of Statistical Learning", "Trevor Hastie", "", 0, "");
    addBook("Neural Networks and Deep Learning", "Michael Nielsen", "", 0, "");
    addBook("The Pragmatic Programmer", "Andrew Hunt", "", 0, "");
    addBook("Introduction to Automata Theory", "John E. Hopcroft", "", 0, "");
    addBook("Software Architecture", "Richard N. Taylor", "", 0, "");

    addStudent("Karan Desai", "pass111");
    addStudent("Meera Nair", "pass222");
    addStudent("Soham Bhatt", "pass333");
    addStudent("Pooja Sharma", "pass444");
    addStudent("Aakash Reddy", "pass555");

    addFaculty("Dr. Anil Kapoor", "pass666");
    addFaculty("Prof. Swati Joshi", "pass777");
    addFaculty("Dr. Naveen Iyer", "pass888");

    addLibrarian("Mrs. Rekha Verma", "pass999");
}