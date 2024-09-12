#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <map>
#include <algorithm> 

using namespace std;

class Book
{
public:
    string ISBN, title, author_name;
    int pages;

    Book() {}

    Book(string ISBN, string title, string author_name, int pages) : ISBN(ISBN), title(title), author_name(author_name), pages(pages) {}

    void addBook()
    {
        cout << "Enter ISBN : ";
        cin >> ISBN;
        cout << "Enter title : ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter author name : ";
        getline(cin, author_name);
        cout << "Enter how many pages : ";
        cin >> pages;

        ofstream file("databaseforbooks.txt", ios::app);
        file << ISBN << " " << title << " " << author_name << " " << pages << '\n';
        file.close();
        cout << "Book added successfully!" << endl;
    }
};

class User
{
public:
    string name, password, email, username;
    int c_page = 1;
    vector<string> reading;

    User() {}

    User(string name, string password, string email, string username)
        : name(name), password(password), email(email), username(username) {}

    void SignUp()
    {
        cout << "Enter your username (no spaces): ";
        cin >> username;
        cout << "Enter Your password (no spaces): ";
        cin >> password;
        cout << "Enter Your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Your email: ";
        cin >> email;

        ofstream reg("database.txt", ios::app);
        reg << username << " " << password << " " << name << " " << email << endl;
        reg.close();
        cout << "Hello " << name << " | User view\n";
    }

    void LogIn()
    {
        string u, p, n, e;
        bool found = false;
        cout << "Enter Your Username: ";
        cin >> username;
        cout << "Enter Your Password: ";
        cin >> password;

        ifstream lg("database.txt");
        while (lg >> u >> p >> n >> e)
        {
            if (u == username && p == password)
            {
                cout << "Hello " << username << " | User view" << endl;
                name = n;
                email = e;
                found = true;
                break;
            }
        }

        lg.close();
        if (!found)
        {
            cout << "Invalid login details, please try again.\n";
            LogIn();
        }
    }

    void ViewProfile()
    {
        cout << "Name : " << name << '\n';
        cout << "Password : " << password << '\n';
        cout << "Email : " << email << '\n';
    }

    void TimeDate()
    {
        time_t now = time(0);
        tm local_time;
        localtime_s(&local_time, &now);
        int hour_12 = local_time.tm_hour % 12;
        if (hour_12 == 0)
        {
            hour_12 = 12;
        }
        string am_pm = (local_time.tm_hour >= 12) ? "PM" : "AM";
        cout << (local_time.tm_year + 1900) << '-'
            << setw(2) << setfill('0') << (local_time.tm_mon + 1) << '-'
            << setw(2) << setfill('0') << local_time.tm_mday << " "
            << setw(2) << setfill('0') << hour_12 << ':'
            << setw(2) << setfill('0') << local_time.tm_min << ':'
            << setw(2) << setfill('0') << local_time.tm_sec << " " << am_pm << endl;
    }

    void SelectChooseFromAvailable()
    {
        ifstream file("databaseforbooks.txt");
        vector<Book> books;

        string ISBN, title, author_name;
        int pages;
        while (file >> ISBN >> ws)//for what ws
        {
            getline(file, title, ' ');
            getline(file, author_name, ' ');
            file >> pages;
            books.emplace_back(ISBN, title, author_name, pages);//what is emplace back
        }
        file.close();

        if (books.empty())
        {
            cout << "The system has no books, sorry try later.\n";
            return;
        }

        cout << "The books in our system:\n";
        for (size_t i = 0; i < books.size(); ++i)
        {
            cout << "[" << i + 1 << "] " << books[i].title << " ISBN : " << books[i].ISBN << '\n';
        }

        int number_book;
        cout << "Which book to read? (enter the ISBN corresponding to the book): ";
        cin >> number_book;

        if (number_book < 1 || number_book > books.size())
        {
            cout << "Invalid choice, try again.\n";
            return;
        }

        cout << "Now, you are reading: ( " << books[number_book - 1].title<<" )" << endl;
        reading.push_back(books[number_book - 1].title);
        c_page = 1;

        cout << "Current Page [1/" << books[number_book - 1].pages << "]\n";

        while (true)
        {
            cout << "Menu:\n";
            cout << setw(5) << "[1] Next page\n";
            cout << setw(5) << "[2] Previous page\n";
            cout << setw(5) << "[3] Stop reading\n";
            cout << setw(5) << "Choose [1-3]: ";
            int cho;
            cin >> cho;

            if (cho == 1 && c_page < books[number_book - 1].pages)
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
                return;
            }
            else
            {
                cout << "Invalid choice\n";
            }
        }
    }

    void SelectChooseFromHistory()
    {
        if (reading.empty())
        {
            cout << "You have no reading history.\n";
            return;
        }

        for (size_t j = 0; j < reading.size(); ++j)
        {
            cout << j + 1 << ". " << reading[j] << endl;
            cout << "The page you stopped at [" << c_page << "]\n";
            TimeDate();
        }
    }

    void Menu()
    {
        cout << "Menu User\n";
        cout << setw(5) << "[1] View profile\n";
        cout << setw(5) << "[2] List & select from available books\n";
        cout << setw(5) << "[3] List & select from history\n";
        cout << setw(5) << "[4] Log out\n";

        int choice_menu_user;
        cin >> choice_menu_user;
        if (choice_menu_user == 1)
        {
            ViewProfile();
        }
        else if (choice_menu_user == 2)
        {
            SelectChooseFromAvailable();
        }
        else if (choice_menu_user == 3)
        {
            SelectChooseFromHistory();
        }
        else if (choice_menu_user == 4)
        {
            return;
        }
        else
        {
            cout << "Invalid choice, try again\n";
        }
    }
};

class Admin
{
public:
    string name_ad, pass;

    void Profile()
    {
        cout << "Admin name: " << name_ad << '\n';
        cout << "Admin password: " << pass << '\n';
    }

    void LogIn()
    {
        cout << "Enter your name: ";
        cin >> name_ad;
        cout << "Enter your password: ";
        cin >> pass;
    }

    void AddBook()
    {
        Book b;
        b.addBook();
    }
};
class System:public Admin,public User
{
public:
    void system()
    {
        User user;
        Admin admin;
        int choice;
        bool logged_in = false;

        while (true)
        {
            cout << "----------------------------------------\n";
            cout << "You are :\n";
            cout << "[1] Admin\n";
            cout << "[2] User\n";
            cout << "----------------------------------------\n";
            int choice = 0;cin >> choice;
            if (choice == 1)
            {
                admin.LogIn();
                cout << "Hello ! Manar Elhabbal " << "| Admin view\n";
                cout << "----------------------------------------\n";
                cout << "[1] view my profile\n";
                cout << "[2] Add a new book\n";
                cout << "----------------------------------------\n";
                int choose = 0;cin >> choose;
                if (choose == 1)
                {
                    admin.Profile();
                }
                else if (choose == 2)
                {
                    admin.AddBook();
                }
                else
                {
                    cout << "Invalid choice, try again\n";
                }
            }
            else if (choice == 2)
            {
                cout << "Main Menu:\n";
                cout << "[1] Sign Up\n";
                cout << "[2] Log In\n";
                cout << "choose from[1-2] :";
                int ch = 0;cin >> ch;
                if (ch == 1)
                {
                    user.SignUp();
                    Menu();
                }
                else if (ch == 2)
                {
                    user.LogIn();
                    logged_in = true;
                    Menu();
                }
                else
                {
                    cout << "invalid choice ,try again\n";
                }
            }


            if (logged_in)
            {
                user.Menu();
            }
        }
    }
};

int main()
{
    System s;
    s.system();
  
    return 0;
}
//the problems are these
//the first is not printed the info after view profile of user
//the second when ask to show the history
//mapping the pages
