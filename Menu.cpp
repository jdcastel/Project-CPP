

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <cstring>
#include <ctime>
#include "Menu.h"

using namespace std;

namespace sdds
{
	MenuItem::MenuItem() {
		menu_item = nullptr;
	}
	MenuItem::MenuItem(const char* menuItem) {
		if (menuItem != nullptr && menuItem[0] != '\0') {
			delete[] menu_item;
			menu_item = new char[strlen(menuItem) + 1];
			strcpy(this->menu_item, menuItem);
		}
		else {
			setEmpty();
		}
	}
	void MenuItem::setEmpty() {
		menu_item = nullptr;
	}

	MenuItem::~MenuItem() {
		delete[] menu_item;
		menu_item = nullptr;
	}

	MenuItem::operator bool() const {
		return menu_item != nullptr && menu_item[0] != '\0';
	}
	MenuItem::operator const char* () const {
		return menu_item;
	}

	std::ostream& MenuItem::display(std::ostream& os) const {
		if (*this) {
			os << menu_item;
		}
		return os;
	}


	Menu::Menu() {
		menu_num = 0;
		menu_title = nullptr;
		for (int i = 0; i < MAX_MENU_ITEMS; i++) {
			menu_items_ptr[i] = nullptr;
		}
	}
	Menu::Menu(const char* menuTitle) {
		setEmpty();
		if (menuTitle != nullptr && menuTitle[0] != '\0') {
			delete[] menu_title;
			menu_title = new char[strlen(menuTitle) + 1];
			strcpy(menu_title, menuTitle);
		}
	}
	void Menu::setEmpty() {
		menu_num = 0;
		menu_title = nullptr;
		for (int i = 0; i < MAX_MENU_ITEMS; i++) {
			menu_items_ptr[i] = nullptr;
		}
	}

	Menu::~Menu() {
		delete[] menu_title;
		menu_title = nullptr;
		for (int i = 0; i < MAX_MENU_ITEMS; i++) {
			delete menu_items_ptr[i];
			menu_items_ptr[i] = nullptr;
		}
	}

	std::ostream& Menu::displayTitle(std::ostream& os) const {
		if (!isEmpty()) {
			os << menu_title;
			os << endl;
		}
		return os;
	}
	std::ostream& Menu::displayMenu(std::ostream& ostr) const {
		displayTitle(ostr);
		for (int i = 0; i < menu_num; i++) {
			ostr.width(2);
			ostr.fill(' ');
			ostr.setf(ios::right);
			ostr << i + 1;
			ostr.unsetf(ios::right);
			ostr << "- ";
			menu_items_ptr[i]->display(ostr);
			ostr << endl;
		}
		ostr << " 0- Exit\n";
		ostr << "> ";
		return ostr;
	}

	unsigned int Menu::run() {
		int flag = 0;
		displayMenu(std::cout);
		int selection = 0;
		do {
			cin >> selection;
			flag = 0;
			cin.clear();
			cin.ignore(256, '\n');
			if (selection < 0 || selection > menu_num || !cin) {
				cout << "Invalid Selection, try again: ";
				flag = 1;
			}
		} while (flag == 1);
		return static_cast<unsigned int>(selection);
	}
	unsigned int Menu::operator~() {
		int flag = 0;
		displayMenu(std::cout);
		int selection = 0;
		do {
			cin.clear();
			cin >> selection;
			flag = 0;
			if (selection < 0 || selection > menu_num || !cin) {
				cout << "Invalid Selection, try again: ";
				flag = 1;
			}
			cin.clear();
			cin.ignore(256, '\n');
		} while (flag == 1);
		return static_cast<unsigned int>(selection);
	}
	Menu& Menu::operator<<(const char* menuitemContent) {
		if (menu_num < MAX_MENU_ITEMS) {
			menu_items_ptr[menu_num] = new MenuItem(menuitemContent);
			menu_num += 1;
		}
		return *this;
	}

	Menu::operator int() const {
		return menu_num;
	}
	Menu::operator unsigned int() {
		return menu_num;
	}
	Menu::operator bool() const {
		int count = 0;
		for (int i = 0; i < MAX_MENU_ITEMS; i++) {
			if (menu_items_ptr[i] != nullptr) {
				count++;
				break;
			}
		}
		return count > 0;
	}

	char* Menu::operator[](int index) const {
		int newIndex = 0;
		newIndex = (index % menu_num);
		return menu_items_ptr[newIndex]->menu_item;
	}

	bool Menu::isEmpty() const {
		return menu_title == nullptr;
	}

	ostream& Menu::operator<<(ostream& os) {
		if (!isEmpty()) {
			displayTitle(os);
		}
		return os;
	}
}