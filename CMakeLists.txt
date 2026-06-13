cmake_minimum_required(VERSION 3.10)
project(LibraryManagementSystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(LibrarySystem
    main.cpp
    Library.cpp
    Book.cpp
    BookItem.cpp
    Member.cpp
)
