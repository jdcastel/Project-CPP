
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include "Publication.h"
namespace sdds {
	class Book : public Publication {
		char* m_authorName{};
	public:
		Book();

		Book(const Book& copy);
		Book& operator=(const Book& copyBook);
		~Book();

		char type() const;
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& in);
		void set(int member_id);
		operator bool() const;

		void setName(const char* authorname);
	};
}
#endif // !SDDS_BOOK_H