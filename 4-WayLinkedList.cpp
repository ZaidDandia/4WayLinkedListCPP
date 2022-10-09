/**
 * @file LinkedList.cpp
 * @author Zaid Dandia (2021719), Tahir Muzaffar (2021665)
 * @brief  A telephone directory using a 4-Way linked list
 * @version 0.1
 * @date 2022-10-07
 */
#include <iostream>
#include <string> // for working with strings
#include <regex>  // for validating inputs of user by regular expressions
#include <limits> // for getting the maximum limit of the input stream buffer
using namespace std;

string regexPatternEmail = "[a-zA-Z0-9\\._-]+@([a-z]+)(\\.[a-z]+)+";
regex regexRuleEmail(regexPatternEmail);
string regexPatternPhoneNumber = "03[0-9]{9}";
regex regexRulePhoneNumber(regexPatternPhoneNumber);

struct details
{
    string phoneNumber;
    string name;
    string address;
    string email;
    friend ostream &operator<<(ostream &output, const details &d)
    {
        if (d.email.length() != 0)
        {
            output << "Phone Number: " << d.phoneNumber << endl;
            output << "Name: " << d.name << endl;
            output << "Address: " << d.address << endl;
            output << "Email: " << d.email << endl;
        }
        else
        {
            output << "Phone Number: " << d.phoneNumber << endl;
            output << "Name: " << d.name << endl;
            output << "Address: " << d.address << endl;
        }
        return output;
    }
    friend istream &operator>>(istream &input, details &d)
    {
        string option;
        while (1)
        {
            cout << "Enter the Phone Number (e.g: 03xxxxxxxxx): ";
            input >> d.phoneNumber;
            bool isValidPhoneNumber = regex_match(d.phoneNumber, regexRulePhoneNumber);
            if (isValidPhoneNumber)
            {
                break;
            }
            cout << "Invalid input, please try again." << endl;
        }
        cin.ignore();
        cout << "Enter the Name: ";
        getline(input, d.name);
        cout << "Enter the Address: ";
        getline(input, d.address);
        while (1)
        {
            cout << "Do you want to enter email? (yes/no) ";
            getline(input, option);
            if (option == "yes" || option == "y" || option == "Yes" || option == "Y")
            {
                while (1)
                {
                    cout << "Enter the Email (e.g: johndoe92@mail.com): ";
                    input >> d.email;
                    bool isValidEmail = regex_match(d.email, regexRuleEmail);
                    if (isValidEmail)
                    {
                        break;
                    }
                    cout << "Invalid input, please try again." << endl;
                }
                break;
            }
            else if (option == "no" || option == "n" || option == "No" || option == "n")
            {
                break;
            }
            else
            {
                cout << "Invalid input, please try again." << endl;
            }
        }
        return input;
    }
};

class LinkedList
{
private:
    details data;
    LinkedList *next;
    LinkedList *prev;
    LinkedList *above;
    LinkedList *below;
    static LinkedList *ListHeadPtr;
    static LinkedList *TailPtr;
    int cur_pos = 1;
    static int rows;
    static int col;

public:
    /**
     * @brief Constructor for initializing the rows and the columns of the telephone directory
     * Time Complexity : O(1);
     */
    LinkedList(int x)
    {
        while (1)
        {
            cout << "Please enter the number of rows: " << endl;
            cin >> rows;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please try again." << endl;
                // cout << "Please enter the number of rows: " << endl;
            }
            else
            {
                break;
            }
        }
        while (1)
        {
            cout << "Please enter the number of columns: " << endl;
            cin >> col;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please try again." << endl;
                // cout << "Please enter the number of columns: " << endl;
            }
            else
            {
                break;
            }
        }
    }
    /**
     * @brief Copy Constructor for initializing the new variables without changing the rows and the columns
     * Time Complexity : O(1);
     */
    LinkedList()
    {
        rows = rows;
        col = col;
    }
    /**
     * @brief A function that checks if there's space left in the telephone directory
     * Time Complexity : O(1);
     */
    static bool isSpace()
    {
        int total = rows * col;
        if (TailPtr == NULL)
        {
            return true;
        }
        if (TailPtr->cur_pos < total)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    /**
     * @brief A function that creates the list
     * Time Complexity : O(1);
     */
    static void create_list()
    {
        ListHeadPtr = NULL;
    }
    /**
     * @brief A function that adds data at the start of the telephone directory
     * Time Complexity : O(n);
     */
    static void AddNodeAtHead()
    {

        if (!isSpace())
        {
            cout << "ERROR: The List is Full!" << endl;
            cout << "Please delete an Element from the list before adding a new Element!" << endl;
            return;
        }
        LinkedList *newPtr = new LinkedList;
        details val;
        cin >> val;
        if (ListHeadPtr->searchNode(val.phoneNumber) != NULL)
        {
            cout << "This Number is already in the list!" << endl;
            cout << "Please try again with a different phone number" << endl;
            return;
        }
        if (ListHeadPtr == NULL)
        {
            newPtr->data = val;
            newPtr->above = newPtr->below = NULL;
            newPtr->next = newPtr->prev = NULL;
            newPtr->cur_pos = 1;
            ListHeadPtr = TailPtr = newPtr;
            cout << "Successfully added" << endl;
            return;
        }

        newPtr->cur_pos = 1;
        newPtr->prev = NULL;
        newPtr->above = newPtr->below = NULL;
        newPtr->data = val;
        ListHeadPtr->prev = newPtr;
        newPtr->next = ListHeadPtr;
        ListHeadPtr = newPtr;
        LinkedList *tempPtr = ListHeadPtr;
        LinkedList *headRow = ListHeadPtr;
        int i = 0;
        while (tempPtr != NULL)
        {
            if (tempPtr->cur_pos % col == 0)
            {
                if (i != 0)
                {
                    headRow = headRow->below;
                }
                tempPtr->above = headRow;
                headRow->below = tempPtr;

                if (headRow->next->below != NULL)
                {
                    tempPtr->next = headRow->next->below;
                    tempPtr->next->prev = tempPtr;
                }
                tempPtr->prev->next = NULL;
                tempPtr->prev = NULL;
                tempPtr->cur_pos += 1;
                tempPtr = tempPtr->next;
                i++;
                continue;
            }
            if (tempPtr != ListHeadPtr)
            {
                tempPtr->cur_pos += 1;
            }
            tempPtr = tempPtr->next;
        }
        cout << "Successfully added!" << endl;
    }
    /**
     * @brief A function that adds data at the end of the telephone directory
     * Time Complexity : O(n);
     */
    static void AddNodeAtTail()
    {

        if (!isSpace())
        {
            cout << "ERROR: The List is Full!!" << endl;
            cout << "Please delete an Element from the list before adding a new Element!" << endl;
            return;
        }
        if(ListHeadPtr == NULL)
        {
            AddNodeAtHead();
            return;
        }
        details val;
        cin >> val;
        if (ListHeadPtr->searchNode(val.phoneNumber) != NULL)
        {
            cout << "This Number is already in the list!" << endl;
            cout << "Please try again with a different phone number" << endl;
            return;
        }
        LinkedList *tempPtr = new LinkedList;
        if (TailPtr->cur_pos % col != 0)
        {
            tempPtr->data = val;
            tempPtr->prev = TailPtr;
            TailPtr->next = tempPtr;
            if (TailPtr->above != NULL)
            {
                TailPtr->above->next->below = tempPtr;
                tempPtr->above = TailPtr->above->next;
            }
            tempPtr->next = NULL;
            tempPtr->cur_pos = TailPtr->cur_pos + 1;
            TailPtr = tempPtr;
        }
        else if (TailPtr->cur_pos % col == 0)
        {
            LinkedList *headPtr = ListHeadPtr;
            while (headPtr->below != NULL)
            {
                headPtr = headPtr->below;
            }
            tempPtr->data = val;
            tempPtr->cur_pos = TailPtr->cur_pos + 1;
            headPtr->below = tempPtr;
            tempPtr->above = headPtr;
            tempPtr->next = NULL;
            tempPtr->prev = NULL;
            TailPtr = tempPtr;
        }
        cout << "Successfully added!" << endl;
    }
    /**
     * @brief A function that displays data of a specific node in the telephone directory
     * Time Complexity : O(1);
     */
    void DisplayNode(LinkedList *ptr)
    {
        if (ptr == NULL)
        {
            cout << "Not Found!" << endl;
            return;
        }
        cout << endl;
        cout << ptr->data;
        cout << endl;
    }
    /**
     * @brief A function that searches for a node using phone number in the telephone directory
     * Time Complexity : O(n);
     */
    LinkedList *searchNode(string val)
    {
        LinkedList *tempPtr = ListHeadPtr;
        LinkedList *headRow = ListHeadPtr;
        while (tempPtr != NULL)
        {
            if (tempPtr->next == NULL)
            {
                if (tempPtr->data.phoneNumber == val)
                {
                    return tempPtr;
                }
                headRow = headRow->below;
                tempPtr = headRow;
            }
            else
            {
                if (tempPtr->data.phoneNumber == val)
                {
                    return tempPtr;
                }
                tempPtr = tempPtr->next;
            }
        }
        return NULL;
    }

    /**
     * @brief A function that searches for a node using name in the telephone directory
     * Time Complexity : O(n);
     */
    LinkedList *searchName(string val)
    {
        LinkedList *tempPtr = ListHeadPtr;
        LinkedList *headRow = ListHeadPtr;
        while (tempPtr != NULL)
        {
            if (tempPtr->next == NULL)
            {
                if (tempPtr->data.name == val)
                {
                    return tempPtr;
                }
                headRow = headRow->below;
                tempPtr = headRow;
            }
            else
            {
                if (tempPtr->data.name == val)
                {
                    return tempPtr;
                }
                tempPtr = tempPtr->next;
            }
        }
        return NULL;
    }
    /**
     * @brief A function that searches for a node using address in the telephone directory
     * Time Complexity : O(n);
     */
    LinkedList *searchAddress(string val)
    {
        LinkedList *tempPtr = ListHeadPtr;
        LinkedList *headRow = ListHeadPtr;
        while (tempPtr != NULL)
        {
            if (tempPtr->next == NULL)
            {
                if (tempPtr->data.address == val)
                {
                    return tempPtr;
                }
                headRow = headRow->below;
                tempPtr = headRow;
            }
            else
            {
                if (tempPtr->data.address == val)
                {
                    return tempPtr;
                }
                tempPtr = tempPtr->next;
            }
        }
        return NULL;
    }
    /**
     * @brief A function that searches for a node using email in the telephone directory
     * Time Complexity : O(n);
     */
    LinkedList *searchEmail(string val)
    {
        LinkedList *tempPtr = ListHeadPtr;
        LinkedList *headRow = ListHeadPtr;
        while (tempPtr != NULL)
        {
            if (tempPtr->next == NULL)
            {
                if (tempPtr->data.email == val)
                {
                    return tempPtr;
                }
                headRow = headRow->below;
                tempPtr = headRow;
            }
            else
            {
                if (tempPtr->data.email == val)
                {
                    return tempPtr;
                }
                tempPtr = tempPtr->next;
            }
        }
        return NULL;
    }
    /**
     * @brief A function that deletes a node in the telephone directory
     * Time Complexity : O(n);
     */
    int deleteNode(LinkedList *ptr)
    {

        if (ptr == NULL)
        {
            cout << "Not Found!" << endl;
            return -1;
        }
        else
        {
            LinkedList *tempPtr = ListHeadPtr;
            LinkedList *headRow = ListHeadPtr;
            LinkedList *temp = headRow->next;
            while (tempPtr != ptr)
            {
                if (tempPtr->next == NULL)
                {
                    headRow = headRow->below;
                    tempPtr = headRow;
                }
                else
                {
                    tempPtr = tempPtr->next;
                }
            }
            LinkedList *next;
            if (tempPtr->next == NULL)
            {
                next = headRow->below;
                headRow = headRow->below;
            }
            else
                next = tempPtr->next;

            while (tempPtr != NULL)
            {
                if (tempPtr == ListHeadPtr)
                {
                    if (ListHeadPtr->next == NULL)
                    {
                        ListHeadPtr->cur_pos = 0;
                        ListHeadPtr = NULL;
                        break;
                    }
                }
                if (tempPtr == TailPtr)
                {
                    tempPtr = tempPtr->prev;
                    if (tempPtr->next->above != NULL)
                    {
                        tempPtr->next->above->below = NULL;
                        tempPtr->next->above = NULL;
                    }
                    tempPtr->next = NULL;
                    TailPtr = tempPtr;
                    break;
                }
                if (next->next == NULL && next != TailPtr)
                {
                    tempPtr->data = next->data;
                    tempPtr = tempPtr->next;
                    next = headRow->below;
                    headRow = headRow->below;
                }
                else if (next == TailPtr)
                {
                    tempPtr->data = next->data;
                    TailPtr = tempPtr;
                    next->prev = NULL;
                    next->above->below = NULL;
                    next->above = NULL;
                    tempPtr->next = NULL;
                    break;
                }
                else
                {
                    tempPtr->data = next->data;
                    tempPtr = next;
                    next = next->next;
                }
            }

            return 1;
        }
    }
    /**
     * @brief A function that displays the whole telephone directory
     * Time Complexity : O(n);
     */
    void DisplayList()
    {
        LinkedList *tempPtr = ListHeadPtr;
        LinkedList *headRow = ListHeadPtr;
        if (tempPtr == NULL)
        {
            cout << "Empty Directory" << endl;
            return;
        }
        while (tempPtr != NULL)
        {
            if (tempPtr->next == NULL)
            {
                cout << endl;
                cout << tempPtr->data;
                cout << endl;
                headRow = headRow->below;
                tempPtr = headRow;
            }
            else
            {
                cout << endl;
                cout << tempPtr->data;
                cout << endl;
                tempPtr = tempPtr->next;
            }
        }
    }
};

LinkedList *LinkedList::ListHeadPtr = NULL;
LinkedList *LinkedList::TailPtr = ListHeadPtr;
int LinkedList::rows = 0;
int LinkedList::col = 0;
/**
 * @brief Main Function and also the menu for the telephone directory
 */
int main()
{

    string x;
    char choice;
    cout << "Welcome to your personal Telephone Directory!" << endl;
    cout << "X-------------------------------------------X" << endl;
    while (1)
    {
        cout << "Do you want to create your own directory? (yes/no)" << endl;
        cin >> x;
        if (x == "Y" || x == "y" || x == "yes" || x == "Yes")
        {
            LinkedList l(1);
            l.create_list();
            while (1)
            {
                cout << "Please Select an option..." << endl;
                cout << "1. Add Phone Number at the start" << endl;
                cout << "2. Add Phone Number at the end" << endl;
                cout << "3. Delete Phone Number" << endl;
                cout << "4. Display Directory" << endl;
                cout << "5. Search Phone Number in the directory" << endl;
                cout << "6. Search Name in the directory" << endl;
                cout << "7. Search Address in the directory" << endl;
                cout << "8. Search Email in the directory" << endl;
                cout << "9. Exit" << endl;
                cin >> choice;
                switch (choice)
                {
                case '1':
                {
                    l.AddNodeAtHead();
                    break;
                }
                case '2':
                {
                    l.AddNodeAtTail();
                    break;
                }
                case '3':
                {
                    string phone;
                    while (1)
                    {
                        cout << "Enter the Phone Number (e.g: 03xxxxxxxxx): ";
                        cin >> phone;
                        bool isValidPhoneNumber = regex_match(phone, regexRulePhoneNumber);
                        if (isValidPhoneNumber)
                        {
                            break;
                        }
                        cout << "Invalid input, please try again." << endl;
                    }
                    l.deleteNode(l.searchNode(phone));
                    break;
                }
                case '4':
                {
                    l.DisplayList();
                    break;
                }
                case '5':
                {
                    string phone;
                    while (1)
                    {
                        cout << "Enter the Phone Number (e.g: 03xxxxxxxxx): ";
                        cin >> phone;
                        bool isValidPhoneNumber = regex_match(phone, regexRulePhoneNumber);
                        if (isValidPhoneNumber)
                        {
                            break;
                        }
                        cout << "Invalid input, please try again." << endl;
                    }
                    l.DisplayNode(l.searchNode(phone));
                    break;
                }
                case '6':
                {
                    cin.ignore();
                    string name;
                    cout << "Enter the name: ";
                    getline(cin, name);
                    l.DisplayNode(l.searchName(name));
                    break;
                }
                case '7':
                {
                    cin.ignore();
                    string address;
                    cout << "Enter the address: ";
                    getline(cin, address);
                    l.DisplayNode(l.searchAddress(address));
                    break;
                }
                case '8':
                {
                    string email;
                    while (1)
                    {
                        cout << "Enter the Email (e.g: johndoe92@mail.com): ";
                        cin >> email;
                        bool isValidEmail = regex_match(email, regexRuleEmail);
                        if (isValidEmail)
                        {
                            break;
                        }
                        cout << "Invalid input, please try again." << endl;
                    }
                    l.DisplayNode(l.searchEmail(email));
                    break;
                }
                case '9':
                {
                    break;
                }
                default:
                {
                    cout << "Invalid option, please try again." << endl;
                    break;
                }
                }
                if (choice == '9')
                {
                    break;
                }
            }
            break;
        }
        else if (x == "N" || x == "n" || x == "no" || x == "No")
        {
            break;
        }
        else
        {
            cout << "Invalid option, please try again." << endl;
        }
    }
}