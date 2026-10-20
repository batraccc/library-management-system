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
    do
    {
        displayMenu();
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
        }
        case 2:
        {
        }
        case 3:
        {
        }
        case 4:
        {
        }
        case 5:
        {
        }
        case 6:
        {
        }
        case 7:
        {
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