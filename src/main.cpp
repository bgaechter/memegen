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
		("caption-top", po::value<std::string>(), "text displayed on top of the meme")
		("caption-bottom", po::value<std::string>(), "text displayed at the bottom of the meme")
		("user", po::value<std::string>(), "user name for your memegenerator.net account")
		("password", po::value<std::string>(), "password for your memegenerator.net account")
		("create", "create a meme")
		("list-popular", "list all popular memes")
		("test", "used to call test function");

	po::variables_map vm;
	po::store(po::parse_command_line(ac,av,desc),vm);
	po::notify(vm);
	
	option_dependency(vm, "create", "meme");
	option_dependency(vm, "create", "caption-top");
	option_dependency(vm, "create", "caption-bottom");
	option_dependency(vm, "create", "user");
	option_dependency(vm, "create", "password");

	if(vm.count("help") || ac <=1 ){
		std::cout << desc << "\n";
		return 0;
	}

	if(vm.count("list-popular")){

		MemeGenerator mg{};
		mg.printPopularMemes(std::cout);
	}

	if(vm.count("create")){
		MemeGenerator mg{};
		mg.createMeme(vm["user"].as<std::string>(), vm["password"].as<std::string>(), vm["meme"].as<std::string>(), vm["caption-top"].as<std::string>(), vm["caption-bottom"].as<std::string>());
	}

	return 0;
}
