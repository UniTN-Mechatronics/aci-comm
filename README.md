# aci-comm
Asctec Communication Interface Commander

## Usage example
```C++

#include "aci_comm_uav.hpp"

int main() {
	using namespace acc; 
    std::string port = "/dev/tty.USB0";
	
	// Initialize the UAV with serial port, 
	// baud rate and control mode
	UAV uav(port, B57600, CTRL_MODE::DIMC);
	
	try {
		// Enable all the motors read and write;
		uav.motors.enable_read(0).enable_write(0);

		// Start the aci and enable control mode
        uav.start().control_enable(true);

        // Write RPM motors 
        uav.motors.write({1500, 1500, 1500, 1500});

        // Read motors 1 RPM
        auto motor_speed_1 = uav.motors[0].read(); // -> 1500;

        uav.motors.write({1075, 1075, 1075, 1075});
		
	} catch (...) {
		// Stop and clean
		uav.stop();
	} 
	return 0;	
}
```

## aci-comm design
![aci-comm-design](doc_images/aci_comm_design.png)

