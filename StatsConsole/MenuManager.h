#pragma once

#include <string>
#include <unordered_map>
#include <functional>


namespace StatsConsole
{
	// A simple menu item: text and a function
	struct MenuItem
	{
		std::string text;
		std::function<bool(const std::string& prompt)> action;
	};

	// A collection of menu items
	using MenuItems = std::unordered_map<std::string, MenuItem>;

	// A class to manage the menu items
	class MenuManager
	{
	public:
		// Destructor
		~MenuManager() = default;

		// Move constructor
		MenuManager(MenuManager&& other) noexcept = delete;

		// Move assignment
		MenuManager& operator=(MenuManager&& other) noexcept = delete;

		// Copy constructor
		MenuManager(const MenuManager& other) = delete;

		// Copy assignment
		MenuManager& operator=(const MenuManager& other) = delete;

		// Creator
		static const MenuManager& Instance(const MenuItems& menu) {
			static MenuManager single(menu);
			return single;
		}

		// Print the menu
		void PrintMenu() const;

		// Process the user selection (input)
		bool ProcessSelection() const;

	private:
		// Constructor
		explicit MenuManager(const MenuItems& menu)
			: m_menu(menu)
		{}

		// A collection of menu items
		MenuItems m_menu;
	};
}
