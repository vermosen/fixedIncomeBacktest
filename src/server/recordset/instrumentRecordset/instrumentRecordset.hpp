/*
 * instrumentRecordset.hpp
 *
 *  Created on: Jun 23, 2015
 *      Author: vermosen
 */

#ifndef INSTRUMENTRECORDSET_HPP_
#define INSTRUMENTRECORDSET_HPP_

#include <map>
#include <server/recordset.hpp>

namespace database {

class instrumentRecordset : public recordset<std::size_t, double, std::map > {
public:
	instrumentRecordset(sql::Connection *);
	virtual ~instrumentRecordset() {};
	void selectStr (const std::string &);
};

} /* namespace database */
#endif /* INSTRUMENTRECORDSET_HPP_ */
