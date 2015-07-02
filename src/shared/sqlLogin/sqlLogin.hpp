/*
 * sqlConnection.hpp
 *
 *  Created on: Jun 26, 2015
 *      Author: vermosen
 */

#ifndef SQLCONNECTION_HPP_
#define SQLCONNECTION_HPP_

#include <string>

#include <boost/serialization/access.hpp>

class sqlLogin {

public:
	sqlLogin() {};
	sqlLogin(	const std::string & ip		,
				const std::string & port	,
				const std::string & user	,
				const std::string & pwd		,
				const std::string & schema	)

		: ip_		(ip		),
		  port_		(port	),
		  user_		(user	),
		  pwd_		(pwd	),
		  schema_	(schema	) {};

	virtual ~sqlLogin() {};

	std::string ip		() const { return ip_		; };
	std::string port	() const { return port_		; };
	std::string user	() const { return user_		; };
	std::string pwd		() const { return pwd_		; };
	std::string schema	() const { return schema_	; };

	void ip		(const std::string & o) { ip_		= o; };
	void port	(const std::string & o) { port_ 	= o; };
	void user	(const std::string & o) { user_ 	= o; };
	void pwd	(const std::string & o) { pwd_ 		= o; };
	void schema	(const std::string & o) { schema_ 	= o; };

protected:

	// for serialization
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version){
		ar & ip_ & port_ & user_ & pwd_ & schema_;
	}

private:
	std::string ip_		;
	std::string port_	;
	std::string user_	;
	std::string pwd_	;
	std::string schema_	;

};

#endif /* SQLCONNECTION_HPP_ */
