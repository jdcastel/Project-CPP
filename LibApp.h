
#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include <iostream>
#include "Lib.h"
#include "Menu.h"
#include "Publication.h"
#include "Book.h"

namespace sdds {
	class LibApp {
		bool m_changed;
		Menu m_mainMenu;
		Menu m_exitMenu;

		char filename[256];
		Publication* PPA[SDDS_LIBRARY_CAPACITY]{};
		int NOLP;
		int LLRN;
		Menu m_pub_Type;

		bool confirm(const char* message);
		void load();
		void save();
		int search(char, int);
		void returnPub();

		void newPublication();
		void removePublication();
		void checkOutPub();
	public:
		LibApp();
		LibApp(const char pubFileName[]);
		~LibApp();
		void prnPub(Publication* p[], int size, int ref);
		void run();
		Publication* getPub(int libRef);
	};
}
#endif // !SDDS_LIBAPP_H