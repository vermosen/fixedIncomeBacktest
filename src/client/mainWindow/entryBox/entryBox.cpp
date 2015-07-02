/*
 * entryBox.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: vermosen
 */

#include "entryBox.hpp"

entryBox::entryBox(const std::string & str) : m_label(str) {

	pack_start	(m_label, false, false);
	pack_end	(m_entry, false, false);

}

