#include <boost/asio.hpp>
using namespace std;

class SimpleSerial{
	public:
		SimpleSerial(string port, unsigned int baud_rate):
		io(), serial(io,port){
			serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
		}	

		void writeString(string s){
			boost::asio::write(serial,boost::asio::buffer(s.c_str(), s.size()));
			std::cout<< s;
		}
		string readLine(){
			char c;
			string result;
			for(;;){
				boost::asio::read(serial, boost::asio::buffer(&c,1));
				switch(c){
					case '\r':
						break;
					case '\n':
						return result;
					default:
						result+=c;
						cout << c;
				}
			}
		}
	private:
		boost::asio::io_service io;
		boost::asio::serial_port serial;
};
