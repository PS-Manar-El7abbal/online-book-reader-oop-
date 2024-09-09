#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class books;
class User;

vector<User> v_user;
vector<books> b_books;

class books
{
public:
    string ISBN, title, author_name;
    int pages;

    books() {}

    books(string ISBN, string title, string author_name, int pages) : ISBN(ISBN), title(title), author_name(author_name), pages(pages) {}

    void add_book()
    {
        books b;
        cout << "Enter ISBN : ";
        cin >> b.ISBN;
        cout << "Enter title : ";
        cin >> b.title;
        cout << "Enter author name : ";
        cin >> b.author_name;
        cout << "Enter how many pages : ";
        cin >> b.pages;
        b_books.push_back(b);
    }
};

class User
{
public:
    string name, password, email, username;
    vector<string> reading;

    User() {}

    User(string name, string password, string email, string username)
        : name(name), password(password), email(email), username(username) {}

    void Sign_Up()
    {
        User u;
        cout << "Enter your username (no spaces): ";
        cin >> u.username;
        cout << "Enter Your password (no spaces): ";
        cin >> u.password;
        cout << "Enter Your name (no spaces): ";
        cin >> u.name;
        cout << "Enter Your email (no spaces): ";
        cin >> u.email;
        cout << "Hello " << u.name << "| User view\n";
        v_user.push_back(u);
    }

    void Log_In()
    {
        cout << "Enter Your User Name: ";
        cin >> username;
        cout << "Enter Your Password: ";
        cin >> password;
        for (auto value : v_user)
        {
            if (username == value.username && password == value.password)
            {
                cout << "Logged in successfully\n";
                return;
            }
        }
        cout << "This is not in our system\n";
    }

    void menu()
    {
        cout << "Menu\n";
        cout << "[1] Log in\n";
        cout << "[2] Sign Up\n";
        cout << "Choice [1-2]: ";
        int choice = 0;
        cin >> choice;
        if (choice == 1)
        {
            Log_In();
        }
        else if (choice == 2)
        {
            Sign_Up();
        }
        else
        {
            cout << "Invalid choice. Try again\n";
        }
    }

    //void menu_user();

    void View_Profile()
    {
        cout << "Name : " << name << '\n';
        cout << "Password : " << password << '\n';
        cout << "Email : " << email << '\n';
    }

    void time_date()
    {
        time_t now = time(0);
        tm local_time;
        localtime_s(&local_time, &now); 

        cout << (local_time.tm_year + 1900) << '-'
            << (local_time.tm_mon + 1) << '-'
            << local_time.tm_mday << " "
            << local_time.tm_hour << ':'
            << local_time.tm_min << ':'
            << local_time.tm_sec << endl;
    }

    void select_choose_from_history() 
{
        for (int j = 0; j < reading.size(); j++)
        {
            cout << j + 1 << ". " << reading[j] << endl;
            time_date();
        }
    }

    void select_choose_from_available()
    {
        cout << "The books in our system: \n";
        for (int i = 0; i < b_books.size(); i++) {
            cout << "[" << i + 1 << "] " << b_books[i].title << '\n';
        }

        cout << "Which book to read? (from 1 to " << b_books.size() << "): ";
        int number_book;
        cin >> number_book;

        reading.push_back(b_books[number_book - 1].title);

        int c_page = 1;
        cout << "Current Page [1/" << b_books[number_book - 1].pages << "]\n";

        while (true)
        {
            cout << "Menu:\n";
            cout << "[1] Next page\n";
            cout << "[2] Previous page\n";
            cout << "[3] Stop reading\n";
            cout << "Choose [1-3]: ";
            int cho;
            cin >> cho;

            if (cho == 1 && c_page < b_books[number_book - 1].pages)
            {
                c_page++;
                cout << "Page: " << c_page << '\n';
            }
            else if (cho == 2 && c_page > 1)
            {
                c_page--;
                cout << "Page: " << c_page << '\n';
            }
            else if (cho == 3)
            {
                menu_user();
                return;
            }
            else
            {
                cout << "Invalid choice\n";
            }
        }
    }

    void Log_out()
    {
        return;
    }

    void menu_user()
    {
        cout << "Menu User\n";
        cout << "[1] View profile\n";
        cout << "[2] List & select from available books\n";
        cout << "[3] List & select from history\n";
        cout << "[4] Log out\n";

        int choice_menu_user;
        cin >> choice_menu_user;
        if (choice_menu_user == 1)
        {
            View_Profile();
        }
        else if (choice_menu_user == 2)
        {
            select_choose_from_available();
        }
        else if (choice_menu_user == 3)
        {
            select_choose_from_history();
        }
        else if (choice_menu_user == 4)
        {
            Log_out();
        }
        else 
        {
            cout << "Invalid choice, try again\n";
        }
    }
};

class Admin : public books
{
public:
    string name_ad, pass;

    void profile()
    {
        cout << "Admin name: " << name_ad << '\n';
        cout << "Admin password: " << pass << '\n';
    }

    void menu_two()
    {
        cout << "Menu\n";
        cout << "[1] View profile\n";
        cout << "[2] Add books\n";
        int choice_menu;
        cin >> choice_menu;
        if (choice_menu == 1)
        {
            profile();
        }
        else if (choice_menu == 2)
        {
            add_book();
        }
        else
        {
            cout << "Invalid choice, try again\n";
        }
    }

    void log_in()
    {
        cout << "Name: ";
        cin >> name_ad;
        cout << "Password: ";
        cin >> pass;
        if (name_ad == pass)
        {
            cout << "Hello " << name_ad << " | Admin view\n";
        }
        else
        {
            cout << "Incorrect admin credentials\n";
        }
    }

    void sign_up()
    {
        cout << "Name: ";
        cin >> name_ad;
        cout << "Password: ";
        cin >> pass;
        cout << "Hello " << name_ad << " | Admin view\n";
    }

    void menu_admin()
    {
        cout << "Menu\n";
        cout << "[1] Log in\n";
        cout << "[2] Sign Up\n";
        int ch;
        cin >> ch;
        if (ch == 1)
        {
            log_in();
            menu_two();
        }
        else if (ch == 2)
        {
            sign_up();
            menu_two();
        }
        else 
        {
            cout << "Invalid choice, try again\n";
        }
    }
};

User new_user;
Admin admin;

void System()
{
    while (true)
        {
        cout << "You're the admin or user?\n";
        cout << "[1] Admin\n";
        cout << "[2] User\n";
        int choose;
        cin >> choose;
        if (choose == 1)
        {
            admin.menu_admin();
        }
        else if (choose == 2)
        {
            new_user.menu();
            new_user.menu_user();
        }
        else 
        {
            cout << "Invalid choice, try again\n";
        }
    }
}

int main()
{
    System();
    return 0;
}

