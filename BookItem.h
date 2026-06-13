#pragma once
#include <string>
#include <chrono>
#include "Bookstatus.h"

class Book;

class BookItem {
private:
    std::string barcode;
    Book* book;

    bool isReferenceOnly;
    double price;
    Bookstatus status;

    std::chrono::system_clock::time_point borrowed;
    std::chrono::system_clock::time_point dueDate;

    bool borrowedSet = false;
    bool dueDateSet = false;

public:
    BookItem(const std::string& barcode,
             Book* book,
             bool isReferenceOnly,
             double price);

    bool operator==(const BookItem& other) const;

    void returnbook();

    double calculateFine(std::chrono::system_clock::time_point returndate) const;

    std::chrono::system_clock::time_point getDueDate() const;

    bool hasDueDate() const;

    Bookstatus getStatus() const;

    bool canuadd();
};
