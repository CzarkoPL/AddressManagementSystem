/**
* Author: Cezary Chromicz
* Index: 229772
*/

#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"
/* https://github.com/friedmud/variadic_table */
#include "VariadicTable.h"

using namespace std;

void printHeader();
void printMainMenu();
int printRow(void*, int, char**, char**);
void showAllResults();
void handleUserSelection();

const char* DB_NAME = "addressDB.db";
sqlite3* db;
VariadicTable<string, string, string, string, string, string, string, string> table({ "ID", "Forename", "Surname", "Zip Code", "City", "Street", "House No.", "Flat No." });

int main() {
    if (sqlite3_open(DB_NAME, &db)) {
        cout << "Can't open database: " << sqlite3_errmsg(db);
        return -1;
    }

    handleUserSelection();

    sqlite3_close(db);
    return 0;
}

void printHeader() {
    cout << "########################################\n"
        << "# Welcome to Address Managment System! #\n"
        << "########################################\n\n";
}

void printMainMenu() {
    cout << "1) Show all addresses\n"
        << "2) Add new address\n"
        << "3) Modify address\n"
        << "4) Delete address\n"
        << "5) Display sorted data\n"
        << "6) Exit\n";
}

int printRow(void* _, int columns, char** columnValues, char** columnNames) {
    table.addRow(columnValues[0], columnValues[1], columnValues[2], columnValues[3], columnValues[4], columnValues[5], columnValues[6], columnValues[7]);
    return 0;
}

void showAllResults() {
    system("cls");
    char* errmsg = 0;
    const char* sql = "SELECT * FROM ADDRESSES";

    cout << "All results:\n\n";

    int result = sqlite3_exec(db, sql, printRow, 0, &errmsg);

    if (result != SQLITE_OK) {
        cout << "Error occured: " << errmsg;
    }

    table.print(cout);

    system("pause");
    handleUserSelection();
}

void handleUserSelection() {
    bool firstCall = true;
    int option = 0;

    while (option == 0) {
        system("cls");
        printHeader();
        if (!firstCall && option == 0) {
            cout << "Invalid option was selected!\n";
        }
        firstCall = false;
        printMainMenu();

        cout << "Select an option: ";
        string optionString;
        cin >> optionString;
        try {
            option = stoi(optionString);
            if (option < 1 || option > 6) {
                option = 0;
            }
        }
        catch (exception& e) {
            option = 0;
        }
    }

    switch (option) {
    case 1:
        //show all
        showAllResults();
        break;
    case 2:
        //add
        break;
    case 3:
        //update
        break;
    case 4:
        //delete
        break;
    case 5:
        //show sorted
        break;
    case 6:
        //exit
        cout << "\nThanks for using :)\n";
        exit(0);
        break;
    }
}