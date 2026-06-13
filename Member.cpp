#include "Member.h"
#include <algorithm>

Member::Member(const std::string& memberId,
       const std::string& name,
       const std::string& email,
       const std::string& phone)
    : memberId(memberId),
      name(name),
      email(email),
      phone(phone),
      totalfine(0.0) {}

bool Member::borrowbook(BookItem& item) {
    if (borrowedbooks.size() >= 5)
        return false;

    if (totalfine > 10.0)
        return false;

    if (!item.canuadd())
        return false;

    borrowedbooks.push_back(item);

    return true;
}

void Member::returnbook(BookItem& bookitem,
                std::chrono::system_clock::time_point returndate) {

    auto it = std::find(
        borrowedbooks.begin(),
        borrowedbooks.end(),
        bookitem);

    if (it == borrowedbooks.end())
        return;

    totalfine += bookitem.calculateFine(returndate);

    bookitem.returnbook();

    borrowedbooks.erase(it);
}

void Member::payfine(double amt) {
    totalfine -= amt;

    if (totalfine < 0)
        totalfine = 0.0;
}

const std::vector<BookItem>& Member::getborrowedbooks() const {
    return borrowedbooks;
}

double Member::getfine() {
    return totalfine;
}
