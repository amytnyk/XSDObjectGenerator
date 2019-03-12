#pragma once

// Copyright 2008, Microsoft Corporation and 2019 Alex Mytnyk
// Sample Code - Use restricted to terms of use defined in the accompanying license agreement (EULA.doc)

//--------------------------------------------------------------
// Autogenerated by XSDObjectGen version 2.0.0.0
// Schema file: schema.xsd
// Creation Date: 3/10/2019 18:34:45
//--------------------------------------------------------------

#include <iostream>
#include <string>
#include <ctime>

namespace Test
{

	struct Declarations
	{
		const std::string SchemaVersion = "";
	};
	//BEGIN_CPP2SERIALIZE



	//MAIN_CLASS
	//CLASS
	struct shiporder
	{

		//ATTRIBUTE_STD
		std::string orderid;

		//ELEMENT_STD
		std::string orderperson;

		//ELEMENT_CLASS
		shipto shipto;

		//LIST
		std::vector<item> item;

		shiporder()
		{
		}
	};


	//CLASS
	struct shipto
	{

		//ELEMENT_STD
		std::string name;

		//ELEMENT_STD
		std::string address;

		//ELEMENT_STD
		std::string city;

		//ELEMENT_STD
		std::string country;

		shipto()
		{
		}
	};


	//CLASS
	struct item
	{

		//ELEMENT_STD
		std::string title;

		//ELEMENT_STD
		std::string note;

		//ELEMENT_STD
		std::string quantity;

		//ELEMENT_PROTO
		int price;

		item()
		{
		}
	};
}
