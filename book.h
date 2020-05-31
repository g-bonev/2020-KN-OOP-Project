#include "user.h"
class Book
{
    char* author;
    char* title;
    char* genre;
    char* description;
    int yearOfRelease;
    int rating;
    int isbn;
    void CopyFrom(const Book& other);
	void Free();
public:
    Book();
    Book(const char* author, const char* title, const char* genre, const char* description, int yearOfRelease, int rating, int isbn);
    Book(const Book& other);
    Book& operator=(const Book& other);
	~Book();
	const char* GetTitle() const;
	const char* GetAuthor() const;
	const char* GetGenre() const;
	const char* GetDescription() const;
	int GetYear() const;
	int GetRating() const;
	int GetISBN() const;
	void Print() const;
	void Info() const;
};
void Book::CopyFrom(const Book& other)
{
    this->author = new char[strlen(other.author) + 1];
	strcpy(this->author, other.author);
    this->title = new char[strlen(other.title) + 1];
	strcpy(this->title, other.title);
	this->genre = new char[strlen(other.genre) + 1];
	strcpy(this->genre, other.genre);
	this->description = new char[strlen(other.description) + 1];
	strcpy(this->description, other.description);
	this->yearOfRelease=other.yearOfRelease;
	//
	this->rating=other.rating;
	this->isbn=other.isbn;
}
void Book::Free()
{
    delete[] author;
    delete[] title;
    delete[] genre;
    delete[] description;
}
Book::Book()
{
    rating=-1;
    isbn=-1;
}
Book::Book(const char* author, const char* title, const char* genre, const char* description, int yearOfRelease, int rating, int isbn)
{
    this->author = new char[strlen(author) + 1];
	strcpy(this->author, author);
    this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
	this->genre = new char[strlen(genre) + 1];
	strcpy(this->genre, genre);
	this->description = new char[strlen(description) + 1];
	strcpy(this->description, description);
	this->yearOfRelease=yearOfRelease;
	//
	this->rating=rating;
	this->isbn=isbn;
}
Book::Book(const Book& other)
{
    this->CopyFrom(other);
}
Book& Book::operator=(const Book& other)
{
    if (this != &other)
	{
		this->Free();
		this->CopyFrom(other);
	}
	return *this;
}
Book::~Book()
{
    this->Free();
}
int Book::GetISBN() const
{
    return this->isbn;
}
const char* Book::GetTitle() const
{
    return this->title;
}
const char* Book::GetAuthor() const
{
    return this->author;
}
const char* Book::GetGenre() const
{
    return this->genre;
}
const char* Book::GetDescription() const
{
    return this->description;
}
int Book::GetYear() const
{
    return this->yearOfRelease;
}
int Book::GetRating() const
{
    return this->rating;
}
void Book::Print() const
{
    std::cout<<title<<" by "<<author<<", "<<genre<<" #"<<isbn<<std::endl;
}
void Book::Info() const
{
    std::cout<<title<<" by "<<author<<", "<<genre<<" #"<<isbn<<std::endl<<description<<std::endl<<"Released in "<<yearOfRelease<<std::endl<<"Rating: "<<rating<<std::endl;
}
