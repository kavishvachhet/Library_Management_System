#include "Book.h"
#include <algorithm>

Book::Book(const std::string& isbn,
     const std::string& title,
     const std::string& author,
     const std::string& subject,
     const std::string& publisher,
     int numPages)
    : isbn(isbn),
      title(title),
      author(author),
      subject(subject),
      publisher(publisher),
      numPages(numPages) {}
    
void Book::addBookitem(BookItem* item) {
    bookItems.push_back(item);
}

bool Book::removeBookItem(BookItem* item) {
    auto it = std::find(bookItems.begin(), bookItems.end(), item);

    if (it != bookItems.end()) {
        bookItems.erase(it);
        return true;
    }

    return false;
}
