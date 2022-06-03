
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include "Publication.h"

using namespace std;

namespace sdds {
	Publication::Publication() {
		m_title = nullptr;
		for (int i = 0; i < 4; i++) {
			m_shelfId[i] = '\0';
		}
		m_membership = 0;
		m_libRef = -1;
		m_date = Date();
	}

	Publication::Publication(const Publication& copy) {
		m_title = nullptr;
		*this = copy;
	}
	Publication& Publication::operator=(const Publication& copyFrom) {
		if (this != &copyFrom) {
			if (copyFrom.m_title != nullptr) {
				delete[] m_title;
				m_title = new char[strlen(copyFrom.m_title) + 1];
				strcpy(m_title, copyFrom.m_title);
			}
			strcpy(m_shelfId, copyFrom.m_shelfId);
			m_membership = copyFrom.m_membership;
			m_date = copyFrom.m_date;
			m_libRef = copyFrom.m_libRef;
		}
		else {
			*this = Publication();
		}
		return *this;
	}
	Publication::~Publication() {
		delete[] m_title;
		m_title = nullptr;
	}

	void Publication::set(int member_id) {
		m_membership = member_id;
	}
	void Publication::setRef(int value) {
		m_libRef = value;
	}
	void Publication::resetDate() {
		Date date;
		m_date = date;
	}

	char Publication::type() const {
		return 'P';
	}
	bool Publication::onLoan() const {
		bool flag = false;
		if (m_membership != 0) {
			flag = true;
		}
		return flag;
	}
	Date Publication::checkoutDate() const {
		return m_date;
	}
	bool Publication::operator==(const char* title) const {
		bool flag = false;
		if (strstr(m_title, title)) {
			flag = true;
		}
		return flag;
	}
	Publication::operator const char* () const {
		return m_title;
	}
	int Publication::getRef() const {
		return m_libRef;
	}

	bool Publication::conIO(ios& io) const {
		bool flag = false;
		if (&io == &cin || &io == &cout) {
			flag = true;
		}
		return flag;
	}
	ostream& Publication::write(ostream& os) const {
		if (conIO(os)) {
			os << "| ";
			os << m_shelfId;
			os << " | ";
			if (strlen(m_title) > SDDS_TITLE_WIDTH) {
				for (int i = 0; i < SDDS_TITLE_WIDTH; i++) {
					os << m_title[i];
				}
			}
			else {
				os.width(SDDS_TITLE_WIDTH);
				os.fill('.');
				os << left << m_title;
			}
			os.fill(' ');
			os << " | ";
			if (m_membership != 0) {
				os << m_membership;
			}
			else {
				os << " N/A ";
			}
			os << " | ";
			os << m_date;
			os << " |";
		}
		else {
			os << type() << "\t" << getRef() << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << checkoutDate();
		}
		return os;
	}
	istream& Publication::read(istream& in) {
		int memberID = 0;
		int libRef = 0;
		Date date;
		char shelfId[SDDS_SHELF_ID_LEN + 1];
		char title[256];
		if (conIO(in)) {
			std::cout << "Shelf No: ";
			in.getline(shelfId, SDDS_SHELF_ID_LEN + 1);
			std::cout << "Title: ";
			in.getline(title, 256);
			if (strlen(title) <= 0)
			{
				in.setstate(ios::failbit);
			}
			std::cout << "Date: ";
			in >> date;
			if (date.errCode()) {
				in.setstate(ios::failbit);
			}
		}
		else {
			in >> libRef;
			in.ignore(1000, '\t');
			in.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
			in.getline(title, 1000, '\t');
			in >> memberID;
			in.ignore(1000, '\t');
			in >> date;
			if (date.errCode()) {
				in.setstate(ios::failbit);
			}
		}
		if (in) {
			strcpy(m_shelfId, shelfId);
			m_title = new char[strlen(title) + 1];
			strcpy(m_title, title);
			m_membership = memberID;
			m_libRef = libRef;
			m_date = date;
		}
		return in;
	}
	Publication::operator bool() const {
		bool flag = false;
		if (m_title != nullptr && m_title[0] != '\0' && m_shelfId[0] != '\0') {
			flag = true;
		}
		return flag;
	}
}