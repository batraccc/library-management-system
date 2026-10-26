#include "../include/Library.h"
#include "../include/Utilities.h"
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
                while (!(std::cin >> id))
                {
                    std::cout << "Invalid input! Please enter a valid positive number for ID!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (library.bookIdExists(id))
                {
                    std::cout << "Book with that id already exists!" << std::endl;
                    break;
                }
                do
                {
                    std::cout << "Enter book title: ";
                    std::getline(std::cin, title);
                } while (title == "");
                do
                {
                    std::cout << "Enter book author: ";
                    std::getline(std::cin, author);
                } while (author == "");
                std::cout << "Enter publish year: ";
                while (!(std::cin >> publish_year))
                {
                    std::cout << "Invalid input! Please enter a valid positive number for publish year!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                do
                {
                    std::cout << "Enter ISBN: ";
                    std::getline(std::cin, ISBN);
                } while (!isValidISBN(ISBN));
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
                if (!library.isBookBorrowed(id))
                {
                    std::string choice{};
                    std::cout << "Are you sure you want to delete the book? [Yes/No]: ";
                    std::getline(std::cin, choice);
                    if (choice == "Yes")
                        library.removeBook(id);
                    else if (choice == "No")
                    {
                        std::cout << "Cancelling request..." << std::endl;
                    }
                    else
                    {
                        std::cout << "Invalid confirmation, cancelling..." << std::endl;
                    }
                }
                else
                    std::cout << "Can not remove the book because it is borrowed!" << std::endl;
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
                    std::cout << book.getId() << ": " << book.getTitle() << ", " << book.getAuthor() << ", " << book.getPublishYear() << ", " << book.getISBN() << ", Is Borrowed: " << (library.isBookBorrowed(book.getId()) ? "Yes" : "No") << std::endl;
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
                while (!(std::cin >> id))
                {
                    std::cout << "Invalid input! Please enter a valid positive number for ID!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (library.memberIdExists(id))
                {
                    std::cout << "Member with that id already exists!" << std::endl;
                    break;
                }
                do
                {
                    std::cout << "Enter member name: ";
                    std::getline(std::cin, name);
                } while (name == "");
                do
                {
                    std::cout << "Enter member surname: ";
                    std::getline(std::cin, surname);
                } while (surname == "");
                do
                {
                    std::cout << "Enter member email: ";
                    std::getline(std::cin, email);
                } while (!isValidEmail(email));
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
                if (!library.isMemberBorrowing(id))
                {
                    std::string choice{};
                    std::cout << "Are you sure you want to delete the member? [Yes/No]: ";
                    std::getline(std::cin, choice);
                    if (choice == "Yes")
                        library.removeMember(id);
                    else if (choice == "No")
                    {
                        std::cout << "Cancelling request..." << std::endl;
                    }
                    else
                    {
                        std::cout << "Invalid confirmation, cancelling..." << std::endl;
                    }
                }
                else
                    std::cout << "Can not remove member because he is currently borrowing a book!" << std::endl;
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
                    std::cout << member.getId() << ", " << member.getName() << ", " << member.getSurname() << ", " << member.getEmail() << ", " << member.getLateFees() << std::endl;
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
            try
            {
                unsigned book_id{};
                unsigned member_id{};
                std::cout << "Enter book id: ";
                std::cin >> book_id;
                std::cout << "Enter member id: ";
                std::cin >> member_id;
                library.borrowBook(book_id, member_id);
                std::cout << "Book borrowed successfuly!" << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 9:
        {
            try
            {
                unsigned book_id{};
                unsigned member_id{};
                std::cout << "Enter book id: ";
                std::cin >> book_id;
                std::cout << "Enter member id: ";
                std::cin >> member_id;
                library.returnBook(book_id, member_id);
                std::cout << "Book returned successfuly!" << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 10:
        {
            try
            {
                unsigned member_id{};
                std::cout << "Enter member id: ";
                std::cin >> member_id;
                std::vector<Book> books = library.getMemberBorrowedBooks(member_id);
                for (const auto &book : books)
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
        case 11:
        {
            try
            {
                std::vector<BorrowRecord> records = library.getBorrowingHistory();
                for (const BorrowRecord &record : records)
                {
                    std::cout << "Member ID: " << record.getMemberId() << std::endl;
                    std::cout << "Book ID: " << record.getBookId() << std::endl;
                    std::cout << "Borrow date: ";
                    record.getBorrowDate().display(std::cout);
                    std::cout << std::endl;
                    std::cout << "Is returned: " << record.isReturned() << std::endl;
                }
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 12:
        {
            try
            {
                std::string filepath{};
                std::cout << "Input filepath: ";
                std::getline(std::cin, filepath);
                library.saveToFile(filepath);
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        case 13:
        {
            try
            {
                std::string filepath{};
                std::cout << "Input filepath: ";
                std::getline(std::cin, filepath);
                library.loadFromFile(filepath);
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        default:
            if (choice != 0)
            {
                std::cout << "Not a valid choice!" << std::endl;
            }
            break;
        }
    } while (choice != 0);
    return 0;
}