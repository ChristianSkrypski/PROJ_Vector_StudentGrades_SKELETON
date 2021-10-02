#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

#include "../includes/constants.h"
#include "../includes/utilities.h"
using namespace std;

//if you are debugging the file must be in the project parent directory
std::string DoubleToString(double Number) {
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

//if myString does not contain a string rep of number returns 0
//if int not large enough has undefined behaviour, 
//this is a very fragile function
//ex. string a="3";
//    int i = stringToInt(a.c_str()); //i contains 3
//    a="s";
//    i = stringToInt(a.c_str()); //i receives 0
int stringToInt(const char *myString) {
	return atoi(myString);
}

//if myString does not contain a string rep of number returns 0
//this is a very fragile function
//ex. string b="4.5";
//    double d = stringToDouble(b.c_str()); //d receives 4.5
double stringToDouble(const char *myString) {
	return atof(myString);
}
int readFile(std::string &file, std::vector<KP::studentData> &allstudentData, char separator_char) {
	// Parameters used to read in each line from the file using stringstream and see if the file is open
	std::string line;
	std::string token;
	KP::studentData myStudentData;
	stringstream ss;
	fstream my_file;
	// Clear the vector
	allstudentData.clear();
	// Attempt to open the file
	my_file.open(file, ios::in);
	// Check if the file is open
	if(!my_file.is_open()){
		return KP:: COULD_NOT_OPEN_FILE;
	}
	// Get the data from each line in the file, place it in the struct, and add it to the vector
	while (std::getline(my_file, line)) {
		ss.clear();
		ss.str(line);
		myStudentData.clear();
		std:: getline(ss, myStudentData.name, ' ');
		std:: getline(ss, token, ' ');
		myStudentData.midterm1 = stringToInt(token.c_str());
		std:: getline(ss, token, ' ');
		myStudentData.midterm2 = stringToInt(token.c_str());
		if (std:: getline(ss, token, ' ')) {
			std:: getline(ss, token, ' ');
			myStudentData.finalgrade = stringToInt(token.c_str());
		}
		allstudentData.push_back(myStudentData);
	}
	return KP:: SUCCESS;
}
int calculateFinalGrade(std::vector<KP::studentData> &allstudentData) {
	// Check if the vector is empty
	if(allstudentData.empty()) {
			return KP:: VECTOR_CONTAINS_NO_STUDENTS;
	}
	// Create a pointer to iterate through the vector
	std::vector<KP::studentData>::iterator iter = allstudentData.begin();
	// Calculate the final grade for each student
	for (iter = allstudentData.begin(); iter != allstudentData.end(); ++iter){
		(*iter).finalgrade = ((*iter).midterm1+(*iter).midterm2)/2;
	}
	return KP:: SUCCESS;
}
int writeFile(std::string &file, std::vector<KP::studentData> &allstudentData, char separator_char){
	// Reference to the file
	fstream my_file;
	// See if the vector is empty
	if(allstudentData.empty()) {
			return KP:: VECTOR_CONTAINS_NO_STUDENTS;
	}
	// Create an iterator to iterate through the vector
	std::vector<KP::studentData>::iterator iter = allstudentData.begin();
	// Open the file to write to
	my_file.open(file, ios::out);
	// See if the file is open
	if(!my_file.is_open()){
		return KP:: COULD_NOT_OPEN_FILE;
	}
	// Write the data from the vector to the file
	for (iter = allstudentData.begin(); iter != allstudentData.end(); ++iter){
		std:: string mid1 = DoubleToString((*iter).midterm1);
		std:: string mid2 = DoubleToString((*iter).midterm2);
		std:: string final = DoubleToString((*iter).finalgrade);
		my_file << (*iter).name << " " << mid1 << " " << mid2 << " " << final << "\n";
	}
	// Close the file
	my_file.close();
	return KP:: SUCCESS;
}
// Used to sort the students alphabetically by name
bool compareName (KP:: studentData& x, KP:: studentData& y) {
	return x.name < y.name;
}
// Used to sort the students from highest to lowest final grade
bool compareFinal (KP:: studentData& x, KP:: studentData& y){
	return x.finalgrade > y.finalgrade;
}
int sortStudentData(std::vector<KP::studentData> &allstudentData,KP::SORT_TYPE st) {
	// See if the vector is empty
	if(allstudentData.empty()) {
		return KP:: VECTOR_CONTAINS_NO_STUDENTS;
	}
	// If the students are sorted by name
	if (st == KP:: NAME){
		std:: sort(allstudentData.begin(), allstudentData.end(), compareName);
	}
	// If the students are sorted by final grade
	else if (st == KP:: FINAL_GRADE) {
		std:: sort(allstudentData.begin(), allstudentData.end(), compareFinal);
	}
	return KP:: SUCCESS;
}


