#include "port.h"

const int SEPARATE = 2;
const int RELEVANT = 1;
const int MIN_PLACE = 0;
const int MAX_PLACE = 1;
const char* HYPHEN = "-";
const char* COMMA_PORT = ",";
const char* EQUAL_PORT = "=";
const int SIZE_OF_FIELD_ITEM = 2;
const int FIELD_INDEX = 0;
const int DATA_INDEX = 1;

/**
 * @brief Creates String objects out of a packet,
 *        Using split/trim operations.
 */
String** packet_field_extractor_port(const String& packet,
									 size_t *size_of_rows) {
	size_t number_of_fields;
	String *fields_from_packet;
	packet.trim().split(COMMA_PORT, &fields_from_packet, &number_of_fields);
	String **fields_and_values;
	fields_and_values = new String*[number_of_fields];
	for (size_t i = 0; i < number_of_fields; i++) {
		fields_and_values[i] = new String[SIZE_OF_FIELD_ITEM];
		String *temp_item;
		size_t temp_item_size;
		fields_from_packet[i].trim().split(EQUAL_PORT, &temp_item,
										   &temp_item_size);
		fields_and_values[i][FIELD_INDEX] = temp_item[FIELD_INDEX].trim();
		fields_and_values[i][DATA_INDEX] = temp_item[DATA_INDEX].trim();
		delete[] temp_item;
	}
	delete[] fields_from_packet;
	*size_of_rows = number_of_fields;
	return fields_and_values;
}

Port::Port(String pattern) : min_value(0), max_value(0), pattern(pattern) {}

Port::~Port(){}

bool Port::set_value(String val) { 
	String *split_min_max;
	size_t two_fields;
	val.split(HYPHEN, &split_min_max, &two_fields);
	if (two_fields != SEPARATE) {
		delete[] split_min_max;
		return false;
	}
	min_value = split_min_max[MIN_PLACE].to_integer();
	max_value = split_min_max[MAX_PLACE].to_integer();
	if (min_value < 0 || max_value > 65535) {
		return false;
	}
	delete[] split_min_max;
	return true;
}

bool Port::match(String value) {
	bool result_match = false;
	size_t fields_and_values_length;
	String **fields_and_values = packet_field_extractor_port(value,
			&fields_and_values_length);
	if (!fields_and_values){
		return false;
	}
	for (size_t i = 0; i < fields_and_values_length; i++) {
		if (fields_and_values[i][FIELD_INDEX].equals(this->pattern)) {
			int val = fields_and_values[i][DATA_INDEX].to_integer();
			if ((val >= this->min_value) && (val <= this->max_value)) {
				result_match = true;
			}
			else {
				result_match = false;
			}
		}
		delete[] fields_and_values[i];
	}
	delete[] fields_and_values;
	return result_match;
}