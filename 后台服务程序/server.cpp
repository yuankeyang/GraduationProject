#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <boost/asio.hpp>
#include <boost/unordered_map.hpp>
#include <Graph.h>
#include <fstream>
#include <iomanip>
#include <Algorithm.h>
#include <Helper.h>
#include <ExeTime.h>


using boost::asio::ip::tcp;

Algorithm al;


// Class to manage the memory to be used for handler-based custom allocation.
// It contains a single block of memory which may be returned for allocation
// requests. If the memory is in use when an allocation request is made, the
// allocator delegates allocation to the global heap.
class handler_allocator
{
public:
	
	handler_allocator()
		: in_use_(false)
	{
	}

	handler_allocator(const handler_allocator&) = delete;
	handler_allocator& operator=(const handler_allocator&) = delete;

	void* allocate(std::size_t size)
	{
		if (!in_use_ && size < sizeof(storage_))
		{
			in_use_ = true;
			return &storage_;
		}
		else
		{
			return ::operator new(size);
		}
	}

	void deallocate(void* pointer)
	{
		if (pointer == &storage_)
		{
			in_use_ = false;
		}
		else
		{
			::operator delete(pointer);
		}
	}

private:
	// Storage space used for handler-based custom memory allocation.
	typename std::aligned_storage<1024>::type storage_;

	// Whether the handler-based custom allocation storage has been used.
	bool in_use_;
};

// Wrapper class template for handler objects to allow handler memory
// allocation to be customised. Calls to operator() are forwarded to the
// encapsulated handler.
template <typename Handler>
class custom_alloc_handler
{
public:
	custom_alloc_handler(handler_allocator& a, Handler h)
		: allocator_(a),
		handler_(h)
	{
	}

	template <typename ...Args>
	void operator()(Args&&... args)
	{
		handler_(std::forward<Args>(args)...);
	}

	friend void* asio_handler_allocate(std::size_t size,
		custom_alloc_handler<Handler>* this_handler)
	{
		return this_handler->allocator_.allocate(size);
	}

	friend void asio_handler_deallocate(void* pointer, std::size_t /*size*/,
		custom_alloc_handler<Handler>* this_handler)
	{
		this_handler->allocator_.deallocate(pointer);
	}

private:
	handler_allocator& allocator_;
	Handler handler_;
};

// Helper function to wrap a handler object to add custom allocation.
template <typename Handler>
inline custom_alloc_handler<Handler> make_custom_alloc_handler(
	handler_allocator& a, Handler h)
{
	return custom_alloc_handler<Handler>(a, h);
}

class session
	: public std::enable_shared_from_this<session>
{
public:

	session(tcp::socket socket)
		: socket_(std::move(socket))
	{
		memset(data_, ' ', DATA_SIZE);
		
	}

	void start()
	{
		do_read();
	}

private:
	static const int DATA_SIZE = 64;
	void do_read()
	{
		auto self(shared_from_this());
		socket_.async_read_some(boost::asio::buffer(data_),
			make_custom_alloc_handler(allocator_,
				[this, self](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				
				char* dst = new char[length + 1];
				strncpy_s(dst,length + 1, data_, length);
				dst[length] = '\0';
				std::string data(dst);
				std::vector<std::string> args = Helper::split(data, ' ');
				memset(data_, ' ', DATA_SIZE);
				if (args.size() != 2)
					do_write("参数错误！");
				else
				{
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
					do_write(result);
				}
			}
		}));
	}

	void do_write(std::string msg)
	{
		auto self(shared_from_this());
		boost::asio::async_write(socket_, boost::asio::buffer(msg),
			make_custom_alloc_handler(allocator_,
				[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				do_read();
			}
		}));
	}
	tcp::socket socket_;
	char data_[DATA_SIZE];
	handler_allocator allocator_;
};

class server
{
public:
	server(boost::asio::io_service& io_service, short port)
		: acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
		socket_(io_service)
	{
		std::cout << "服务器启动......正在监听端口:" << port << std::endl;
		std::string sketch_file = "../facebook_sketch.txt";
		//std::string sketch_file = "../test1_sketch.txt";
		al.read_sketchs(sketch_file);
		do_accept();
	}

private:
	void do_accept()
	{
		acceptor_.async_accept(socket_,
			[this](boost::system::error_code ec)
		{
			if (!ec)
			{
				std::cout << "一个客户端连接成功！\n";
				std::make_shared<session>(std::move(socket_))->start();
			}

			do_accept();
		});
	}

	tcp::acceptor acceptor_;
	tcp::socket socket_;
};

int main(int argc, char* argv[])
{
	try
	{
		const int port = 3200;

		boost::asio::io_service io_service;
		server s(io_service, port);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return EXIT_SUCCESS;
}