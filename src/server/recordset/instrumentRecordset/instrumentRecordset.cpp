/*
 * instrumentRecordset.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: vermosen
 */

#include "instrumentRecordset.hpp"

namespace database {

	instrumentRecordset::instrumentRecordset(sql::Connection * conn) : recordset(conn) {}

	void instrumentRecordset::selectStr (const std::string & std) {}

} /* namespace database */
