#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	try
	{
		static const int max_line_length = 80;
		static const int DATA_SIZE = 4096;
		const int port = 3200;
		std::string host = "127.0.0.1";
		boost::asio::io_service io_service;
		tcp::endpoint end_point(boost::asio::ip::address::from_string(host), port);
		boost::system::error_code ec;

		tcp::socket socket(io_service);
		socket.connect(end_point, ec);
		if (!ec)
		{
			std::cout << "����" << host << ":" << port << "�ɹ���\n";
			std::cout << "�����Ƽ��㷨�ͻ���:\n";
			std::cout << "�����ʽ:>> id number" << std::endl;
			std::cout << "number�Ƽ�С�ڵ���100" << std::endl;
			std::cout << "-------------------" << std::endl;
		}
		else 
		{
			std::cout << "����ʧ�ܣ�������Ϣ��" << ec << std::endl;
			return EXIT_SUCCESS;
		}

		char line[max_line_length + 1];
		char data[DATA_SIZE];
		while (std::cin.getline(line, max_line_length + 1))
		{
			std::string buf(line);
			if (buf.size() == 0)
				continue;
			socket.write_some(boost::asio::buffer(buf), ec);
			size_t length = socket.read_some(boost::asio::buffer(data), ec);
			if (!ec && length > 0)
			{
				std::cout.write(data, length);
				std::cout << std::endl;
				std::cout << "--------------------\n";
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}