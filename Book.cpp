
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Book.h"

using namespace std;

namespace sdds {
	Book::Book() {}

	Book::Book(const Book& copy) {
		m_authorName = nullptr;
		*this = copy;
	}
	Book& Book::operator=(const Book& copyBook) {
		if (this != &copyBook) {
			Publication::operator=(copyBook);
			setName(copyBook.m_authorName);
		}
		else {
			m_authorName = nullptr;
		}
		return *this;
	}

	Book::~Book() {
		delete[] m_authorName;
		m_authorName = nullptr;
	}
	char Book::type() const {
		return 'B';
	}
	std::ostream& Book::write(std::ostream& os) const {
		Publication::write(os);
		if (Publication::conIO(os)) {
			os << " ";
			if (strlen(m_authorName) > SDDS_AUTHOR_WIDTH) {
				for (int i = 0; i < SDDS_AUTHOR_WIDTH; i++) {
					os << m_authorName[i];
				}
			}
			else {
				os.width(SDDS_AUTHOR_WIDTH);
				os.fill(' ');
				os << left << m_authorName;
			}
			os.fill(' ');
			os << " |";
		}
		else {
			os << "\t";
			os << m_authorName;
		}
		return os;
	}
	std::istream& Book::read(std::istream& in) {
		char authorName[256];
		Publication::read(in);
		delete[] m_authorName;
		if (Publication::conIO(in)) {
			in.ignore(1000, '\n');
			cout << "Author: ";
			in.getline(authorName, 256);
			if (strlen(authorName) <= 0) {
				in.setstate(ios::failbit);
			}
		}
		else {
			in.ignore(1000, '\t');
			in.get(authorName, 256, '\n');
			if (strlen(authorName) <= 0) {
				in.setstate(ios::failbit);
			}
		}
		if (in) {
			setName(authorName);
		}
		return in;
	}
	void Book::set(int member_id) {
		Publication::set(member_id);
		Publication::resetDate();
	}
	Book::operator bool() const {
		bool flag = false;
		if (m_authorName != nullptr && m_authorName[0] != '\0' && Publication::operator bool()) {
			flag = true;
		}
		return flag;
	}
	void Book::setName(const char* authorname) {
		if (m_authorName != nullptr) {
			delete[] m_authorName;
			m_authorName = nullptr;
		}
		if (authorname != nullptr && authorname[0] != '\0') {
			m_authorName = new char[strlen(authorname) + 1];
			strcpy(m_authorName, authorname);
		}
	}
}