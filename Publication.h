
#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H
#include<iostream>
#include "Date.h"
#include "Lib.h"
#include "Streamable.h"

namespace sdds {
	class Publication : public Streamable {
		char* m_title;
		char m_shelfId[SDDS_SHELF_ID_LEN + 1];
		int m_membership;
		int m_libRef;
		Date m_date;
	public:
		Publication();

		Publication(const Publication& copy);
		Publication& operator=(const Publication& copyFrom);
		~Publication();

		virtual void set(int member_id);
		void setRef(int value);
		void resetDate();

		virtual char type() const;
		bool onLoan() const;
		Date checkoutDate() const;
		bool operator==(const char* title) const;
		operator const char* () const;
		int getRef() const;

		bool conIO(std::ios& io) const;
		virtual std::ostream& write(std::ostream& os) const;
		virtual std::istream& read(std::istream& in);
		operator bool() const;
	};
}
#endif // !SDDS_PUBLICATION_H
