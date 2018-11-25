/*
 Birthday Database class
 =======================
 This class serves to function as a means to hold pairs of names and birthdates of people in a file log.
 It can collect pairs from a file, add, remove, and modify people, and finally write to a given output file.
 It contains internal menu functions to avoid need for complicated driver programs.
 */

#include "BinarySearchTree.h"
#include "Person.h"

#ifndef BirthdayDatabase_h
#define BirthdayDatabase_h

void clearNewLineChar();

class BirthdayDatabase
{
private:
    std::string inputFileAddress; // address for file to be read from
    std::string nameOutputFileAddress; // address for names based BST to be traversed and printed
    std::string dateOutputFileAddress; // address for dates based BST to be traversed and printed
    BinarySearchTree<Person> treeByName; // BST based on Person's names
    BinarySearchTree<Person> treeByDate;  // BST based on Person's birthdates
    
    void internalModifyPerson(Person&); // takes user input for given Person's name and date
    void internalMenu(int); // procceses user input for menu choice in main menu method
    bool readFromInputFile(); // parses the given inout file, and assuming it is in the correct format, fills the two BST's in the class
    void writeToOutputFiles(); // perfroms different traversal sets and writes the trees to the appropriate output files
    void clearInput(); // clears std::cin due to an innaproriate value entered by the user
    void pressEnterToContinue(); // asks user to respond with ENTER key to continue operations
    void insertIntoBothTrees(Person&); // inserts a Person object into both trees, changes sorting bool in Person appropriately
    void removeFromBothTrees(Person&); // removes a person object from both trees, changes sorting bool in Person appropriately
    
    bool getInputFile(); // has user enter input file address and returns true if it can be read from
    
public:
    BirthdayDatabase(std::string);
    void displayMenu(); // offers users operations and sends the choice to the internal menu method
    /*
     This method takes a string, and if it contains only alphabet letters returns true with correct letters capitalized and others not
     Pre: string name
     Post: name is appropriately formatted
     Return: true if name is valid
     */
    bool nameFormatter(std::string&);
    
    /*
     This method has a user give input for the creation of a new Person object, and adds it to both trees.
     Calls on BST insert function.
     Pre: none
     Post: Person added to both trees
     Return: true if Person added
     */
    bool addEntry();
    
    /*
     This method has a user give input for the removal of a Person object, and removes it from both trees if it is found in them.
     Calls on BST remove function.
     Pre: none
     Post: Person removed from both trees
     Return: true if Person removed
     */
    bool removeEntry();
    
    /*
     This method allows user to modify an entry in both trees based on a name entered. It calls upon the internal modification method.
     Pre: none
     Post: Person in trees modified if given name found
     Return: true if succesful in modifying
     */
    bool modifyEntry();
    
    /*
     This method prints the name and birthdate of a Person in both trees based on a given name, if found.
     Pre: none
     Post: information printed to console
     Return: none
     */
    void displayEntry();
    
};

/*
 Public Functions
 */

BirthdayDatabase::BirthdayDatabase(std::string outputFile)
{
    this->nameOutputFileAddress = outputFile + "/NamesOutput.txt";
    this->dateOutputFileAddress = outputFile + "/DatesOutput.txt";
    
    while(!this->getInputFile())
    {
        std::cout << "Error: input file could not be read properly, try again..." << std::endl;
    }
    
    pressEnterToContinue();
}

void BirthdayDatabase::displayMenu()
{
    int menuChoice = 0;
    while (menuChoice != 7)
    {
        std::cout << "[1] -- View Entry" << std::endl;
        std::cout << "[2] -- Modify Entry" << std::endl;
        std::cout << "[3] -- Add Entry" << std::endl;
        std::cout << "[4] -- Remove Entry" << std::endl;
        std::cout << "[5] -- Display Database Tree by Name" << std::endl;
        std::cout << "[6] -- Display Database Tree by Date" << std::endl;
        std::cout << "[7] -- Exit and Save to Files" << std::endl;
        std::cout << "--> ";
        std::cin >> menuChoice;
        if (std::cin.fail() || menuChoice < 1 || menuChoice > 7)
        {
            clearInput();
            std::cout << "*** invalid menu choice ***" << std::endl;
            menuChoice = 0;
            pressEnterToContinue();
        }
        else
            internalMenu(menuChoice);
    }
    this->writeToOutputFiles();
}

bool BirthdayDatabase::nameFormatter(std::string &name)
{
    for (int index = 0; index < name.length(); index++)
    {
        if (name[index] < 65 || name[index] > 90)
            if ((name[index] < 97 || name[index] > 122) && name[index] != ' ')
            {
                // if name is not a letter, either captial or lowercase
                return false;
            }
        if (index == 0 && name[index] > 90) // if first letter and not capitalized
            name[index] -= 32; // capitalize
        else if (index == 0 && name[index] <= 90)
            continue; // else leave as is
        else if (name[index] == ' ' && name[index + 1] > 90) // if space and next letter not capitalized
        {
            name[++index] -= 32; // capitalize
            index++; // skip two spaces
            continue;
        }
        else if(name[index] == ' ' && name[index + 1] <= 90) // if space and is capitalized
        {
            index += 2; // leave as is and skip two indeces
            continue;
        }
        else if (name[index] >= 65 && name[index] <= 90) // if capitalized otherwise
            name[index] += 32; // make lowercase
    }
    return true;
}

bool BirthdayDatabase::addEntry()
{
    bool validInput = false;
    std::string name, date;
    Person newPerson;
    
    while (!validInput)
    {
        std::cout << "Name for new entry: ";
        getline(std::cin, name);
        if (nameFormatter(name)) // if name is valid inpit
        {
            newPerson.setName(name);
            validInput = true;
        }
        else std::cout << "Name input invalid, input must only use alphabet letters!" << std::endl;
    }
    
    validInput = false;
    
    while (!validInput)
    {
        std::cout << "Date (yyyy/mm/dd): ";
        getline(std::cin, date);
        Date newDate;
        try {
            newDate.updateDate(date); //  will throw an exception if invalid input to method
            newPerson.setDate(newDate);
            validInput = true;
        }
        catch(char const* errorMessage)
        {
            std::cout << errorMessage << " -- Provide new date in (yyyy/mm/dd) format please!" << std::endl;
        }
    }
    this->insertIntoBothTrees(newPerson); // add new Person with valid input to both trees
    std::cout << "'" << name << "' has been added to this database." << std::endl;
    return true;
}

bool BirthdayDatabase::removeEntry()
{
    Person::sortByName();
    Person searchPerson;
    std::string nameToFind;
    std::cout << "Name of entry to remove: ";
    getline(std::cin, nameToFind);
    if (nameFormatter(nameToFind) && this->treeByName.findForModification(Person(nameToFind), searchPerson)) // if name is found in Name tree
    {
        removeFromBothTrees(searchPerson);
        std::cout << "'" << nameToFind << "' has been removed from this database." << std::endl;
        return true;
    }
    std::cout << "'" << nameToFind << "' is not present in this database, try again." << std::endl; // if name not found
    return false;
}

bool BirthdayDatabase::modifyEntry()
{
    Person::sortByName();
    Person updatedPerson;
    
    std::string name;
    std::cout << "Name to edit --> ";
    getline(std::cin, name);
    
    if (nameFormatter(name) && this->treeByName.findForModification(Person(name), updatedPerson)) // if name found in Name tree
    {
        this->treeByName.remove(updatedPerson); // remove this person from Name tree
        Person::sortByDate();
        this->treeByDate.remove(updatedPerson); // remove this person from Date tree
        
        this->internalModifyPerson(updatedPerson); // will update the Person
        
        this->insertIntoBothTrees(updatedPerson); // then it will add this Person back to both trees
        
        return true;
    }
    else
    {
        std::cout << "Sorry, could't find '" << name << "' ..." << std::endl; // if name not found
        return false;
    }
}

void BirthdayDatabase::displayEntry()
{
    Person personToDisplay;
    Person::sortByName();
    std::string name;
    std::cout << "Name to search --> ";
    getline(std::cin, name);
    
    if (nameFormatter(name) && this->treeByName.findForModification(Person(name), personToDisplay)) // if name found in Name tree
    {
        std::cout << personToDisplay << std::endl; // print the Person's information
    }
    else
    {
        std::cout << "Sorry, could't find '" << name << "' ..." << std::endl; // if name not found
    }
}

/*
 Private Functions
 */

void BirthdayDatabase::internalModifyPerson(Person &personToUpdate)
{
    Person temp;
    std::string name, date;
    std::cout << "Name [Press ENTER to keep '" << personToUpdate.getName() << "' as name]: ";
    getline(std::cin, name);
    if (name != "" && nameFormatter(name)) // if user gave new valid name
        personToUpdate.setName(name);
    std::cout << "Date (yyyy/mm/dd) [Press ENTER to keep '" << personToUpdate.getBirthday() << "' as date]: ";
    getline(std::cin, date);
    if (date != "")
    {
        Date temp;
        try {
            temp.updateDate(date);
            personToUpdate.setDate(temp); // if user gave new valid Date
        }
        catch(char const* errorMessage) // else the Date will not be changed
        {
            std::cout << errorMessage << " -- " << personToUpdate.getName() << "'s birthdate shall remain " << personToUpdate.getBirthday() << std::endl;
        }
    }
}

bool BirthdayDatabase::readFromInputFile()
{
    std::ifstream inputFile;
    inputFile.open(this->inputFileAddress);
    if (inputFile)
    {
        while (!inputFile.eof())
        {
            std::string name, date;
            getline(inputFile, name);
            getline(inputFile, date);
            Person newPerson(name, date); // creates new Person for each file entry
            this->insertIntoBothTrees(newPerson); // adds to both trees
        }
        inputFile.close();
        return true;
    }
    return false;
}

void BirthdayDatabase::writeToOutputFiles()
{
    std::ofstream namesOutput;
    namesOutput.open("/Users/matanbroner/Desktop/NamesOutput.txt");
    if (namesOutput)
    {
        namesOutput << "=== Pre-Order Traversal of Names BST ===" << std::endl << std::endl;
        this->treeByName.preOrderTraversal(this->treeByName.retrieveRootPointer(), namesOutput);
        namesOutput << "=== Post-Order Traversal of Names BST ===" << std::endl << std::endl;
        this->treeByName.postOrderTraversal(this->treeByName.retrieveRootPointer(), namesOutput);
        namesOutput.close();
    }
    
    std::ofstream datesOutput;
    datesOutput.open("/Users/matanbroner/Desktop/DatesOutput.txt");
    if (datesOutput)
    {
        datesOutput << "=== In-Order Traversal of Dates BST ===" << std::endl << std::endl;
        this->treeByDate.inOrderTraversal(this->treeByDate.retrieveRootPointer(), datesOutput);
        datesOutput << "=== Breadth-First Traversal of Dates BST ===" << std::endl << std::endl;
        this->treeByDate.breadthFirstTraversal(this->treeByDate.retrieveRootPointer(), datesOutput);
        datesOutput.close();
    }
}

void BirthdayDatabase::clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // removes illegal value
}

void BirthdayDatabase::pressEnterToContinue()
{
    std::cout << "Press ENTER to continue...";
    std::cin.get();
    system("clear");
}

void BirthdayDatabase::insertIntoBothTrees(Person &newPerson)
{
    // changes Person sort boolean accordingly
    Person::sortByName();
    this->treeByName.insert(newPerson);
    Person::sortByDate();
    this->treeByDate.insert(newPerson);
}

void BirthdayDatabase::removeFromBothTrees(Person &newPerson)
{
    // changes Person sort boolean accordingly
    Person::sortByName();
    this->treeByName.remove(newPerson);
    Person::sortByDate();
    this->treeByDate.remove(newPerson);
}

void BirthdayDatabase::internalMenu(int choice)
{
    clearNewLineChar();
    switch (choice)
    {
        case 1: displayEntry(); break;
        case 2: modifyEntry(); break;
        case 3: addEntry(); break;
        case 4: removeEntry(); break;
        case 5: this->treeByName.printTree(this->treeByName.retrieveRootPointer(), 0); break;
        case 6: this->treeByDate.printTree(this->treeByDate.retrieveRootPointer(), 0); break;
        case 7: std::cout << "Saving output files and exiting... goodbye!" << std::endl; break;
        default: std::cout << "invalid menu option..." << std::endl;
    }
    pressEnterToContinue();
}

bool BirthdayDatabase::getInputFile()
{
    std::cout << "Please provide a COMPLETE input file address [this includes the name of the file]" << std::endl;
    std::cout << "--> ";
    getline(std::cin, this->inputFileAddress);
    if (this->readFromInputFile()) // if valid input file given
        return true;
    else return false;
}

void clearNewLineChar()
{
    std::cin.ignore();
}


#endif /* BirthdayDatabase_h */
