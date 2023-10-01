#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// data structure used in creating our table
struct inventory
{
    string name;
    string description;
    int amount;
    float cost;
};

// function for writing user inputs into our struct format
inventory write_input()
{
    string name;
    string description;
    int amount;
    float cost;
    cout << "Building new line in table.\n";

    cout << "Please enter the name of the item.\n";
    cin.ignore(256, '\n');
    getline(cin, name);

    cout << "Please enter the description of the item.\n";
    getline(cin, description);

    cout << "Please enter the amount of the item stored (int).\n";
    cin >> amount;

    cout << "Please enter the cost of the item (float).\n";
    cin >> cost;

    inventory new_row = {name, description, amount, cost};
    return new_row;
}

int main()
{
    // initialize table by making a vector of our data structure
    vector<inventory> inventory_table;
    // initialize user input variables
    string user_input;
    string file_name;
    // welcome ^^
    cout << "Hello and Welcome to the table builder.\n";
    // loop to take user input repeatedly
    while (user_input != "end")
    {
        // list of acceptable commands and their uses
        cout << "If you would like to load a table file into the current table or a new table enter 'load'.\n";
        cout << "If you would like to save the current table enter 'save'.\n";
        cout << "If you would like to print the current table in a readable format enter 'print'.\n";
        cout << "If you would like to write input into the current table or a new table enter 'input'.\n";
        cout << "If you would like to clear the current table enter 'clear'.\n";
        cout << "If you would like to quit, enter 'end'.\n";
        // take user input
        cin >> user_input;

        // block for 'input' command
        if (user_input == "input")
        {
            while (user_input == "y" || user_input == "Y" || user_input == "input")
            {
                inventory_table.push_back(write_input());
                cout << "Write another line to the table? (Y/n)\n";
                cin >> user_input;
            }
        }

        // block for 'print' command
        else if (user_input == "print")
        {
            // build organized output for table
            cout << "\n";
            cout << "|-------------|------------------------------|--------|---------|\n";
            cout << "| Item        | Description                  | Amount | Cost    |\n";
            // loops through each of our inventory structs within our table
            for (int i = 0; i < inventory_table.size(); i++)
            {
                cout << "|-------------|------------------------------|--------|---------|\n";
                cout << "| ";
                cout << setw(12) << left << inventory_table[i].name;
                cout << "| ";
                cout << setw(29) << left << inventory_table[i].description;
                cout << "| ";
                cout << setw(7) << left << inventory_table[i].amount;
                cout << "| $";
                cout << setw(7) << left << setprecision(2) << fixed << inventory_table[i].cost;
                cout << "|\n";
            }
            cout << "|-------------|------------------------------|--------|---------|\n\n";
            // ask user if they wish to print the table shown directly to a file
            cout << "Print to file? (Y/n)\n";
            cin >> user_input;
            if (user_input == "Y" || user_input == "y")
            {
                // accept file name
                cout << "Enter a '.txt' file name. \n";
                cin >> file_name;
                ofstream PrintFile(file_name);
                // repeat process, but into file instead of cout
                PrintFile << "|-------------|------------------------------|--------|---------|\n";
                PrintFile << "| Item        | Description                  | Amount | Cost    |\n";
                for (int i = 0; i < inventory_table.size(); i++)
                {
                    PrintFile << "|-------------|------------------------------|--------|---------|\n";
                    PrintFile << "| ";
                    PrintFile << setw(12) << left << inventory_table[i].name;
                    PrintFile << "| ";
                    PrintFile << setw(29) << left << inventory_table[i].description;
                    PrintFile << "| ";
                    PrintFile << setw(7) << left << inventory_table[i].amount;
                    PrintFile << "| $";
                    PrintFile << setw(7) << left << setprecision(2) << fixed << inventory_table[i].cost;
                    PrintFile << "|\n";
                }
                PrintFile << "|-------------|------------------------------|--------|---------|\n\n";
                // don't forget to close file
                PrintFile.close();
                cout << "File printed successfully!";
            }
        }

        // block for save command
        else if (user_input == "save")
        {
            // prompt for file name
            cout << "Enter a '.txt' file name. \n";
            cin >> file_name;
            // open file
            ofstream SaveFile(file_name);
            // save each piece of data from our structs to a new line
            for (int i = 0; i < inventory_table.size(); i++)
            {
                SaveFile << inventory_table[i].name;
                SaveFile << "\n";
                SaveFile << inventory_table[i].description;
                SaveFile << "\n";
                SaveFile << inventory_table[i].amount;
                SaveFile << "\n";
                SaveFile << inventory_table[i].cost;
                SaveFile << "\n";
            }
            // be sure to close file
            SaveFile.close();
            cout << "File saved successfully!";
        }

        // block for 'load' command
        else if (user_input == "load")
        {
            // prompt file and inform on what type of file to give
            cout << "NOTE: Only 'saved' files can be loaded, trying to load a printed table will not work!\nEnter a '.txt' file name. \n";
            cin >> file_name;
            // open file
            ifstream LoadFile(file_name);
            string loaded_line;
            inventory saved_line;
            int i = 1;
            // because each piece of data is on a new line we need to know where it goes, we iterate through 4 repeating pieces of code for this.
            while (getline(LoadFile, loaded_line))
            {
                if (i == 1)
                {
                    saved_line.name = loaded_line;
                }
                else if (i == 2)
                {
                    saved_line.description = loaded_line;
                }
                else if (i == 3)
                {
                    saved_line.amount = stoi(loaded_line);
                }
                else if (i == 4)
                {
                    // push to vector and reset our iterator
                    saved_line.cost = stof(loaded_line);
                    inventory_table.push_back(saved_line);
                    i = 0;
                }
                i++;
            }
            // close file
            LoadFile.close();
            cout << "File Loaded Successfully!\n";
        }

        // block for clear command
        else if (user_input == "clear")
        {
            inventory_table.clear();
        }
    }

    return 0;
}