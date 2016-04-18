//
// chat_server.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "chat_message.hpp"

#include <Helper.h>
#include <Graph.h>
#include <Algorithm.h>
#include <AESClass.h>

using boost::asio::ip::tcp;

Algorithm al;
AESClass aes;

//----------------------------------------------------------------------

typedef std::deque<chat_message> chat_message_queue;

//----------------------------------------------------------------------

class chat_participant
{
public:
	virtual ~chat_participant() {}
	virtual void deliver(const chat_message& msg) = 0;
};

typedef boost::shared_ptr<chat_participant> chat_participant_ptr;

//----------------------------------------------------------------------

class chat_room
{
public:
	void join(chat_participant_ptr participant)
	{
		participants_.insert(participant);
		std::for_each(recent_msgs_.begin(), recent_msgs_.end(),
			boost::bind(&chat_participant::deliver, participant, _1));
	}

	void leave(chat_participant_ptr participant)
	{
		std::cout << participant << ":leave..." << std::endl;
		std::cout << "--------------------------------" << std::endl;
		participants_.erase(participant);
		recent_msgs_.clear();
	}

	void deliver(const chat_message& msg)
	{
		recent_msgs_.push_back(msg);
		while (recent_msgs_.size() > max_recent_msgs)
			recent_msgs_.pop_front();

		std::for_each(participants_.begin(), participants_.end(),
			boost::bind(&chat_participant::deliver, _1, boost::ref(msg)));
	}

private:
	std::set<chat_participant_ptr> participants_;
	enum { max_recent_msgs = 100 };
	chat_message_queue recent_msgs_;
};

//----------------------------------------------------------------------

class chat_session
	: public chat_participant,
	public boost::enable_shared_from_this<chat_session>
{
public:
	chat_session(boost::asio::io_service& io_service, chat_room& room)
		: socket_(io_service),
		room_(room)
	{
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		room_.join(shared_from_this());
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), chat_message::header_length),
			boost::bind(
				&chat_session::handle_read_header, shared_from_this(),
				boost::asio::placeholders::error));
	}

	void deliver(const chat_message& msg)
	{
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()),
				boost::bind(&chat_session::handle_write, shared_from_this(),
					boost::asio::placeholders::error));
		}
	}

	void handle_read_header(const boost::system::error_code& error)
	{
		if (!error && read_msg_.decode_header())
		{
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				boost::bind(&chat_session::handle_read_body, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}

	void handle_read_body(const boost::system::error_code& error)
	{
		if (!error)
		{
			std::string message(read_msg_.body(), read_msg_.body_length());
			//会话内容打印
			std::cout << shared_from_this() << ":" << message << std::endl;

			std::vector<std::string> args = Helper::split(message, ' ');

			if (args.size() != 2) {
				chat_message error_msg;
				error_msg.body_length(error_args_msg.length());
				memcpy(error_msg.body(), error_args_msg.data(), error_msg.body_length());
				error_msg.encode_header();
				room_.deliver(error_msg);
				return;
			}

			VERTEXTYPE id = std::stoi(args[0]);
			int number = std::stoi(args[1]);
			std::cout << "id = " << id << ", number = " << number << std::endl;

			auto candiates = al.get_recommend(id);
			int i = 0;
			std::string result = "";
			for (auto itr = candiates.begin();
			i < number && itr != candiates.end(); itr++, i++)
			{
				result += "Vertex:";
				result += std::to_string(itr->first);
				result += ", closeness:";
				result += std::to_string((int)std::floor(itr->second));
				result += "\n";
			}
			std::string ciphtext = aes.encryp(result);
			chat_message re_msg;
			re_msg.body_length(ciphtext.length());
			memcpy(re_msg.body(), ciphtext.data(), re_msg.body_length());
			re_msg.encode_header();

			room_.deliver(re_msg);
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), chat_message::header_length),
				boost::bind(&chat_session::handle_read_header, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}

	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			write_msgs_.pop_front();
			if (!write_msgs_.empty())
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().data(),
						write_msgs_.front().length()),
					boost::bind(&chat_session::handle_write, shared_from_this(),
						boost::asio::placeholders::error));
			}
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}

private:
	const std::string error_args_msg = "参数错误";
	tcp::socket socket_;
	chat_room& room_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
};

typedef boost::shared_ptr<chat_session> chat_session_ptr;

//----------------------------------------------------------------------

class chat_server
{
public:
	chat_server(boost::asio::io_service& io_service,
		const tcp::endpoint& endpoint)
		: io_service_(io_service),
		acceptor_(io_service, endpoint)
	{
		std::cout << "server starting...: " << endpoint <<std::endl;
		start_accept();
	}

	void start_accept()
	{
		chat_session_ptr new_session(new chat_session(io_service_, room_));
		acceptor_.async_accept(new_session->socket(),
			boost::bind(&chat_server::handle_accept, this, new_session,
				boost::asio::placeholders::error));
	}

	void handle_accept(chat_session_ptr session,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			std::cout << "--------------------------------" << std::endl;
			std::cout << "a session start...\n";
			session->start();
		}

		start_accept();
	}

private:
	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
	chat_room room_;
};

typedef boost::shared_ptr<chat_server> chat_server_ptr;
typedef std::list<chat_server_ptr> chat_server_list;

//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
	try
	{
		boost::asio::io_service io_service;

		chat_server_list servers;
		for (int i = 1; i < argc; ++i)
		{
			using namespace std; // For atoi.
			tcp::endpoint endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), 8888);
			chat_server_ptr server(new chat_server(io_service, endpoint));
			servers.push_back(server);
		}
		std::string sketch_file = "../facebook_sketch.txt";
		//std::string sketch_file = "../test1_sketch.txt";
		al.read_sketchs(sketch_file);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}