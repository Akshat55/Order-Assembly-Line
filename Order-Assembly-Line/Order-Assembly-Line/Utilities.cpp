#include "Utilities.h"


//Static variable initialization/Declaration
char Utilities::delimiter = '|';
std::ofstream Utilities::logFile;



//Constructor - Intializes field_width (Member variable)
Utilities::Utilities() {
	this->field_width = 1;
}



//Resets the field width of the current object to the given parameter value
void Utilities::setFieldWidth(size_t fw) {
	this->field_width = fw;
}



//Query that returns the Field Width
size_t Utilities::getFieldWidth() const {
	return this->field_width;
}



//Receives a reference to string str
//A reference to the position (next_pos) in this string at which to start extraction
//A reference to a boolean flag (more)
const std::string Utilities::nextToken(const std::string& str, size_t& next_pos, bool& more) {

	//Extract the values from the string
	std::string extraction(str.substr(next_pos));

	//Search for the First Delimiter
	size_t delPos = extraction.find_first_of(delimiter);


	//Checks if first value is a delimiter --> If So throw error
	if (delPos == 0) {
		throw str + "<-- *** no token found before the delimiter ***";
	}


	//If delimiter position == string::npos ->Record until end of line - IF NOT  --> Until Next Delimeter
	if (delPos == std::string::npos) {
		extraction = extraction.substr(0, std::string::npos);
	}
	else {
		extraction = extraction.substr(0, delPos);
	}


	//Update the next_pos(next position) and more
	next_pos += extraction.length() + 1;
	if (next_pos < str.length() - 1) {
		more = true;
	}
	else {
		more = false;
	}


	//Remove Extra space From Beginning and Ending - While Loop can also be used here
	bool ioSpace = true;
	while (ioSpace) {

		//No space is removed inbetween words even if there is multiple - Can be changed too
		if (extraction.empty()) {
			extraction.clear();
			break;
		}
		else if (extraction[0] == ' ') {
			extraction.erase(extraction.begin());
		}
		else if (extraction[extraction.length() - 1] == ' ') {
			extraction.erase(extraction.end() - 1);
		}
		else {
			break;
		}
	}

	//Update the field width if length greater than current field_width
	//A minimum of 1 delimiter is required inorder for the field_width to be updated
	if (extraction.length() > this->getFieldWidth() && delPos != std::string::npos) {
		this->setFieldWidth(extraction.length());
	}

	if (extraction.length() == 0) {
		more = false;
		next_pos = 0;
	}

	return extraction;
}



//Resets the delimiter for this class to the character received
void Utilities::setDelimiter(const char del) {
	delimiter = del;
}



//Opens a file of this name for writing and truncation. 
void Utilities::setLogFile(const char* logfile) {
	//Open a file for Writing
	logFile.open(logfile);
}



//Returns a modifiable reference to the log file
std::ofstream& Utilities::getLogFile() {
	return logFile;
}


