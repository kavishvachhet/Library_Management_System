#pragma once
#include <string>
#include <vector>
#include "Address.h"
#include "Book.h"
#include "Member.h"

class Library {
private:
    std::string name;
    Address address;

public:
    std::vector<Book> books;
    std::vector<Member> members;

    Library(const std::string& name,
            const Address& address);

    void addBook(const Book& book);

    void addmember(const Member& member);

    std::vector<Book> search(const std::string& s);
};
