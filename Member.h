#pragma once
#include <string>
#include <vector>
#include "BookItem.h"

class Member {
private:
    std::string memberId;
    std::string name;
    std::string email;
    std::string phone;

public:
    std::vector<BookItem> borrowedbooks;
    double totalfine;

    Member(const std::string& memberId,
           const std::string& name,
           const std::string& email,
           const std::string& phone);

    bool borrowbook(BookItem& item);

    void returnbook(BookItem& bookitem,
                    std::chrono::system_clock::time_point returndate);

    void payfine(double amt);

    const std::vector<BookItem>& getborrowedbooks() const;

    double getfine();
};
