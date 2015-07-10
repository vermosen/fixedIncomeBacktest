/*
 * tcpConnection.hpp
 *
 *  Created on: May 21, 2015
 *      Author: vermosen
 */

#ifndef TCPCONNECTION_HPP_
#define TCPCONNECTION_HPP_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

// activate/inactivate strand
#define STRAND
//#undef STRAND

using boost::asio::ip::tcp;

// class tcpConnection - the use of boost::tuple
// is a workaround to a limitation of boost::bind
// when it is used together with templates
class tcpConnection {

public:

	tcpConnection(boost::asio::io_service& io_service) : m_socket(io_service)
		#ifdef STRAND
		,m_strand(io_service)
		#endif /* STRAND */
	{}

	tcp::socket& socket() { return m_socket; }

	// template functions to send and retrieve data
	// of type T asynchroneously. Handler is the
	// callback function passed as an argument.
	template <typename T, typename Handler>								// writing asynchroneously on the socket
	void async_write(const T& t, Handler handler) {

		std::ostringstream archive_stream;								// serialize t
		boost::archive::text_oarchive archive(archive_stream);
		archive << t;
		m_outbound_data = archive_stream.str();							// adds the archive to the outbound data

		std::ostringstream header_stream;								// write a header
		header_stream
			<< std::setw(header_length)
			<< std::hex
			<< m_outbound_data.size();

		if (!header_stream || header_stream.str().size() != header_length) {

			// error on the message size
			boost::system::error_code error(boost::asio::error::invalid_argument);

			#ifdef STRAND
			m_socket.get_io_service().post(m_strand.wrap(boost::bind(handler, error)));
			#else
			m_socket.get_io_service().post(boost::bind(handler, error));
			#endif /* STRAND */

			return;

		}

		m_outbound_header = header_stream.str();
		std::vector<boost::asio::const_buffer> buffers;					// write the data on the socket
		buffers.push_back(boost::asio::buffer(m_outbound_header));
		buffers.push_back(boost::asio::buffer(m_outbound_data));

		#ifdef STRAND
		boost::asio::async_write(m_socket, buffers, m_strand.wrap(handler));
		#else
		boost::asio::async_write(m_socket, buffers, handler);
		#endif /* STRAND */
	}

	template <typename T, typename Handler>								// reading asynchroneously from the socket
	void async_read(T& t, Handler handler) {

		void (tcpConnection::*f)(const boost::system::error_code&, T&, boost::tuple<Handler>)
			= &tcpConnection::handle_read_header<T, Handler>;			// get the socket

		#ifdef STRAND
		boost::asio::async_read(
			m_socket, boost::asio::buffer(m_inbound_header), m_strand.wrap(
			boost::bind(
				f, this, boost::asio::placeholders::error, boost::ref(t),
				boost::make_tuple(handler))));
		#else
		boost::asio::async_read(
			m_socket, boost::asio::buffer(m_inbound_header),
			boost::bind(
				f, this, boost::asio::placeholders::error, boost::ref(t),
				boost::make_tuple(handler)));
		#endif
		// STRAND
	}

	template <typename T, typename Handler>								// read the header
	void handle_read_header(
		const boost::system::error_code& e,
		T& t, boost::tuple<Handler> handler) {

		if (e) {

			boost::get<0>(handler)(e);									// get the error from the handler

		} else {

			std::istringstream is(std::string(m_inbound_header, header_length));
			std::size_t m_inbound_datasize = 0;

			if (!(is >> std::hex >> m_inbound_datasize)) {

				// non valid header
				boost::system::error_code error(boost::asio::error::invalid_argument);
				boost::get<0>(handler)(error);
				return;

			}

			m_inbound_data.resize(m_inbound_datasize);					// get the data
			void (tcpConnection::*f)(const boost::system::error_code&, T&, boost::tuple<Handler>)
				= &tcpConnection::handle_read_data<T, Handler>;

			#ifdef STRAND
			boost::asio::async_read(m_socket, boost::asio::buffer(m_inbound_data), m_strand.wrap(
				boost::bind(f, this,
				boost::asio::placeholders::error, boost::ref(t), handler)));
			#else
			boost::asio::async_read(m_socket, boost::asio::buffer(m_inbound_data),
				boost::bind(f, this,
				boost::asio::placeholders::error, boost::ref(t), handler));
			#endif /* STRAND */
		}
	}

	template <typename T, typename Handler>								// on error, write the archive
	void handle_read_data(
		const boost::system::error_code& e,
		T& t, boost::tuple<Handler> handler) {

		if (e) {

			boost::get<0>(handler)(e);

		} else {

			try {														// attempt to extract

				std::string archive_data(&m_inbound_data[0], m_inbound_data.size());
				std::istringstream archive_stream(archive_data);
				boost::archive::text_iarchive archive(archive_stream);
				archive >> t;

			} catch (std::exception& e) {

				boost::system::error_code error(boost::asio::error::invalid_argument);
				boost::get<0>(handler)(error);
				return;

			}

			boost::get<0>(handler)(e);									// inform caller of the failure
		}
	}


private:

	enum { header_length = 8 }; 										// header size

	// members
	tcp::socket 		m_socket						;				// the socket
	std::string 		m_outbound_header				;				// outbound header
	std::string 		m_outbound_data					;				// outbound data
	char 				m_inbound_header[header_length]	;				// inbound header
	std::vector<char> 	m_inbound_data					;				// inbound data

	#ifdef STRAND
	boost::asio::io_service::strand	m_strand;							// strand object
	#endif

};

#endif /* TCPCONNECTION_HPP_ */
