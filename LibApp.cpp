
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <cstring>
#include <string.h>
#include "LibApp.h"
#include "Menu.h"
#include "Publication.h"
#include "Book.h"
#include"PublicationSelector.h"

using namespace std;

namespace sdds {
	LibApp::LibApp() : m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_pub_Type("Choose the type of publication:") {
		m_changed = false;
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";

		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";

		m_pub_Type << "Book" << "Publication";

		load();
	}
	LibApp::LibApp(const char fname[]) :m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_pub_Type("Choose the type of publication:") {
		strcpy(filename, fname);
		m_changed = false;
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";

		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";

		m_pub_Type << "Book" << "Publication";

		load();
	}

	LibApp::~LibApp()
	{
		for (int i = 0; i < NOLP; i++) {
			delete PPA[i];
			PPA[i] = nullptr;
		}
	}

	void LibApp::prnPub(Publication* p[], int size, int ref) {
		int i;
		for (i = 0; i < size; i++) {
			if (ref == p[i]->getRef()) {
				cout << *p[i] << endl;
				i = size;
			}
		}
	}
	bool LibApp::confirm(const char* message) {
		Menu menu(message);
		menu << "Yes";
		int flag = (int)menu.run();
		return  flag == 1;
	}
	void LibApp::load() {
		cout << "Loading Data" << endl;
		ifstream infile(filename);
		int i;
		char type{};
		NOLP = 0;
		for (i = 0; infile || i < SDDS_LIBRARY_CAPACITY; i++) {

			infile >> type;
			infile.ignore();
			if (infile) {
				if (type == 'P')
					PPA[i] = new Publication;
				else if (type == 'B')
					PPA[i] = new Book;
				if (PPA[i]) {
					infile >> *PPA[i];
					NOLP = NOLP + 1;
				}
			}
		}
		LLRN = PPA[NOLP - 1]->getRef();
	}
	void LibApp::save() {
		cout << "Saving Data" << endl;
		ofstream outfile(filename);
		int i;

		for (i = 0; i < NOLP; i++)
		{
			if (PPA[i]->getRef() != 0) {
				outfile << *PPA[i];
				outfile << endl;
			}
		}
	}
	int LibApp::search(char type, int option) {

		PublicationSelector p("Select one of the following found matches:", 15);

		cout << "Publication Title: ";
		char title[256];
		cin.getline(title, 256);
		switch (option) {
		case 1:
			for (int i = 0; i < NOLP; i++) {
				if (strstr(*PPA[i], title) && PPA[i]->getRef() != 0 && type == PPA[i]->type()) {
					p << PPA[i];
				}
			}
			break;
		case 2:
			for (int i = 0; i < NOLP; i++) {
				if (strstr(*PPA[i], title) && PPA[i]->onLoan() && PPA[i]->getRef() != 0 && type == PPA[i]->type()) {
					p << PPA[i];
				}
			}
			break;
		case 3:
			for (int i = 0; i < NOLP; i++) {
				if (strstr(*PPA[i], title) && !PPA[i]->onLoan() && PPA[i]->getRef() != 0 && type == PPA[i]->type()) {
					p << PPA[i];
				}
			}
			break;
		default:
			break;
		}

		int ref = 0;
		if (p) {

			p.sort();

			ref = (int)p.run();
			if (ref) {
				prnPub(PPA, NOLP, ref);
			}
			else {
				cout << "Aborted!" << endl;
			}
		}
		else {
			cout << "No matches found!" << endl;
		}

		return ref;
	}
	Publication* LibApp::getPub(int libRef) {

		Publication* p = nullptr;
		for (int i = 0; i < NOLP; i++)
		{
			if (PPA[i]->getRef() == libRef) {
				p = PPA[i];

			}

		}

		return p;
	}
	void LibApp::returnPub() {
		cout << "Return publication to the library" << endl;
		char type = '\0';

		int flag = m_pub_Type.run();

		if (flag == 1) {
			type = 'B';
		}
		else if (flag == 2) {
			type = 'P';
		}
		else {
			cout << "No data found!";
		}

		int ref = search(type, 2);

		if (ref)
		{
			if (confirm("Return Publication?"))
			{
				float loan;
				Date d;
				int noOfdays = d.diffValue() - getPub(ref)->checkoutDate().diffValue();
				if (noOfdays > 15)
				{
					noOfdays -= 15;
					loan = (float)noOfdays * 0.5;
					cout << "Please pay $";
					std::cout << std::fixed;
					std::cout << std::setprecision(2);
					cout << loan;
					cout << " penalty for being ";
					cout << noOfdays - 15;
					cout << " days late!" << endl;
				}

				cout << "Publication returned";
				m_changed = true;

			}
		}

	}

	void LibApp::newPublication() {
		if (NOLP == SDDS_LIBRARY_CAPACITY)
		{
			cout << "Library is at its maximum capacity!" << endl;
		}
		else
		{
			cout << "Adding new publication to the library" << endl;

			int typ = m_pub_Type.run();

			if (typ != 0) {
				if (typ == 2)
					PPA[NOLP] = new Publication;
				else if (typ == 1)
					PPA[NOLP] = new Book;
				cin >> *PPA[NOLP];

				if (cin)
				{
					if (confirm("Add this publication to the library?"))
					{
						if (PPA[NOLP])
						{
							LLRN = LLRN + 1;
							PPA[NOLP]->setRef(LLRN);
							NOLP = NOLP + 1;
							m_changed = true;
							cout << "Publication added";
						}
						else
						{
							cout << "Failed to add publication!" << endl;
							delete PPA[NOLP];
						}
					}
					else {
						m_changed = false;
						cout << "Aborted!" << endl;;
					}
				}
				else
				{
					cout << "Aborted!" << endl;
				}
			}
			else
				cout << "Aborted!" << endl;
		}
	}
	void LibApp::removePublication() {
		cout << "Removing publication from the library" << endl;
		int runs = (int)m_pub_Type.run();
		char type = '\0';
		if (runs == 1) {
			type = 'B';
		}
		else {
			type = 'P';
		}
		int ref = search(type, 1);
		if (ref)
		{
			if (confirm("Remove this publication from the library?"))
			{
				Publication* p = getPub(ref);
				p->setRef(0);

				m_changed = true;
				cout << "Publication removed";

			}
			else
				m_changed = false;
		}
		else
		{
			cin.clear();
		}

	}
	void LibApp::checkOutPub() {
		cout << "Checkout publication from the library" << endl;
		int runs = (int)m_pub_Type.run();
		char type = '\0';
		if (runs == 1) {
			type = 'B';
		}
		else {
			type = 'P';
		}
		int ref = search(type, 3);
		if (ref)
		{
			int mem = 0;
			if (confirm("Check out publication?"))
			{
				int flag = 1;
				cout << "Enter Membership number: ";
				cin >> mem;
				while (flag)
				{


					if (mem < 99999 && mem > 10000)
					{
						flag = 0;
					}
					else {
						cout << "Invalid membership number, try again: ";
						cin >> mem;
						cin.ignore(1000, '\n');
					}

				}
				m_changed = true;
				cout << "Publication checked out" << endl;
				Publication* p = getPub(ref);
				p->set(mem);
			}
			else
				m_changed = false;
		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
	void LibApp::run() {
		bool loop = true;
		do {
			int Flag = (int)m_mainMenu.run();
			if (Flag == 1) {
				newPublication();
				cout << endl << endl;
			}
			else if (Flag == 2) {
				removePublication();
				cout << endl;
			}
			else if (Flag == 3) {
				checkOutPub();
				cout << endl;
			}
			else if (Flag == 4) {
				returnPub();
				cout << endl;
			}
			else {
				if (m_changed) {
					unsigned int Flag = m_exitMenu.run();
					switch (Flag) {
					case 1:
						save();
						loop = false;
						break;
					case 2:
						cout << endl;
						break;
					default:
						if (confirm("This will discard all the changes are you sure?")) {
							loop = false;
							break;
						}
						else {
							cout << endl;
							break;
						}
					}
				}
				else {
					loop = false;
					break;
				}
			}
		} while (loop);

		cout << "-------------------------------------------\n";
		cout << "Thanks for using Seneca Library Application\n";

	}

}