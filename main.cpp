#include "test.hpp"

namespace acc 
{
	void
	cin_runner(acc::UAV uav, int* main_loop) {
		bool run = true;
		std::string cmd;
		double value;
		
		while(run) {
			std::cout << "Enter cmd and value: " << std::endl;
			std::cin >> cmd >> value;
			if (cmd == "exit") {
				run = false;
			} else if (cmd == "t") { // thrust 
	
			} else if (cmd == "p") { // thrust 
				uav.frame.pitch.write(static_cast<int>(value));
			} else if (cmd == "?") { // thrust 
				std::cout << "??????" << std::endl;
			}
		}
		*main_loop = 0;
	}
};

int 
main() {
	using namespace acc;
    int main_loop = 1;
    std::string port = "/dev/tty.usbserial-A504DRSI";
    UAV uav(port, B57600, CTRL_MODE::DIMC);
    std::thread cin_thread(&cin_runner, uav, &main_loop);

    
    while (main_loop == 1) {
    	sleep(1);
    }

	// testcase();
	// testcase2();
	// testcase3();
  	// testcase_read();
  	// testcase_motors_dynamics();
  	// testcase_motors_dynamics_engine();
  	// testcase_motors_start_stop();
  	cin_thread.join();
	return 0;
}