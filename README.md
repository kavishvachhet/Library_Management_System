# Library Management System

This is a monolithic C++ codebase for a Library Management System refactored into a structured format. 

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
