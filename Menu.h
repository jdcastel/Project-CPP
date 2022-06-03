

#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_
#include<iostream>

namespace sdds
{
	const int MAX_MENU_ITEMS = 20;

	class Menu;

	class MenuItem
	{
	public:
		MenuItem(const char* menuItem);
	private:
		friend class Menu;
		char* menu_item{};

		MenuItem();
		void setEmpty();

		MenuItem(const MenuItem& menuItem) = delete;
		MenuItem& operator=(const MenuItem& menuItem) = delete;

		~MenuItem();

		operator bool() const;
		operator const char* () const;
		std::ostream& display(std::ostream& os) const;
	};

	class Menu
	{
		friend class LibApp;
		char* menu_title;
		MenuItem* menu_items_ptr[MAX_MENU_ITEMS] = { nullptr };
		int menu_num;
	public:
		Menu();
		Menu(const char* menuTitle);
		void setEmpty();

		Menu(const Menu& menu) = delete;
		Menu& operator=(const Menu& menu) = delete;

		~Menu();

		std::ostream& displayTitle(std::ostream& os) const;
		std::ostream& displayMenu(std::ostream& ostr) const;

		unsigned int run();
		unsigned int operator~();
		Menu& operator<<(const char* menuitemContent);

		operator int() const;
		operator unsigned int();
		operator bool() const;

		char* operator[](int index) const;

		bool isEmpty() const;

		std::ostream& operator<<(std::ostream& os);
	};
}

#endif // !SDDS_MENU_H_