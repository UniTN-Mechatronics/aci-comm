#include "test.hpp"

int 
main() {
	//testcase();
	//testcase2();
	// testcase3();
  	//testcase_read();
  	acc::Logger lg(std::cout);
  	for (int i = 0; i < 100; ++i) {
  		lg.log(lg.timer.time(), "Ehi", "Bitch", 1, 2,3,4);
  		usleep(1000);
  	} 

  	lg.timer.time();
	return 0;
}