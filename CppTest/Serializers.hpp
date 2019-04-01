#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <pugixml.hpp>
#include <stack>

class IXmlSerializerWriter
{
public:
	virtual ~IXmlSerializerWriter() = default;
	virtual void Write(const char* name, int32_t value) = 0;
	virtual void Write(const char* name, double value) = 0;
	virtual void Write(const char* name, bool value) = 0;
	virtual void Write(const char* name, const char* value) = 0;
	virtual void WriteAttr(const char* name, bool value) = 0;
	virtual void WriteAttr(const char* name, const char* value) = 0;
	virtual void WriteAttr(const char* name, int32_t value) = 0;
	virtual void WriteAttr(const char* name, double value) = 0;
private:
	virtual void LeaveChild() = 0;
	virtual void AddChild(const char* name) = 0;
public:
	class Scope
	{
	private: IXmlSerializerWriter& _s;
	public: Scope(IXmlSerializerWriter& s, const char* name) : _s(s) {
		_s.AddChild(name);
	}
			~Scope() {
				_s.LeaveChild();
			}
	};
};

class IXmlSerializerReader
{
public:
	virtual ~IXmlSerializerReader() = default;
	//virtual bool ReadInt(const char*name, int32_t&value) = 0;

	virtual bool ReadInt(const char* name, int32_t& value) = 0;
	virtual bool ReadDouble(const char* name, double& value) = 0;
	virtual bool ReadBool(const char* name, bool& value) = 0;
	virtual bool ReadStr(const char* name, std::string& value) = 0;
	virtual std::vector<int32_t>	 ReadVectorInt(const char* name) = 0;
	virtual std::vector<double>		 ReadVectorDouble(const char* name) = 0;
	virtual std::vector<bool>		 ReadVectorBool(const char* name) = 0;
	virtual std::vector<std::string> ReadVectorStr(const char* name) = 0;
	virtual bool		ReadAttrBool(const char* name) = 0;
	virtual const char* ReadAttrStr(const char* name) = 0;
	virtual double		ReadAttrDouble(const char* name) = 0;
	virtual int32_t		ReadAttrInt(const char* name) = 0;
	//virtual bool NextChild(const char* name) = 0;
	//virtual void beginArray() = 0;
	//virtual void endArray() = 0;
private:
	virtual void LeaveChild(const char* name) = 0;
	virtual bool EnterChild(const char* name) = 0;
public:
	class Scope
	{
	public: bool exist() {
		return is_successfull;
	}
	private: IXmlSerializerReader& _s;
			 const char* _name;
			 bool is_successfull;
	public:
		Scope(IXmlSerializerReader& s, const char* name) : _s(s), _name(name) {
			is_successfull = _s.EnterChild(name);
		}
		~Scope() {
			if (is_successfull) {
				_s.LeaveChild(_name);
			}
		}
	};
};

class PugiXmlSerializerWriter : public IXmlSerializerWriter {
private:
	pugi::xml_document _doc;
	pugi::xml_node _cursor;
public:
	PugiXmlSerializerWriter() { _cursor = _doc; }

	void AddChild(const char* name) override { _cursor = _cursor.append_child(name); }
	void LeaveChild() override { _cursor = _cursor.parent(); }

	void Write(const char* name, int32_t value) override {
		_cursor.append_child(name).text().set(value);
	}

	void Write(const char* name, double value) override {
		_cursor.append_child(name).text().set(value);
	}

	void Write(const char* name, bool value) override {
		_cursor.append_child(name).text().set(value);
	}

	void Write(const char* name, const char* value) override {
		_cursor.append_child(name).text().set(value);
	}

	void WriteAttr(const char* name, bool value) override {
		_cursor.append_attribute(name).set_value(value);
	}

	void WriteAttr(const char* name, const char* value) override {
		_cursor.append_attribute(name).set_value(value);
	}

	void WriteAttr(const char* name, int32_t value) override {
		_cursor.append_attribute(name).set_value(value);
	}

	void WriteAttr(const char* name, double value) override {
		_cursor.append_attribute(name).set_value(value);
	}

	void SaveToFile(const char* file_name) {
		_doc.save_file(file_name);
	}
};

class PugiXmlSerializerReader : public IXmlSerializerReader
{
private:
	pugi::xml_document _doc;
	pugi::xml_node _cursor;
	std::stack<std::string> names;
public:
	PugiXmlSerializerReader() { _cursor = _doc; names.push(""); }

	bool EnterChild(const char* name) override {
		pugi::xml_node new_cursor;
		std::string new_name(name);
		if (new_name == names.top()) {
			names.pop();
			names.push(new_name);
			new_cursor = _cursor.next_sibling(name);
		}
		else {
			names.pop();
			names.push(new_name);
			new_cursor = _cursor.child(name);
		}
		if (new_cursor == NULL) {
			return false;
		}
		else {
			_cursor = new_cursor;
			return true;
		}
	}
	/*
	bool NextChild(const char* name) override {
		pugi::xml_node new_cursor = _cursor.next_sibling(name);
		if (new_cursor == NULL)
			return false;
		else {
			_cursor = new_cursor;
			return true;
		}
	}
	*/

	void LeaveChild(const char* cname) override {
		//names.pop();
		//names.push("");
		if (_cursor.next_sibling(cname) == NULL) {
			_cursor = _cursor.parent();
		}
	}

	bool hasMember(const char* name) {
		auto p = _cursor.child(name);
		return p != NULL;
	}

	bool ReadInt(const char* name, int32_t& value) override {
		if (!hasMember(name))
			return false;
		value = atoi(_cursor.child(name).child_value());
		return true;
	}

	bool ReadDouble(const char* name, double& value) override {
		if (!hasMember(name))
			return false;
		value = atof(_cursor.child(name).child_value());
		return true;
	}

	bool ReadBool(const char* name, bool& value) override {
		if (!hasMember(name))
			return false;
		value = _cursor.child(name).child_value() == "true" ? true : false;
		return true;
	}

	bool ReadStr(const char* name, std::string& value) override {
		if (!hasMember(name))
			return false;
		value = _cursor.child(name).child_value();
		return true;
	}

	bool ReadAttrBool(const char* name) override {
		return _cursor.attribute(name).as_bool();
	}

	const char* ReadAttrStr(const char* name) override {
		return _cursor.attribute(name).as_string();
	}

	std::vector<int32_t> ReadVectorInt(const char* name) override {
		std::vector<int32_t> r;
		for (pugi::xml_node tool = _cursor.child(name); tool; tool = tool.next_sibling(name))
		{
			r.push_back(tool.text().as_int());
		}
		return r;
	}

	std::vector<double> ReadVectorDouble(const char* name) override {
		std::vector<double> r;
		for (pugi::xml_node tool = _cursor.child(name); tool; tool = tool.next_sibling(name))
		{
			r.push_back(tool.text().as_double());
		}
		return r;
	}

	std::vector<std::string> ReadVectorStr(const char* name) override {
		std::vector<std::string> r;
		for (pugi::xml_node tool = _cursor.child(name); tool; tool = tool.next_sibling(name))
		{
			r.push_back(tool.text().as_string());
		}
		return r;
	}

	std::vector<bool> ReadVectorBool(const char* name) override {
		std::vector<bool> r;
		for (pugi::xml_node tool = _cursor.child(name); tool; tool = tool.next_sibling(name))
		{
			r.push_back(tool.text().as_bool());
		}
		return r;
	}

	int32_t ReadAttrInt(const char* name) override {
		return _cursor.attribute(name).as_int();
	}

	double ReadAttrDouble(const char* name) override {
		return _cursor.attribute(name).as_double();
	}

	void Load(const char* file_name) {
		_doc.load_file(file_name);
	}
};