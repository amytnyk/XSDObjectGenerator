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
		void Write(IXmlSerializer& s);
		void Read(IXmlSerializer& s);
	};
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
		void Write(IXmlSerializer& s);
		void Read(IXmlSerializer& s);
	};
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
		void Write(IXmlSerializer& s);
		void Read(IXmlSerializer& s);
	};
}
void Test::shiporder::Write(IXmlSerializer& s)
{
	IXmlSerializer::Scope scope(s, "shiporder");
	s.WriteAttr("orderid", orderid.c_str());
	{
		IXmlSerializer::Scope scope(s, "orderperson");
 		s.Write(orderperson.c_str());
	}
	shipto.Write(s);
	for(int i = 0;i < item.size();i++)
	{
		item[i].Write(s); 
	}
}

void Test::shiporder::Read(IXmlSerializer& s)
{
	IXmlSerializer::Scope scope(s, "shiporder");
	orderid = s.ReadAttrStr("orderid");
	{
		IXmlSerializer::Scope scope(s, "orderperson");
 		orderperson = s.ReadStr();
	}
	shipto.Read(s);
	for(int i = 0;i < item.size();i++)
	{
		item.push_back(s.Read()); 
	}
}

void Test::shipto::Write(IXmlSerializer& s)
{
	IXmlSerializer::Scope scope(s, "shipto");
	{
		IXmlSerializer::Scope scope(s, "name");
 		s.Write(name.c_str());
	}
	{
		IXmlSerializer::Scope scope(s, "address");
 		s.Write(address.c_str());
	}
	{
		IXmlSerializer::Scope scope(s, "city");
 		s.Write(city.c_str());
	}
	{
		IXmlSerializer::Scope scope(s, "country");
 		s.Write(country.c_str());
	}
}

void Test::shipto::Read(IXmlSerializer& s)
{
	IXmlSerializer::Scope scope(s, "shipto");
	{
		IXmlSerializer::Scope scope(s, "name");
 		name = s.ReadStr();
	}
	{
		IXmlSerializer::Scope scope(s, "address");
 		address = s.ReadStr();
	}
	{
		IXmlSerializer::Scope scope(s, "city");
 		city = s.ReadStr();
	}
	{
		IXmlSerializer::Scope scope(s, "country");
 		country = s.ReadStr();
	}
}

void Test::item::Write(IXmlSerializer& s)
{
	IXmlSerializer::Scope scope(s, "item");
	{
		IXmlSerializer::Scope scope(s, "title");
 		s.Write(title.c_str());
	}
	{
		IXmlSerializer::Scope scope(s, "note");
 		s.Write(note.c_str());
	}
	{
		IXmlSerializer::Scope scope(s, "quantity");
 		s.Write(quantity.c_str());
	}
	{
		IXmlSerializer::Scope scope(s, "price");
 		s.Write(price);
	}
}

void Test::item::Read(IXmlSerializer& s)
{
	IXmlSerializer::Scope scope(s, "item");
	{
		IXmlSerializer::Scope scope(s, "title");
 		title = s.ReadStr();
	}
	{
		IXmlSerializer::Scope scope(s, "note");
 		note = s.ReadStr();
	}
	{
		IXmlSerializer::Scope scope(s, "quantity");
 		quantity = s.ReadStr();
	}
	{
		IXmlSerializer::Scope scope(s, "price");
 		price = s.ReadInt();
	}
}
