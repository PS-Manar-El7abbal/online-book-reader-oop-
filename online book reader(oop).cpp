#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include<iomanip>
#include<map>
using namespace std;

class books;
class User;

vector<User> v_user;
vector<books> b_books;
class books;
books b;
class books
{
public:
    string ISBN, title, author_name;
    int pages;

    books() {}

    books(string ISBN, string title, string author_name, int pages) : ISBN(ISBN), title(title), author_name(author_name), pages(pages) {}
    

    void add_book(const string& filename)
    {
        cout << "Enter ISBN : ";
        cin >> ISBN;
        cout << "Enter title : ";
        cin >> title;
        cout << "Enter author name : ";
        cin >> author_name;
        cout << "Enter how many pages : ";
        cin >> pages;
        b_books.push_back(*this);

        map<string, int>title_current_page;

        ofstream file("databaseforbooks.txt", ios::app);  
        file << title << " " << author_name << '\n';
        file.close();
        cout << "Book added successfully!" << endl;
    }

   
};

class User:public books
{
public:
    string name, password, email, username;
    int c_page = 1;
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
        cout << "Enter Your name: ";
        cin.ignore();
        getline(cin, u.name);
        cout << "Enter Your email: ";
        cin >> u.email;
        cout << "Hello " << u.name << " | User view\n";
        name = u.name;
        password = u.password;
        email = u.email;

        v_user.push_back(u);


        ofstream reg("database.txt", ios::app);
        reg << u.username << " " << u.password << " " << u.name << " " << u.email << endl;
        reg.close();
    }

    void Log_In()
    {
        string u, p, n, e;
        bool found = false;
        cout << "Enter Your User Name: ";
        cin >> username;
        cout << "Enter Your Password: ";
        cin >> password;

        ifstream lg("database.txt");
        while (lg >> u >> p >> n >> e)
        {
            if (u == username && p == password)
            {
                cout << "Hello " << username << " | User view" << endl;
                cout << '\a';
                cout << "Logged in successfully\n";
                name = n;         // Store the name
                email = e;        // Store the email
                password = p;     // Store the password
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "This is not in the system, try again\n";
            Log_In();
        }

        lg.close();
    }



    void menu()
    {
        cout << "Menu\n";
        cout << setw(5) << "[1] Log in\n";
        cout << setw(5) << "[2] Sign Up\n";
        cout << setw(5) << "Choice [1-2]: ";
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
    //not printed well this is empty 
    //the problem is that the user when log in not add the name or the email

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
        localtime_s(&local_time, &now); // Use localtime_s instead of localtime
        int hour_12 = local_time.tm_hour % 12;
        if (hour_12 == 0)
        {
            hour_12 = 12;
        }
        string am_pm = (local_time.tm_hour >= 12) ? "PM" : "AM";
        cout << (local_time.tm_year + 1900) << '-'
            << setw(2) << setfill('0') << (local_time.tm_mon + 1) << '-'
            << setw(2) << setfill('0') << local_time.tm_mday << " "
            << setw(2) << setfill('0') << (local_time.tm_hour - 12) << ':'
            << setw(2) << setfill('0') << local_time.tm_min << ':'
            << setw(2) << setfill('0') << local_time.tm_sec << " " << am_pm << endl;
    }


    void select_choose_from_available()
    {
         cout << "For debugging :" << b_books.size() << endl;
         ifstream file("databaseforbooks.txt");
         if (b_books.size() == 0)
         {
             cout << "The system has not any books, sorry try latter\n";
             System();
         }
         else
         {
            
           
            cout << "The books in our system: \n";
            
            for (int i = 0; i < b_books.size(); i++)
            {
                cout << "[" << i + 1 << "] " << b_books[i].title<<" ISBN : "<<b_books[i].ISBN << '\n';
            }
            cout << "Which book to read? (from 1 to " << b_books.size() << "): ";
            cout << "please enter the isbn of this book : ";
            int number_book;
            while (file >> number_book)
            {
                for (int j = 0;j < b_books.size();j++)
                {
                    if (number_book == b_books[j].ISBN)
                    {
                        cout << "Now ,you are reading : ";
                        cout << b_books[j].title << endl;
                    }
                    else
                    {
                        cout << "invalid isbn try again\n";
                        menu_user();
                    }
                }
               
            }
            reading.push_back(b_books[number_book - 1].title);

            //int c_page = 1;
            cout << "Current Page [1/" << b_books[number_book - 1].pages << "]\n";
          
            while (true)
            {
                //maping pages
                cout << "Menu:\n";
                cout << setw(5) << "[1] Next page\n";
                cout << setw(5) << "[2] Previous page\n";
                cout << setw(5) << "[3] Stop reading\n";
                cout << setw(5) << "Choose [1-3]: ";
                int cho;
                cin >> cho;

                if (cho == 1 && c_page < b_books[number_book - 1].pages)
                {
                    c_page++;
                    cout << "Page: " << c_page << '\n';
                }
                else if (cho == 2 && c_page > 1) {
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
       
         
    }

    void select_choose_from_history()
    {
        for (int j = 0; j < reading.size(); j++)
        {
            cout << j + 1 << ". " << reading[j] << endl;
            //this is not done why?
            cout << "the page you have stopped at [" << c_page << " ]" << endl;
            time_date();
          
        }
    }

    void Log_out()
    {
        return;
    }

    void menu_user()
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
    void System();
    void menu_two()
    {
       //i wanna need to add option to remove the book
        cout << "Menu\n";
        cout << setw(5) << "[1] View profile\n";
        cout << setw(5) << "[2] Add books\n";
        cout << setw(5) << "[3] back\n";
        int choice_menu;
        cin >> choice_menu;
        if (choice_menu == 1)
        {
            profile();
        }
        else if (choice_menu == 2)
        {
            
            add_book("databaseforbooks.txt");
        }
        else if (choice_menu == 3)
        {
            System();
        }
        else
        {
            cout << "Invalid choice, try again\n";
        }
    }

    void log_in()
    {
        string na, pa;
        cout << "Name: ";
        cin >> name_ad;
        cout << "Password: ";
        cin >> pass;
        ifstream s_i("databaseforadmin.txt");
        while (s_i >> na >> pa)
        {
            if (na == name_ad && pa == pass)
            {
                cout << "logged in successfully \n";
                cout << "Hello " << name_ad << " | Admin view\n";
            }
            else
            {
                cout << "Logged in error\n";
                log_in();
            }
        }
        s_i.close();
    }

    void sign_up()
    {
        cout << "Name: ";
        cin >> name_ad;
        cout << "Password: ";
        cin >> pass;
        ofstream s_a("databaseforadmin.txt", ios::app);
        s_a << name_ad << " " << pass << endl;
        s_a.close();
        cout << "Hello " << name_ad << " | Admin view\n";
    }

    void menu_admin()
    {
        cout << "Menu\n";
        cout << setw(5) << "[1] Log in\n";
        cout << setw(5) << "[2] Sign Up\n";
        cout << setw(5) << "[3] Back\n";
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
        else if (ch == 3)
        {
            System();
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
    cout << "You're the admin or user?\n";
    cout << setw(5) << "[1] Admin\n";
    cout << setw(5) << "[2] User\n";

    while (true)
    {
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
//the problems
//not print the name or email after the view profile
//more restriction on the data to be more secure
//maping the pages in the books and to show the page you stopped at
//database for books
//if the system is empty say the system is empty and this also for the history of the user
