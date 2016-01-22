#include "MemeGenerator.h"

#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <iterator>


namespace po = boost::program_options;

int main(int ac, char* av[]){

	po::options_description desc("Supported options");

	desc.add_options()
		("help", "display this message")
		("meme", po::value<std::string>(), "specify the name of the meme")
		("caption", po::value<std::string>(), "give a caption (meme tex)")
		("user", po::value<std::string>(), "user name for your memegenerator.net account")
		("password", po::value<std::string>(), "password for your memegenerator.net account")
		("create", "create a meme")
		("list-popular", "list all popular memes")
		("test", "used to call test function");

	po::variables_map vm;
	po::store(po::parse_command_line(ac,av,desc),vm);
	po::notify(vm);
	

	if(vm.count("help") || ac <=1 ){
		std::cout << desc << "\n";
		return 0;
	}

	if(vm.count("list-popular")){

		MemeGenerator mg{};
		mg.printPopularMemes(std::cout);
	}

	if(vm.count("test")){
		
		std::cout << "Testing...";
		MemeGenerator mg{};
		std::cout << mg.getImageID("Insanity-Wolf");
	
	}

	if(vm.count("create")){
		MemeGenerator mg{};
		mg.createMeme(vm["user"].as<std::string>(), vm["password"].as<std::string>(), vm["meme"].as<std::string>(), vm["caption"].as<std::string>(), "test");
	}

	return 0;
}
