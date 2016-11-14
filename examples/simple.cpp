#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <boost/bind.hpp>
#include <boost/intrusive_ptr.hpp>

#include <boost/fiber/all.hpp>

void fn() {
}

int main() {
    try {
        boost::fibers::fiber f( fn);
        f.join();
        std::cout << "done." << std::endl;
        return EXIT_SUCCESS;
    }
	catch ( std::exception const& e)
	{ std::cerr << "exception: " << e.what() << std::endl; }
	catch (...)
	{ std::cerr << "unhandled exception" << std::endl; }
	return EXIT_FAILURE;
}
