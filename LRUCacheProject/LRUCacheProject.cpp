// LRUCacheProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "LRUCache.h"
#include "boost/optional.hpp"

int main()
{
	LRUCache<std::string, std::string> cache(2);

	cache.Put("A", "1");
	cache.Put("B", "2");
	cache.Put("C", "3");

	boost::optional<std::string> x = cache.Get("A");
	if (!x)
		std::cout << "No data available" << std::endl;
	else 
		std::cout << "data available" << std::endl;

	x = cache.Get("B");
	if (!x)
		std::cout << "No data available" << std::endl;
	else
		std::cout << "data available" << std::endl;


    return 0;
}

