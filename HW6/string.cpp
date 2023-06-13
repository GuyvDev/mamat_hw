#include <cstring>
#include "string.h"

const char EMPTY_CHAR = '\0';
const char SPACE = ' ';
const char* EMPTY_STR = "";
const int CLOSING_FROM_RIGHT = 1;

String::String() : data(new char[1]{EMPTY_CHAR}), length(0) {}

String::String(const String& str) : data(strcpy(new char[str.length + 1],
										 str.data)), length(str.length) {}

String::String(const char* str) : data(strcpy(new char[strlen(str) + 1],str)),
								  length(strlen(str)) {}

String::~String() { 
	delete[] data;
}

String& String::operator=(const String& rhs) {
	if (this == &rhs) {
		return *this;
	}
	length = rhs.length;
	delete[] data;
	data = strcpy(new char[rhs.length + 1], rhs.data);
	return *this;
}

String& String::operator=(const char* str) {
	if (str == nullptr) {
		delete[] data;
		data = new char[1];
		data[0] = EMPTY_CHAR;
		length = 0;
		return *this;
	}
	length = strlen(str);
	delete[] data;
	data = strcpy(new char[length + 1], str);
	return *this;
}

bool String::equals(const String& rhs) const {
	return ((length == rhs.length) && (strcmp(data, rhs.data) == 0));
}

bool String::equals(const char* rhs) const {
	if (rhs == nullptr) {
		return false;
	}
	return ((length == strlen(rhs)) && (strcmp(data, rhs) == 0));
}

void String::split(const char *delimiters,
	String **output, size_t *size) const {

   if (size == nullptr) {
	return;
   }
   if (delimiters == nullptr) {
		*size = 0;
		return;
	}
	char *str = new char[length + 1];
	strcpy(str, data);
	char *token = strtok(str, delimiters);
	*size = 0;
	while (token != nullptr) {
		(*size)++;
		token = strtok(nullptr, delimiters);
	}
	
	if (output != nullptr) {
		*output = new String[*size];
		token = strtok(data, delimiters);
		for (size_t i = 0; i < *size; i++) {
			(*output)[i] = String(token);
			token = strtok(nullptr, delimiters);
		}
	}
	delete[] str;
}

int String::to_integer() const {
	return atoi(this->data);
}

String String::trim() const {
	char *new_string = new char[this->length + 1];
	strcpy(new_string, this->data);
	char *front = new_string;
	while (*front == SPACE) {
		front++;
	}
	if (*front == EMPTY_CHAR) {
		delete[] new_string;
		return String(EMPTY_STR);
	}
	char *end = front + strlen(front) - 1;
	while ((end > front) && (*end == SPACE)) {
		end--;
	}
	end[CLOSING_FROM_RIGHT] = EMPTY_CHAR;
	String result(front);
	delete[] new_string;
	return result;
}