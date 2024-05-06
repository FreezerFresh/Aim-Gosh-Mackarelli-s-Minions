#include <cstdlib>
#include<iostream>
#include<string>
#include<boost/asio.hpp>
using namespace std;
using boost::asio::ip::tcp;

//ideas - having a daily bonus that the server checks up on
//multiplayer(obviously)

void  daily_box( bool k){
	if(k){
	k= false;
		//give items here
	cout<<"you got a bonus today";
	return;
	}else 
	cout<<"you already accepted a bonus"<<endl;
	return;
}

int main(int argc, char* argv[]){
	try {
			if(argc != 3){
		cerr << "Usage: client <host> <port>" <<endl;
		return EXIT_FAILURE;
	}
	tcp::iostream s(argv[1], argv[2]);
	if (!s)
	{
		cout<<"unable to connect: "<< s.error().message()<<endl;
		return EXIT_FAILURE;
	}
	string line;
	getline(s,line);
	cout<<line<<endl;


}


	catch (const std::exception& e) {
		cout <<"Excpetion: "<<e.what()<<endl;
	}
	return 0;
}


