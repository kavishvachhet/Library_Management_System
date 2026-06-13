#include "Library.h"
#include <algorithm>
#include <cctype>

Library::Library(const std::string& name,
        const Address& address)
    : name(name),
      address(address) {}

void Library::addBook(const Book& book) {
    books.push_back(book);
}

void Library::addmember(const Member& member) {
    members.push_back(member);
}

std::vector<Book> Library::search(const std::string& s) {
    std::string key = s;

    std::transform(
        key.begin(),
        key.end(),
        key.begin(),
        [](unsigned char c){ return std::tolower(c); });

    std::vector<Book> rss;

    for (auto& b : books) {

        std::string title = b.getTitle();
        std::string author = b.getAuthor();
        std::string subject = b.getSubject();

        std::transform(title.begin(), title.end(),
                  title.begin(), [](unsigned char c){ return std::tolower(c); });

        std::transform(author.begin(), author.end(),
                  author.begin(), [](unsigned char c){ return std::tolower(c); });

        std::transform(subject.begin(), subject.end(),
                  subject.begin(), [](unsigned char c){ return std::tolower(c); });

        if (title.find(key) != std::string::npos ||
            author.find(key) != std::string::npos ||
            subject.find(key) != std::string::npos) {
            rss.push_back(b);
        }
    }

    return rss;
}
