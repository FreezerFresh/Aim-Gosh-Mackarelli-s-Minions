#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
using namespace std;
using boost::asio::ip::tcp;

const int port = 39253; //just used a random number

string mds()
{
	using namespace std;
time_t now = time(0);
	return ctime(&now);
}
int main()
{
	try {
		
	boost::asio::io_context io_context;

	tcp::endpoint endpoint(tcp::v4(), port);
	tcp::acceptor acceptor(io_context, endpoint);

	for(;;)
	 {
		tcp::iostream stream;
		boost::system::error_code ec;
		acceptor.accept(stream.socket(), ec);
	if(!ec)
	 {
				stream<< "needs a command\n";
				string str;

	//stream<<mds();

	 }
	}
}
catch(exception& e)
{
	cerr<<e.what()<<endl;
}
}
