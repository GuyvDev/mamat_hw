#ifndef PORT_H
#define PORT_H

#include "generic-field.h"

class Port : public GenericField {
private:
	int min_value;
	int max_value;
	String pattern;

public:
	
	/**
	 * @brief Constructs an Port object with the specified pattern. min_value,
	 * 		  max_value are zeroed.
	 * @param pattern could be "src-port" / "dst-port"
	 */
	Port(String pattern);

	/**
	 * @brief Destroys the Port object.
	 */
	~Port();

	/**
	 * @brief Sets the value of the port field and determines its validity.
	 * @param val The value to be set.
	 * @return True if the value is parsed successfully and valid,
	 * 		   false otherwise.
	 */
	bool set_value(String val);
	
	/**
	 * @brief Matches the port field against a given value.
	 * @param value The value to match against.
	 * @return True if the value is valid according to the set value,
	 * 		   false otherwise.
	 */
	bool match(String value);
};

#endif