#include <cstdlib>
#include<iostream>
#include<string>
#include<boost/asio.hpp>
    #include <ctime>

  #include "map.h"
  #include <unistd.h>
  #include <CircSLelement.h>

  //#include "classes.h"
  //#include "Turns.cc"
  #include "/public/read.h"
  using namespace std;
      using boost::asio::ip::tcp;

  const int MAX_FPS = 60;
  const unsigned int TIMEOUT = 10;
  const int UP = 65;
  const int DOWN = 66;
  const int RIGHT = 67;
  const int LEFT =68;
  const int port = 15533;

using namespace std;
using boost::asio::ip::tcp;

//ideas - having a daily bonus that the server checks up on
//multiplayer(obviously)
//have a socket get the map back and update it, ans wait for any inputs untill its received and displayed
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
 Map map;
//int x = Map::SIZE / 2, y = Map::SIZE /2;
//	int old_x = -1, old_y = -1;
	map.setcord(2,(Map::SIZE/2)-1,'@');
	map.setcord(2,(Map::SIZE/2),'@');
//	int level=0;


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
		while(true){
			//have the map read in first by the server 
	string line;
	getline(s,line);`
	cout<<line<<endl;
	cin>>line;
		s<<line<<endl;
		}

}


	catch (const std::exception& e) {
		cout <<"Excpetion: "<<e.what()<<endl;
	}
	return 0;
}


