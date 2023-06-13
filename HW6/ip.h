#ifndef IP_H
#define IP_H

#include "generic-field.h"


class Ip : public GenericField {
private:
	unsigned int ip;
	unsigned int subnet;
	unsigned int network_prefix;
	String pattern;
	
public:

	/**
	 * @brief Constructs an Ip object with the specified pattern. ip, subnet,
	 * 		  network_prefix are zeroed.
	 * @param pattern could be "src-ip" / "dst-ip"
	 */
	Ip(String pattern);

	/**
	 * @brief Destroys the Ip object.
	 */
	~Ip();
	
	/**
	 * @brief Sets the value of the IP field and determines its validity.
	 * @param val The value to be set.
	 * @return True if the value is parsed successfully and valid, 
	 * 		   false otherwise.
	 */
	bool set_value(String val);
	
	/**
	 * @brief Matches the IP field against a given value.
	 * @param value The value to match against.
	 * @return True if the value is valid according to the set value, 
	 * 		   false otherwise.
	 */
	bool match(String value);
};

#endif