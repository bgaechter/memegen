#pragma once
#include <ostream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace curlpp::options;

struct MemeGenerator{

	void printPopularMemes(std::ostream &out){
		curlpp::Cleanup cleanup;
		curlpp::Easy request;

		request.setOpt<Url>("http://version1.api.memegenerator.net/Generators_Select_ByPopular?pageIndex=0&pageSize=12");

		request.perform();


	}

};
