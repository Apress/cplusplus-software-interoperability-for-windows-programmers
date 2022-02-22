#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "MenuManager.h"

namespace StatsConsole 
{
    //
    // Print out the menu items
    //
	void MenuManager::PrintMenu() const
	{
		std::cout << "\n";

		for (const auto& i : m_menu)
		{
			const auto& key = i.first;
			const auto& item = i.second;
			std::cout << key << ". " << item.text << "\n";
		}
	}

    //
    // Obtain and process the user input
    //
	bool MenuManager::ProcessSelection() const
	{
		bool retval = true;
		std::cout << "Enter Selection> ";

        std::string selection;
		if (getline(std::cin, selection))
		{
			if (!selection.empty())
			{
				std::transform(selection.begin(), selection.end(), selection.begin(), std::toupper);
                const auto& it = m_menu.find(selection);
                if (it != m_menu.end())
                {
                    try
                    {
                        const auto& item = it->second;
                        // call operator() on the action function 
                        retval = item.action(item.text);
                    }
                    catch (const std::exception& e)
                    {
                        std::cout << e.what() << "\n";
                        retval = true;
                    }
                }
                else
                {
                    std::cout << "Unrecognised input selection. Please try again.\n";
                    retval = true;
                }
			}
		}
		return retval;
	}
}
