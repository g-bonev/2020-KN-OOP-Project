#include <iostream>
#include <fstream>
#include <cstring>
#define MAXN 4096
using namespace std;
class User
{
    char username[MAXN];
    char password[MAXN];
    bool admin;
    bool isInit;
public:
    User();
    User(const char* username, const char* password, bool admin);
    const char* getUsername() const;
    const char* getPassword() const;
    bool getAdmin() const;
    bool getIsInit() const;
};
User::User()
{
    strcpy(this->username, "");
    strcpy(this->password, "");
    this->admin=false;
    this->isInit=false;
}
User::User(const char* username, const char* password, bool admin)
{
    this->admin=admin;
    this->isInit=true;
    strcpy(this->username, username);
    strcpy(this->password, password);
}
const char* User::getUsername() const
{
    return this->username;
}
const char* User::getPassword() const
{
    return this->password;
}
bool User::getAdmin() const
{
    return this->admin;
}
bool User::getIsInit() const
{
	return this->isInit;
}
