#pragma once
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <string>
#include <sstream>
#include <json/json.h>
#include <ostream>

struct MemeGenerator{

	void printPopularMemes(std::ostream &out){

		std::stringstream ss;

		curlpp::Cleanup cleanup;
		curlpp::Easy request;
		request.setOpt(new curlpp::options::WriteStream(&ss));
		request.setOpt(new curlpp::options::Url("http://version1.api.memegenerator.net/Generators_Select_ByPopular?pageIndex=0&pageSize=12"));

		request.perform();

		Json::Value popularMemes;

		ss >> popularMemes;

		out << popularMemes;

	}

	std::string getGenerator(std::string memeName){

		std::string url {"http://version1.api.memegenerator.net/Generator_Select_ByUrlNameOrGeneratorID?urlName="+memeName};
		std::stringstream ss;
		curlpp::Cleanup cleanup;
		curlpp::Easy request;
		request.setOpt(new curlpp::options::WriteStream(&ss));
		request.setOpt(new curlpp::options::Url(url));

		request.perform();

		Json::Value response;

		ss >> response;


		return response["result"].get("generatorID", 0).asString();

	}

	std::string getImageID(std::string memeName){
	
		std::string url {"http://version1.api.memegenerator.net/Generator_Select_ByUrlNameOrGeneratorID?urlName="+memeName};
		std::stringstream ss;
		curlpp::Cleanup cleanup;
		curlpp::Easy request;
		request.setOpt(new curlpp::options::WriteStream(&ss));
		request.setOpt(new curlpp::options::Url(url));

		request.perform();

		Json::Value response;

		ss >> response;

		std::string imageUrl = response["result"].get("imageUrl", "").asString();

		std::string imageName = imageUrl.substr(imageUrl.rfind("/")+1, imageUrl.size());

		std::string imageID  = imageName.substr(0, imageName.find("."));

		return imageID;
	
	}

	void createMeme(std::string username, std::string password, std::string memeName, std::string textTop, std::string textBottom){
		
		std::string generatorID {getGenerator(memeName)};
		std::string imageID {getImageID(memeName)};

		std::string url {"http://version1.api.memegenerator.net/Instance_Create?username="+username+"&password="+password+"&languageCode=en&generatorID="+generatorID+"&imageID="+imageID+"&text0="+textTop+"&text1="+textBottom};
		std::stringstream ss;
		curlpp::Cleanup cleanup;
		curlpp::Easy request;
		request.setOpt(new curlpp::options::WriteStream(&ss));
		request.setOpt(new curlpp::options::Url(url));

		request.perform();

		Json::Value response;

		ss >> response;
		std::cout << response;
	}



};
