#include <iostream>
#include "Address.h"
#include "Library.h"
#include "Book.h"
#include "BookItem.h"
#include "Member.h"

using namespace std;
using namespace std::chrono;

int main() {

    Address address(
        "123 Main Street",
        "New York",
        "NY",
        "10001",
        "USA");
    
    Library library("Central Library",address);

    Book book(
        "978-123456789",
        "Design Patterns",
        "Gang of Four",
        "Software Design",
        "Addison Wesley",
        395);

    BookItem item(
        "B001",
        &book,
        false,
        50.0);

    book.addBookitem(&item);

    Member member(
        "B3221",
        "Raj Patel",
        "rajp@example.com",
        "9999999999");

    library.addBook(book);
    library.addmember(member);


    if (member.borrowbook(item)) {
        cout << "Book borrowed successfully\n";
    }

    auto returnDate =
        system_clock::now() + hours(24 * 14);

    member.returnbook(item, returnDate);

    cout << member.getfine() << endl;

    return 0;

}
