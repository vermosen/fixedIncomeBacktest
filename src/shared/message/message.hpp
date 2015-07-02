/*
 * message.hpp
 *
 *  Created on: May 26, 2015
 *      Author: vermosen
 */

#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <string>

class message {

	friend class boost::serialization::access;

public:

	message() : m_body() {} ;
	message(const std::string & body) : m_body(body) {}
	void reset() {m_body.clear();};

	// accessors
	std::string body() const { return m_body; };
	void body(const std::string & o) { m_body = o; };

public:
	std::string m_body;

protected:
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version){
		ar & m_body;
	}
};

#endif /* MESSAGE_HPP_ */
