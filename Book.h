#pragma once
#include <string>
#include <vector>

class BookItem;

class Book {
private:
    std::string isbn;
    std::string title;
    std::string author;
    std::string subject;
    std::string publisher;
    int numPages;

    std::vector<BookItem*> bookItems;

public:
    Book(const std::string& isbn,
         const std::string& title,
         const std::string& author,
         const std::string& subject,
         const std::string& publisher,
         int numPages);
        
    void addBookitem(BookItem* item);
    bool removeBookItem(BookItem* item);

    const std::string& getTitle() const { return title; }
    const std::string& getAuthor() const { return author; }
    const std::string& getSubject() const { return subject; }
};
