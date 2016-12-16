#include "test.hpp"

int 
main() {
	//std::vector<std::ostream> &vec;// {std::cout, std::cout};
	//vec.push_back(std::cout);
	
	acc::Logger lg(std::cout);
    lg.log("ciao", 6757, 56.0f);
    lg.log("Ciao!", 1012, 56.0f, 89, "Chiara");
    lg.log("Ehi!");

    lg << "Ehi!" << "Ciao!";
}	

/*
int 
main() {
	//testcase();
	//testcase2();
	testcase3();
	return 0;
}*/