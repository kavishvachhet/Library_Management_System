# Library Management System

Design a Library Management System that allows librarians to manage books and members, and enables members to borrow and return books.

The system should support the following operations:
1. Add, update, and remove books from the library catalog
2. Register new members and manage their information
3. Allow members to borrow and return books
4. Track due dates and calculate fines for overdue books
5. Search for books by various criteria (title, author, subject, etc.)
6. Manage different types of library items (books, magazines, DVDs, etc.)

## Requirements
- The system should maintain information about books including title, author, ISBN, publication date, and category
- Each book can have multiple physical copies, each with a unique ID
- Members should have profiles with contact information and borrowing history
- Members can borrow a limited number of books for a specific duration
- The system should track due dates and calculate fines for overdue books
- Librarians should be able to search for books and members
- The system should generate reports on book availability, overdue books, and popular books

## Constraints
- A book can be borrowed if at least one copy is available
- A member cannot borrow more than the allowed limit of books
- A book cannot be borrowed if the member has unpaid fines above a threshold
- Books marked as "reference" cannot be borrowed

## UML Class Diagram

```mermaid
classDiagram
    class Bookstatus {
        <<enumeration>>
        AVAILABLE
        BORROWED
        RESERVED
        LOST
    }

    class Address {
        -street: string
        -city: string
        -state: string
        -zipCode: string
        -country: string
    }

    class Library {
        -name: string
        -address: Address
        +books: vector~Book~
        +members: vector~Member~
        +addBook(book: Book)
        +addmember(member: Member)
        +search(s: string): vector~Book~
    }

    class Book {
        -isbn: string
        -title: string
        -author: string
        -subject: string
        -publisher: string
        -numPages: int
        -bookItems: vector~BookItem*~
        +addBookitem(item: BookItem*)
        +removeBookItem(item: BookItem*): bool
        +getTitle(): string
        +getAuthor(): string
        +getSubject(): string
    }

    class BookItem {
        -barcode: string
        -book: Book*
        -isReferenceOnly: bool
        -price: double
        -status: Bookstatus
        -borrowed: time_point
        -dueDate: time_point
        -borrowedSet: bool
        -dueDateSet: bool
        +operator==(other: BookItem): bool
        +returnbook()
        +calculateFine(returndate: time_point): double
        +getDueDate(): time_point
        +hasDueDate(): bool
        +getStatus(): Bookstatus
        +canuadd(): bool
    }

    class Member {
        -memberId: string
        -name: string
        -email: string
        -phone: string
        +borrowedbooks: vector~BookItem~
        +totalfine: double
        +borrowbook(item: BookItem): bool
        +returnbook(bookitem: BookItem, returndate: time_point)
        +payfine(amt: double)
        +getborrowedbooks(): vector~BookItem~
        +getfine(): double
    }

    Library *-- Book : contains
    Library *-- Member : contains
    Library *-- Address : has a
    Book "1" *-- "*" BookItem : has
    Member "1" *-- "*" BookItem : borrows
    BookItem --> Bookstatus : status
```

## UML Sequence Diagram

The following sequence diagram shows the interactions when a member borrows and then returns a book, as demonstrated in `main.cpp`.

```mermaid
sequenceDiagram
    participant Main
    participant Library
    participant Book
    participant BookItem
    participant Member

    Main->>Library: Library("Central Library", address)
    Main->>Book: Book(isbn, title, ...)
    Main->>BookItem: BookItem("B001", book, ...)
    Main->>Book: addBookitem(item)
    Main->>Member: Member(memberId, name, ...)
    Main->>Library: addBook(book)
    Main->>Library: addmember(member)
    
    %% Borrowing Process
    Main->>Member: borrowbook(item)
    Member->>BookItem: canuadd()
    alt is available
        BookItem-->>Member: true (updates borrowed, dueDate, status to BORROWED)
        Member->>Member: adds to borrowedbooks
        Member-->>Main: true
    else is not available
        BookItem-->>Member: false
        Member-->>Main: false
    end

    %% Returning Process
    Main->>Member: returnbook(item, returnDate)
    Member->>BookItem: calculateFine(returnDate)
    BookItem-->>Member: 0.0 (or calculated fine)
    Member->>BookItem: returnbook()
    BookItem-->>BookItem: status = AVAILABLE
    Member->>Member: removes from borrowedbooks
```

## Build Instructions

1. Ensure CMake and a C++ compiler are installed.
2. Run `cmake .` or `cmake -B build` to generate the build files.
3. Run `cmake --build build` or `make` to compile the project.
4. Execute the binary `LibrarySystem`.
