#include "../include/Library.h"
#include <iostream>

void displayMenu()
{
    std::cout << "====== LIBRARY ======" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Add book" << std::endl;
    std::cout << "2. Remove book" << std::endl;
    std::cout << "3. List books" << std::endl;
    std::cout << "4. Search books" << std::endl;
    std::cout << std::endl;
    std::cout << "5. Add member" << std::endl;
    std::cout << "6. Remove member" << std::endl;
    std::cout << "7. List members" << std::endl;
    std::cout << std::endl;
    std::cout << "8. Borrow book" << std::endl;
    std::cout << "9. Return book" << std::endl;
    std::cout << "10. Show member's borrowed books" << std::endl;
    std::cout << "11. Show borrowing history" << std::endl;
    std::cout << std::endl;
    std::cout << "12. Save data" << std::endl;
    std::cout << "13. Load data" << std::endl;
    std::cout << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << std::endl;
    std::cout << "Choose option: ";
}

int main()
{
    int choice{};
    Library library;
    do
    {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice)
        {
        case 1:
        {
            try
            {
                unsigned id{};
                std::string title{};
                std::string author{};
                unsigned short publish_year{};
                std::string ISBN{};
                std::cout << "Enter book id: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter book title: ";
                std::getline(std::cin, title);
                std::cout << "Enter book author: ";
                std::getline(std::cin, author);
                std::cout << "Enter publish year: ";
                std::cin >> publish_year;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, ISBN);
                library.addBook(Book(id, title, author, publish_year, ISBN));
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 2:
        {
            try
            {
                unsigned id{};
                std::cout << "Enter book id: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                library.removeBook(id);
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 3:
        {
            try
            {
                const std::vector<Book> &all_books = library.getAllBooks();
                for (const auto &book : all_books)
                {
                    std::cout << book.getId() << ": " << book.getTitle() << ", " << book.getAuthor() << ", " << book.getPublishYear() << ", " << book.getISBN() << std::endl;
                }
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 4:
        {
            try
            {
                std::string title_author_ISBN{};
                std::cout << "Enter book title, author or ISBN: ";
                std::getline(std::cin, title_author_ISBN);
                std::vector<Book> matching_books = library.searchBooks(title_author_ISBN);
                for (const Book &book : matching_books)
                {
                    std::cout << book.getId() << ": " << book.getTitle() << ", " << book.getAuthor() << ", " << book.getPublishYear() << ", " << book.getISBN() << std::endl;
                }
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 5:
        {
            try
            {
                unsigned id{};
                std::string name{};
                std::string surname{};
                std::string email{};
                std::cout << "Enter member id: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter member name: ";
                std::getline(std::cin, name);
                std::cout << "Enter member surname: ";
                std::getline(std::cin, surname);
                std::cout << "Enter member email: ";
                std::getline(std::cin, email);
                library.addMember(Member(id, name, surname, email));
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 6:
        {
            try
            {
                unsigned id{};
                std::cout << "Enter member id: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                library.removeMember(id);
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 7:
        {
            try
            {
                const std::vector<Member> all_members = library.getAllMembers();
                for (const Member &member : all_members)
                {
                    std::cout << member.getId() << ": " << member.getName() << " " << member.getSurname() << ", " << member.getEmail() << ", Late Fee: " << member.getLateFees() << std::endl;
                }
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 8:
        {
        }
        case 9:
        {
        }
        case 10:
        {
        }
        case 11:
        {
        }
        case 12:
        {
        }
        case 13:
        {
        }
        default:
            break;
        }
    } while (choice != 0);
    return 0;
}