#include "ip.h"

const char* COMMA = ",";
const char* EQUAL = "=";
const char* EMPTY_STR_I = "";
const int SIZE_OF_FIELD_ITEM = 2;
const int FIELD_INDEX = 0;
const int DATA_INDEX_P = 1;
const int CARE_INDEX = 1;
const int DATA_INDEX = 0;
const size_t NUMBER_OF_VARIABLES_FROM_DATA = 2;
const size_t NUMBER_OF_EXPECTED_BYTES_FROM_DATA = 4;
const int ERROR = -1;
const int SIZE_OF_BYTE_IN_BITS = 8;
const int SIZE_OF_IP_WORD_IN_BITS = 32;
const char* SLASH = "/";
const char* DOT = ".";

/**
 * @brief Creates String objects out of a packet,
 *        Using split/trim operations.
 */
String** packet_field_extractor(const String& packet, size_t *size_of_rows) {
	size_t number_of_fields;
	String *fields_from_packet;
	packet.trim().split(COMMA, &fields_from_packet, &number_of_fields);
	String **fields_and_values;
	fields_and_values = new String*[number_of_fields];
	for (size_t i = 0; i < number_of_fields; i++) {
		fields_and_values[i] = new String[SIZE_OF_FIELD_ITEM];
		String *temp_item;
		size_t temp_item_size;
		fields_from_packet[i].trim().split(EQUAL, &temp_item,&temp_item_size);
		fields_and_values[i][FIELD_INDEX] = temp_item[FIELD_INDEX].trim();
		fields_and_values[i][DATA_INDEX_P] = temp_item[DATA_INDEX_P].trim();
		delete[] temp_item;
	}
	delete[] fields_from_packet;
	*size_of_rows = number_of_fields;
	return fields_and_values;
}

unsigned int subnet_mask_generator(int subnet_num_bits) {
	if (subnet_num_bits < 0 || 
		subnet_num_bits > SIZE_OF_IP_WORD_IN_BITS) {
		return 0;
	}

	return (~0U << (SIZE_OF_IP_WORD_IN_BITS - subnet_num_bits));
}


int ip_from_String(const String& ip_string) {
	int result = 0;
	String *decimal_bytes;
	size_t number_of_bytes;
	ip_string.trim().split(DOT, &decimal_bytes, &number_of_bytes);
	if (number_of_bytes != NUMBER_OF_EXPECTED_BYTES_FROM_DATA) {
		delete[] decimal_bytes;
		return ERROR;
	}
	int temp_byte = 0, temp_multiplyer = 0;
	for (size_t i = 0; i < number_of_bytes; i++) {
		temp_byte = decimal_bytes[i].to_integer();
		temp_multiplyer = SIZE_OF_BYTE_IN_BITS*((int)(number_of_bytes-1-i));
		result = result | (temp_byte << temp_multiplyer);
	}
	delete[] decimal_bytes;
	return result;
}

Ip::Ip(String pattern) : ip(0), subnet(0), network_prefix(0), 
						 pattern(pattern) {}

Ip::~Ip(){}

bool Ip::set_value(String val) {
	size_t split1_size;
	String *split1;
	val.trim().split(SLASH, &split1, &split1_size);
	if (split1_size != NUMBER_OF_VARIABLES_FROM_DATA) {
		delete[] split1;
		return false;
	}
	int error_check = ip_from_String(split1[DATA_INDEX].trim());
	if (error_check == ERROR) {
		delete[] split1;
		return false;
	}
	int subnet_num_bits = split1[CARE_INDEX].trim().to_integer();
	this->subnet = subnet_mask_generator(subnet_num_bits);
	if (subnet == 0) {
		return false;
	}
	this->ip = (unsigned int)error_check;
	this->network_prefix = this->subnet & this->ip;
	delete[] split1;
	return true;
}

bool Ip::match(String value) {
	if (value.equals(EMPTY_STR_I)) {
		return false;
	}
	bool result_match = false;
	size_t fields_and_values_length;
	String **fields_and_values = packet_field_extractor(value,
			&fields_and_values_length);
	if (!fields_and_values){
		return false;
	}
	for (size_t i = 0; i < fields_and_values_length; i++) {
		if (fields_and_values[i][FIELD_INDEX].equals(this->pattern)) {
			String data = fields_and_values[i][DATA_INDEX_P];
			unsigned int ip_to_match = (unsigned int)ip_from_String(
															data.trim());
			if ((int)ip_to_match == ERROR || ((ip_to_match&this->subnet) !=
											  this->network_prefix)) {
				result_match = false;
			}
			else {
				result_match = true;
			}
		}
		delete[] fields_and_values[i];
	}
	delete[] fields_and_values;
	return result_match;
}