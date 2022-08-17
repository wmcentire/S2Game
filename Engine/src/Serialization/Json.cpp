#include "Json.h"
#include "Core/Logger.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>

bool pb::json::Load(const std::string& filename, rapidjson::Document& document)
{
	std::ifstream stream(filename);
	if (stream.is_open() == false) {
		LOG("error opening file %s.", filename.c_str());
		return false;
	}
	else {
		rapidjson::IStreamWrapper istream(stream);
		document.ParseStream(istream);
	}
	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, int& data)
{
		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsInt() == false)
	{
		LOG("error reading json data %s", name.c_str());
		return false;
	}

	// set data 
	data = value[name.c_str()].GetInt();

	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, float& data)
{
	if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsNumber() ==
		false)
	{
		LOG("error reading json data %s", name.c_str());
		return false;
	}

	// set data 
	data = value[name.c_str()].GetFloat();

	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, bool& data)
{
	if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsInt() ==
		false)
	{
		LOG("error reading json data %s", name.c_str());
		return false;
	}

	// set data 
	data = value[name.c_str()].GetInt();

	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, std::string& data)
{
	if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsInt() ==
		false)
	{
		LOG("error reading json data %s", name.c_str());
		return false;
	}

	// set data 
	data = value[name.c_str()].GetInt();

	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, Vector2& data)
{
	// check if 'name' member exists and is an array with 2 elements 
	if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray()
		== false || value[name.c_str()].Size() != 2)
	{
		LOG("error reading json data %s", name.c_str());
		return false;

	}

	// create json array object 
	auto& jarr = value[name.c_str()];
	// get array values 
	for (rapidjson::SizeType i = 0; i < jarr.Size(); i++)
	{
		if (!jarr[i].IsNumber())
		{

			LOG("error reading json data (not a float) %s", name.c_str());
			return false;
		}

		data[i] = jarr[i].GetFloat();
	}

	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, Color& data)
{
	// check if 'name' member exists and is an array with 2 elements 
	if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray()
		== false || value[name.c_str()].Size() != 2)
	{
		LOG("error reading json data %s", name.c_str());
		return false;

	}

	// create json array object 
	auto& array = value[name.c_str()];
	// get array values 
	for (rapidjson::SizeType i = 0; i < array.Size(); i++)
	{
		if (!array[i].IsNumber())
		{

			LOG("error reading json data (not a float) %s", name.c_str());
			return false;
		}

		data[i] = array[i].GetFloat();
	}

	return true;
}
