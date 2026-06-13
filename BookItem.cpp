#include "BookItem.h"

BookItem::BookItem(const std::string& barcode,
         Book* book,
         bool isReferenceOnly,
         double price)
    : barcode(barcode),
      book(book),
      isReferenceOnly(isReferenceOnly),
      price(price),
      status(Bookstatus::AVAILABLE) {}

bool BookItem::operator==(const BookItem& other) const {
    return barcode == other.barcode;
}

void BookItem::returnbook() {
    borrowedSet = false;
    dueDateSet = false;
    status = Bookstatus::AVAILABLE;
}

double BookItem::calculateFine(std::chrono::system_clock::time_point returndate) const {
    if (!borrowedSet)
        return 0.0;

    if (returndate <= dueDate)
        return 0.0;

    auto overdue =
        std::chrono::duration_cast<std::chrono::hours>(returndate - dueDate).count();

    int overdays = overdue / 24;

    return overdays * 50;
}

std::chrono::system_clock::time_point BookItem::getDueDate() const {
    return dueDate;
}

bool BookItem::hasDueDate() const {
    return dueDateSet;
}

Bookstatus BookItem::getStatus() const {
    return status;
}

bool BookItem::canuadd() {
    if (isReferenceOnly)
        return false;

    if (status != Bookstatus::AVAILABLE)
        return false;

    status = Bookstatus::BORROWED;

    borrowed = std::chrono::system_clock::now();
    dueDate = borrowed + std::chrono::hours(24 * 14);

    borrowedSet = true;
    dueDateSet = true;

    return true;
}
