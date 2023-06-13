#include <iostream>
#include "input.h"
#include "ip.h"
#include "port.h"

const char* COMMA = ",";
const char* EQUAL = "=";
const char* EMPTY_STR = "";
const int RULE_ARGV_INDEX = 1;
const int EXIT_ERROR = -1;
const int FIELD_DATA_EXPECTED_SIZE = 2;
const int FIELD_INDEX = 0;
const int DATA_INDEX = 1;

enum PatternIndex {
	SRC_IP,
	DST_IP,
	SRC_PORT,
	DST_PORT,
	INVALID_PATTERN
};

const char* const PATTERNS[] = {
	"src-ip",
	"dst-ip",
	"src-port",
	"dst-port"
};

const int PATTERNS_SIZE = sizeof(PATTERNS) / sizeof(PATTERNS[0]);

PatternIndex getPatternIndex(const String& pattern) {
	// Compare the pattern using a loop and array
	for (int i = 0; i < PATTERNS_SIZE; i++) {
		if (pattern.trim().equals(PATTERNS[i])) {
			return static_cast<PatternIndex>(i);
		}
	}
	return INVALID_PATTERN;
}

void processRule(const String& rule) {
	String *rule_comma_splited;
	size_t rule_split1_size;
	int index_of_rule = 0;
	rule.split(COMMA, &rule_comma_splited, &rule_split1_size);
	for (size_t i = 0; i < rule_split1_size; i++) {
		if (!rule_comma_splited[i].trim().equals(EMPTY_STR)) {
			index_of_rule = static_cast<int>(i);
		}
	}
	String *rule_field_data;
	size_t rule_field_data_size;
	rule_comma_splited[index_of_rule].trim().split(EQUAL, &rule_field_data,
												   &rule_field_data_size);
	if (rule_field_data_size != FIELD_DATA_EXPECTED_SIZE) {
		std::cerr << "ERROR IN EXTRACTING RULE\n" << std::endl;
		delete[] rule_comma_splited;
		delete[] rule_field_data;
		return;
	}

	PatternIndex patternIndex = getPatternIndex(rule_field_data[FIELD_INDEX]);
	if (patternIndex == INVALID_PATTERN) {
		std::cerr << "INVALID PATTERN\n" << std::endl;
		delete[] rule_comma_splited;
		delete[] rule_field_data;
		return;
	}

	GenericField *ruleField = nullptr;
	if (patternIndex == SRC_IP || patternIndex == DST_IP) {
		ruleField = new Ip(rule_field_data[FIELD_INDEX].trim());
	}
	else if (patternIndex == SRC_PORT || patternIndex == DST_PORT) {
		ruleField = new Port(rule_field_data[FIELD_INDEX].trim());
	}

	if (ruleField) {
		if (ruleField->set_value(rule_field_data[DATA_INDEX].trim()) == 0) {
			std::cerr << "ERROR IN RULE\n" << std::endl;
			return;
		}
		parse_input(*ruleField);
		delete ruleField;
	}

	delete[] rule_comma_splited;
	delete[] rule_field_data;
}

int main(int argc, char** argv)
{
	if (check_args(argc, argv) != 0) {
		return EXIT_ERROR;
	}

	String rule(argv[RULE_ARGV_INDEX]);
	processRule(rule);
	return 0;
}