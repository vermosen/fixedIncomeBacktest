/*
 * recordset.hpp
 *
 *  Created on: Jun 23, 2015
 *      Author: vermosen
 */

#ifndef RECORDSET_HPP_
#define RECORDSET_HPP_

#include <string>
#include <map>

#include <boost/noncopyable.hpp>
#include <boost/lexical_cast.hpp>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


// concatenate two string values in the form Y'X'
#define SQL_INSERT_STR(X,Y) \
	X.append("'" )          \
	 .append(Y   )          \
	 .append("'");

// insert a value via a cast
#define SQL_INSERT_NUM(X,Y) \
	 X.append(boost::lexical_cast<std::string>(Y));

// insert a date value
//#define SQL_INSERT_DATE(X,Y,Z)
//	X.append("'")
//	 .append(Y.convertSqlDateTime(Z))
//	 .append("'");

namespace database {

	enum deletionPolicy : unsigned char {						// defines deletion policy

		authorizeCopy      = 0,
		preserveFormerData = 1,
		EraseFormerData    = 2

	};

	// recordset class<Key, T, Container> where T is
	// the return type, generally an object (instru-
	// ment, quote, etc). In general, we could defi-
	// ne a map<Key, T> but in some case, we wouldn'
	// t insure unicity of the key and would go for
	// some other container.
	template<
		typename Key,
		typename T	,
		template<
			typename Key,
			typename T,
			typename Rel = std::less<Key>,
			typename All = std::allocator<std::pair<const Key, T>>>
		class Container>
	class recordset : public boost::noncopyable {

	public:
		typedef typename Container<Key, T>::const_iterator const_iterator;
		typedef typename Container<Key, T>::iterator iterator;

		recordset() = delete;									// no default ctor
		recordset & operator =(const recordset & o) = delete;	// no assignement

		recordset(sql::Connection * connection)
			: connection_(connection) {};
		virtual ~recordset() {};

		// database request methods, return true is the statement succeed, throw otherwise
		virtual void 	selectStr (const std::string &) = 0	;
		void 			insertStr (const std::string &)		;
		void 			deleteStr (const std::string &)		;

		// iterators
		const_iterator 	cbegin 	() const	{ return records_.cbegin(); };
		const_iterator 	cend  	() const 	{ return records_.cend  (); };
		iterator 		begin	() 			{ return records_.begin	(); };
		iterator 		end  	() 			{ return records_.end  	(); };

		// data container size
		std::size_t size() const { return records_.size(); };

	protected:
		sql::Connection * 	connection_	;
		Container<Key, T> 	records_	;

	};

	template<
		typename Key,
		typename T	,
		template<
			typename Key,
			typename T	,
			typename Rel,
			typename All>
		class Container>
	void recordset<Key, T, Container>::deleteStr(const std::string & deleteStr) {

		try {

			//if (mysql_query(connection_, deleteStr.c_str()) != 0)	// throw on an error
			//	throw std::exception(mysql_error(connection_));

		} catch (...) {

			// TODO: exception management

		}
	}

	template<
		typename Key,
		typename T,
		template<
			typename Key,
			typename T,
			typename Rel,
			typename All>
		class Container>
	void recordset<Key, T, Container>::insertStr(const std::string & insertStr) {

		try{

			// throw on an error
			//if (mysql_query(myFix::settings::instance().connection(), insertStr.c_str()) != 0)
			//	throw std::exception(mysql_error(myFix::settings::instance().connection()));

		} catch (...){

			// TODO: exception management

		}
	}
}

#endif /* RECORDSET_HPP_ */
