//#include <iterator>
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
	std::string line;
	std::string token;
	KP::studentData myStudentData;
	stringstream ss;
	fstream my_file;
	allstudentData.clear();
	my_file.open(file, ios::in);
	if(!my_file.is_open()){
		return KP:: COULD_NOT_OPEN_FILE;
	}
	while (std::getline(my_file, line)) {
		ss.clear();
		ss.str(line);
		myStudentData.clear();
		//while (std:: getline(ss, token)){
		std:: getline(ss, myStudentData.name, ' ');
		std:: getline(ss, token, ' ');
		myStudentData.midterm1 = stringToInt(token.c_str());
		std:: getline(ss, token, ' ');
		myStudentData.midterm2 = stringToInt(token.c_str());
		if (std:: getline(ss, token, ' ')) {
			std:: getline(ss, token, ' ');
			myStudentData.finalgrade = stringToInt(token.c_str());
		}
		//}
		allstudentData.push_back(myStudentData);
	}
	//while (!my_file.eof()){
		//getline(my_file, line);
		//ss.clear();
		//ss.str(line);
		//myStudentData.clear();
		//getline(ss, myStudentData.name, KP::SEPERATOR_CHAR);
		//getline(ss, token, KP::SEPERATOR_CHAR);
		//myStudentData.midterm1 = stringToInt(token.c_str());
		//getline(ss, token, KP::SEPERATOR_CHAR);
		//myStudentData.midterm2 = stringToInt(token.c_str());
		//if (getline(ss, token, KP::SEPERATOR_CHAR)) {
			//getline(ss, token, KP::SEPERATOR_CHAR);
			//myStudentData.finalgrade = stringToInt(token.c_str());
		//}
		//allstudentData.push_back(myStudentData);
	//}
	//int x = allstudentData.size();
	return KP:: SUCCESS;
}
int calculateFinalGrade(std::vector<KP::studentData> &allstudentData) {
	if(allstudentData.empty()) {
			return KP:: VECTOR_CONTAINS_NO_STUDENTS;
	}
	std::vector<KP::studentData>::iterator iter = allstudentData.begin();
	//if (iter == NULL){
	//	return KP:: VECTOR_CONTAINS_NO_STUDENTS;
	//}
	for (iter = allstudentData.begin(); iter != allstudentData.end(); ++iter){
		(*iter).finalgrade = ((*iter).midterm1+(*iter).midterm2)/2;
	}
	//int x = allstudentData.size();
	return KP:: SUCCESS;
}
int writeFile(std::string &file, std::vector<KP::studentData> &allstudentData, char separator_char){
	fstream my_file;
	if(allstudentData.empty()) {
			return KP:: VECTOR_CONTAINS_NO_STUDENTS;
	}
	std::vector<KP::studentData>::iterator iter = allstudentData.begin();
	my_file.open(file, ios::out);
	if(!my_file.is_open()){
		return KP:: COULD_NOT_OPEN_FILE;
	}
	//if (iter == NULL){
		//return KP:: VECTOR_CONTAINS_NO_STUDENTS;
	//}
	for (iter = allstudentData.begin(); iter != allstudentData.end(); ++iter){
		std:: string mid1 = DoubleToString((*iter).midterm1);
		std:: string mid2 = DoubleToString((*iter).midterm2);
		std:: string final = DoubleToString((*iter).finalgrade);
		my_file << (*iter).name << " " << mid1 << " " << mid2 << " " << final << "\n";
	}
	my_file.close();
	//int x = allstudentData.size();
	return KP:: SUCCESS;
}
bool compareName (KP:: studentData& x, KP:: studentData& y) {
	return x.name < y.name;
}
bool compareFinal (KP:: studentData& x, KP:: studentData& y){
	return x.finalgrade > y.finalgrade;
}
int sortStudentData(std::vector<KP::studentData> &allstudentData,KP::SORT_TYPE st) {
	if(allstudentData.empty()) {
		return KP:: VECTOR_CONTAINS_NO_STUDENTS;
	}
	if (st == KP:: NAME){
		std:: sort(allstudentData.begin(), allstudentData.end(), compareName);
	}
	else if (st == KP:: FINAL_GRADE) {
		std:: sort(allstudentData.begin(), allstudentData.end(), compareFinal);
	}
	//int x = allstudentData.size();
	return KP:: SUCCESS;
}


