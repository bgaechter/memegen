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

};
