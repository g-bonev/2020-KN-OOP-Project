#include "book.h"
class Library
{
    Book *books[MAXN];
    int firstFreeIndex();
    void DeleteBook(int idx);
    void CopyFrom(const Library& other);
	void Free();
public:
    Library();
    Library(const Library& other);
    Library& operator=(const Library& other);
	~Library();
    void AddBook(const char* author, const char* title, const char* genre, const char* description, int yearOfRelease, int rating, int isbn);
    void AddBook(const Book& other);
    void Print() const;
    void Info(int isbn) const;
    void FindTitle(const char* title);
    void FindAuthor(const char* author);
    void Save(const char* fileName);
    bool RemoveBook(int isbn);
};
int Library::firstFreeIndex()
{
	for (int i = 0; i < MAXN; i++)
	{
		if (books[i] == nullptr)
			return i;
	}
}
void Library::CopyFrom(const Library& other)
{
	for (int i = 0; i < MAXN; i++)
	{
		if (other.books[i] == nullptr)
			books[i] = nullptr;
		else
		{
			books[i] = new Book(*other.books[i]);
		}
	}
}
void Library::Free()
{
	for (int i = 0; i < MAXN; i++)
		delete books[i];
}
Library::Library()
{
    for (int i = 0; i < MAXN; i++)
		books[i] = nullptr;
}

void Library::AddBook(const char* author, const char* title, const char* genre, const char* description, int yearOfRelease, int rating, int isbn)
{
    int idx = firstFreeIndex();
	books[idx] = new Book(author, title, genre, description, yearOfRelease, rating, isbn);
}
void Library::AddBook(const Book& other)
{
    int idx = firstFreeIndex();
    books[idx] = new Book(other);
}
Library::Library(const Library& other)
{
	CopyFrom(other);
}
Library& Library::operator=(const Library& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
Library::~Library()
{
	Free();
}
void Library::Print() const
{
    for(int i=0;i<MAXN;i++)
	{
		if (books[i])
		{
			books[i]->Print();
		}
	}
}
void Library::Info(int isbn) const
{
    for(int i=0;i<MAXN;i++)
	{
		if(books[i])
		{
		    if(books[i]->GetISBN()==isbn)
            {
                books[i]->Info();
                break;
            }
		}
	}
}
void Library::FindTitle(const char* title)
{
    for(int i=0;i<MAXN;i++)
	{
		if(books[i])
		{
		    if(strcmp(books[i]->GetTitle(), title)==0)
            {
                books[i]->Info();
                break;
            }
		}
	}
}
void Library::FindAuthor(const char* author)
{
    for(int i=0;i<MAXN;i++)
	{
		if(books[i])
		{
		    if(strcmp(books[i]->GetAuthor(), author)==0)
            {
                books[i]->Info();
                break;
            }
		}
	}
}
void Library::Save(const char* fileName)
{
    std::ofstream outf;
    outf.open(fileName, ios::trunc);
    for(int i=0;i<MAXN;i++)
	{
		if(books[i])
		{
		    outf<<books[i]->GetTitle()<<"|"<<books[i]->GetAuthor()<<"|"<<books[i]->GetGenre()<<"|"<<
		    books[i]->GetDescription()<<"|"<<books[i]->GetYear()<<"|"<<books[i]->GetRating()<<"|";
		}
	}
	outf.close();
}
void Library::DeleteBook(int idx)
{
	delete books[idx];
	books[idx]=nullptr;
}
bool Library::RemoveBook(int isbn)
{
    for(int i=0;i<MAXN;i++)
	{
		if(books[i]->GetISBN()==isbn)
		{
			this->DeleteBook(i);
			return true;
		}
	}
	return false;
}
