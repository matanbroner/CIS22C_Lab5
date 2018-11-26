#include "Datatype.h"
#include "BST.h"
#include <fstream>
#include <iostream>

void getInputFile(std::ifstream& input) {
	std::string inputFile = "";
	do {
		std::cout << "Please enter the input file name:" << std::endl;
		std::getline(std::cin, inputFile);
		input.open(inputFile, std::ifstream::in);

		if (!input.is_open()) {
			system("cls||clear");
			std::cout << "Error opening file \"" << inputFile << "\" for reading" << std::endl;
			std::cin.clear();	// clear error flag
			//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (!input.is_open());
}

void menu() {
	std::ifstream input;
	std::ofstream birthdayOutput, nameOutput;
	
	std::cout << "Welcome to Lab 5: BST for sorting by name and birth date." << std::endl;
//	get input file from user
	getInputFile(input);

	std::string naOutFile = "NamesOutput.txt";
	std::string bdOutFile = "BirthdaysOutput.txt";
	nameOutput.open(naOutFile, std::ofstream::out | std::ofstream::app);
	birthdayOutput.open(bdOutFile, std::ofstream::out | std::ofstream::app);

//	create and populate bsts with inputfile
	BST<name> names;
	BST<birthdate> birthdates;

	std::string tempFirst, tempLast, tempBirth;

	while (!input.eof()) {
		std::getline(input, tempFirst, ' ');
		std::getline(input, tempLast, ' ');
		std::getline(input, tempBirth, '\n');

		name tempName{ tempFirst, tempLast, tempBirth };
		birthdate tempBirthdate{ tempFirst, tempLast, tempBirth };

		names.add(tempName);
		birthdates.add(tempBirthdate);
	}

// name pre, post transversal
	nameOutput << "Sorted by name" << std::endl;
	//nameOutput << "---------------------" << std::endl;

	nameOutput << std::endl;
	nameOutput << "Pre-order traversal:" << std::endl;
	nameOutput << "---------------------" << std::endl;
	names.preOrder(names.getRootptr(), nameOutput);

	nameOutput << std::endl << std::endl;
	nameOutput << "Post-order traversal:" << std::endl;
	nameOutput << "---------------------" << std::endl;
	names.postOrder(names.getRootptr(), nameOutput);

	nameOutput << std::endl;

	//nameOutput << std::endl << std::endl;
	//nameOutput << "end of program output" << std::endl;
	//nameOutput << "---------------------" << std::endl;

// birthday, inorder,breadth traversals
	birthdayOutput << "Sorted by Birthdate" << std::endl;
	//birthdayOutput << "---------------------" << std::endl;

	birthdayOutput << std::endl;
	birthdayOutput << "In-order traversal:" << std::endl;
	birthdayOutput << "---------------------" << std::endl;
	birthdates.inOrder(birthdates.getRootptr(), birthdayOutput);

	birthdayOutput << std::endl << std::endl;
	birthdayOutput << "Breadth traversal:" << std::endl;
	birthdayOutput << "---------------------" << std::endl;
	birthdates.breadthFirst(birthdates.getRootptr(), birthdayOutput);

	birthdayOutput << std::endl;

	//birthdayOutput << std::endl << std::endl;
	//birthdayOutput << "end of program output" << std::endl;
	//birthdayOutput << "---------------------" << std::endl;


	// close
	input.close();
	birthdayOutput.close();
	nameOutput.close();

	system("cls||clear");
	std::cout << "Input file processed, please check \"" << naOutFile << "\" and \"" << bdOutFile << "\" for output." << std::endl;
	std::cout << "Program closing..." << std::endl;
}