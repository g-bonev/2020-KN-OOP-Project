#include "library.h"
Library library;
User users[MAXN];
int firstFreeIdx(User* arr)
{
    for (int i = 0; i < MAXN; i++)
	{
		if (!arr[i].getIsInit())
			return i;
	}
	return -1;
}
bool addUser(const char* username, const char* password, bool admin)
{
    for(int i=0;i<MAXN;i++)
    {
        if(strcmp(users[i].getUsername(), username)==0)
        {
            return false;
        }
    }
    int idx = firstFreeIdx(users);
    User newUser(username, password, admin);
    users[idx]=newUser;
    return true;
}
bool removeUser(const char* username)
{
    for(int i=0;i<MAXN;i++)
    {
        cout<<users[i].getUsername()<<endl;
        if(strcmp(users[i].getUsername(), username)==0)
        {
            User emptyUser;
            users[i]=emptyUser;
            return true;
        }
    }
    return false;
}
int main()
{
    bool openedFile=0;
    int loggedIn=0;// 0 - not logged in, 1 - client, 2 - admin
    ifstream inf;
    ofstream outf;
    char file[MAXN];
    char fileName[MAXN]={};
    addUser("admin", "i<3c++", true);
    for(char command[MAXN];cin.getline(command, MAXN);)
    {
        if(strncmp(command, "open ", 5)==0)
        {
            openedFile=1;
            strcpy(fileName, command+5);
            inf.open(fileName);
            if (inf.fail())
            {
                cout << "File not found, creating a new one." << endl;
                outf.open(fileName, ios::trunc);
                outf.close();
            }
            else
            {
                cout << "File successfully opened." <<endl;
                for(;!inf.fail();)
                {
                    char author[MAXN];
                    inf.getline(author, MAXN, '|');
                    char title[MAXN];
                    inf.getline(title, MAXN, '|');
                    char genre[MAXN];
                    inf.getline(genre, MAXN, '|');
                    char description[MAXN];
                    inf.getline(description, MAXN, '|');
                    int yearOfRelease=0;
                    char year[MAXN];
                    inf.getline(year, MAXN, '|');
                    for(int i=0;year[i]!='\0';i++)
                    {
                        yearOfRelease*=10;
                        yearOfRelease+=year[i]-'0';
                    }
                    int rating=0;
                    char Rating[MAXN];
                    inf.getline(Rating, MAXN, '|');
                    for(int i=0;Rating[i]!='\0';i++)
                    {
                        rating*=10;
                        rating+=Rating[i]-'0';
                    }
                    int isbn=0;
                    char ISBN[MAXN];
                    inf.getline(ISBN, MAXN, '|');
                    for(int i=0;ISBN[i]!='\0';i++)
                    {
                        isbn*=10;
                        isbn+=ISBN[i]-'0';
                    }
                    library.AddBook(author, title, genre, description, yearOfRelease, rating, isbn);
                }
                library.RemoveBook(0);
            }
            inf.close();
            continue;
        }
        if(strcmp(command, "help")==0)
        {
            cout<<"The following commands are supported:"<<endl;
            cout<<"open <file>                  opens <file>"<<endl;
            cout<<"close                        closes currently opened file"<<endl;
            cout<<"save                        saves the currently open file"<<endl;
            cout<<"saveas <file>                   saves the currently open file in <file>"<<endl;
            cout<<"help                         prints this information"<<endl;
            cout<<"exit                         exits the program"<<endl;
            cout<<"login                          inquires username and password to log in"<<endl;
            cout<<"logout                         logs the logged in user out"<<endl;
            cout<<"books all                         prints a bit of information for every book in the library"<<endl;
            cout<<"books info <isbn>            prints detailed information about the book with the given isbn"<<endl;
            cout<<"books find <option> [title|author] prints detailed information about the book with the given title|author"<<endl;
            cout<<"users add <user> <password>      adds a new client user"<<endl;
            cout<<"users remove <user>          removes given user"<<endl;
            continue;
        }

        if(strcmp(command, "exit")==0)
        {
            cout<<"Exiting the program..."<<endl;
            return 0;
        }
        if (strcmp(command, "login")==0)
        {
            if(loggedIn)
            {
                cout<<"You are already logged in."<<endl;
                continue;
            }
            cout<<"Please enter username"<<endl;
            char username[MAXN], password[MAXN];
            int foundUser=-1;
            cin.getline(username, MAXN);
            for(int i=0;i<MAXN;i++)
            {
                if(strcmp(username, users[i].getUsername())==0)
                {
                    foundUser=i;
                    break;
                }
            }
            if(foundUser==-1)
            {
                cout<<"Username not recognized. Aborting login."<<endl;
            }
            else
            {
                cout<<"Please enter password"<<endl;
                cin.getline(password, MAXN);
                if(strcmp(password, users[foundUser].getPassword())==0)
                {
                    if(users[foundUser].getAdmin()) loggedIn=2;
                    else loggedIn=1;
                    cout<<"Welcome, "<<users[foundUser].getUsername()<<"!"<<endl;
                }
                else
                {
                    cout<<"Wrong password. Aborting login."<<endl;
                }
            }
            continue;
        }
        if (strncmp(command, "logout ", 7)==0)
        {
            if(loggedIn==0)
            {
                cout<<"You are not logged in."<<endl;
                continue;
            }
            loggedIn=0;
            cout<<"You have been logged out."<<endl;
            continue;
        }
        if(!openedFile)
        {
            cout<<"Error: no file opened."<<endl;
            continue;
        }
        if(strcmp(command, "close")==0)
        {
            openedFile=0;
            cout<<"File successfully closed."<<endl;
            continue;
        }
        if (strncmp(command, "save", 4)==0)
        {
            if(strncmp(command, "saveas ", 7)==0)
            {
                char name[MAXN];
                strcpy(name, command+7);
                library.Save(name);
            }
            else if(strncmp(command, "save", 4)==0)
            {
                library.Save(fileName);
            }
            cout<<"File successfully saved."<<endl;
            continue;
        }
        if(strncmp(command, "books ", 6)==0)
        {
            if(loggedIn==0)
            {
                cout<<"You are not logged in."<<endl;
                continue;
            }
            if(strncmp(command+6, "all", 3)==0)
            {
                library.Print();
                continue;
            }
            if(strncmp(command+6, "info ", 5)==0)
            {
                int isbn=0;
                for(int isbnLength=0;*(command+11+isbnLength)!='\0';isbnLength++)
                {
                    isbn*=10;
                    isbn+=*(command+11+isbnLength)-'0';
                }
                library.Info(isbn);
                continue;
            }
            if(strncmp(command+6, "find ", 5)==0)
            {
                if(strncmp(command+11, "title ", 6)==0)
                {
                    char title[MAXN];
                    int titleLength;
                    for(titleLength=0;*(command+17+titleLength)!='\0';titleLength++)
                    {
                        title[titleLength]=*(command+17+titleLength);
                    }
                    title[titleLength]='\0';
                    library.FindTitle(title);
                    continue;
                }
                if(strncmp(command+11, "author ", 7)==0)
                {
                    char author[MAXN];
                    int authorLength;
                    for(authorLength=0;*(command+18+authorLength)!='\0';authorLength++)
                    {
                        author[authorLength]=*(command+18+authorLength);
                    }
                    author[authorLength]='\0';
                    library.FindAuthor(author);
                    continue;
                }
            }
            if(loggedIn==1)
            {
                cout<<"Administrator only command."<<endl;
                continue;
            }
            if(strncmp(command+6, "remove ", 7)==0)
            {
                int isbn=0;
                for(int isbnLength=0;*(command+13+isbnLength)!='\0';isbnLength++)
                {
                    isbn*=10;
                    isbn+=*(command+13+isbnLength)-'0';
                }
                if(library.RemoveBook(isbn))
                {
                    cout<<"Book successfully removed"<<endl;
                }
                else cout<<"Book with given ISBN not found"<<endl;
                continue;
            }
        }
        if(strncmp(command, "users ", 6)==0)
        {
            if(loggedIn==0)
            {
                cout<<"You are not logged in."<<endl;
                continue;
            }
            if(loggedIn==1)
            {
                cout<<"Administrator only command."<<endl;
                continue;
            }
            if(strncmp(command+6, "add ", 4)==0)
            {
                char username[MAXN]={}, password[MAXN]={};
                int nameLength, passLength;
                for(nameLength=0;*(command+10+nameLength)!=' ';nameLength++)
                {
                    username[nameLength]=*(command+10+nameLength);
                }
                for(passLength=0;*(command+10+nameLength+1+passLength)!='\0';passLength++)
                {
                    password[passLength]=*(command+10+nameLength+1+passLength);
                }
                if(addUser(username, password, false)) cout<<"User successfully added."<<endl;
                else cout<<"User already exists."<<endl;
                continue;
            }
            if(strncmp(command+6, "remove ", 7)==0)
            {
                inf.open("credentials.txt");
                bool userFound=0;
                int nameLength=strlen(command+13);
                if(removeUser(command+13)) cout<<"User successfully removed."<<endl;
                else cout<<"User not found."<<endl;
                continue;
            }
        }
        cout<<"Invalid command."<<endl;
    }
}
