#include "Json.h"
#include "Core/Logger.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "rapidjson/istreamwrapper.h"
#include "Math/Rect.h"
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
	// check if 'name' member exists 
	if (!value.HasMember(name.c_str())) return false;

	// check if data is the expected type 
	if (!value[name.c_str()].IsInt())
	{
		LOG("error reading json data int %s", name.c_str());
		return false;
	}

	// set data 
	data = value[name.c_str()].GetInt();

	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, float& data)
{
	// check if 'name' member exists 
	if (!value.HasMember(name.c_str())) return false;

	// check if data is the expected type 
	if (!value[name.c_str()].IsInt())
	{
		LOG("error reading json data float %s", name.c_str());
		return false;
	}

	// set data 
	data = value[name.c_str()].GetFloat();

	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, bool& data)
{
	if (value.HasMember(name.c_str()) == false) return false;

	if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsBool() ==
		false)
	{
		LOG("error reading json data bool %s", name.c_str());
		return false;
	}

	// set data 
	data = value[name.c_str()].GetBool();

	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, std::string& data)
{
	if (value.HasMember(name.c_str()) == false) return false;

	if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsString() ==
		false)
	{
		LOG("error reading json data string %s", name.c_str());
		return false;
	}

	// set data 
	data = value[name.c_str()].GetString();

	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, Vector2& data)
{
	if (value.HasMember(name.c_str()) == false) return false;

	// check if 'name' member exists and is an array with 2 elements 
	if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray()
		== false || value[name.c_str()].Size() != 2)
	{
		LOG("error reading json data float color %s", name.c_str());
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
	if (value.HasMember(name.c_str()) == false) return false;

	// check if 'name' member exists and is an array with 2 elements 
	if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray()
		== false || value[name.c_str()].Size() != 4)
	{
		LOG("error reading json data int color %s", name.c_str());
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

		data[i] = array[i].GetInt();
	}

	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, Rect& data)
{
	if (value.HasMember(name.c_str()) == false) return false;

	// check if 'name' member exists and is an array with 2 elements 
	if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray()
		== false || value[name.c_str()].Size() != 4)
	{
		LOG("error reading json data rect %s", name.c_str());
		return false;

	}

	// create json array object 
	auto& array = value[name.c_str()];
	// get array values 

	data.x = (int)array[0].GetInt();
	data.y = (int)array[1].GetInt();
	data.w = (int)array[2].GetInt();
	data.h = (int)array[3].GetInt();

	
	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data)
{

	if (value.HasMember(name.c_str()) == false) return false;

	// check if 'name' member exists and is an array with 2 elements 
	if ( !value[name.c_str()].IsArray())
	{
		LOG("error reading json data vector string %s", name.c_str());
		return false;

	}

	// create json array object 
	auto& array = value[name.c_str()];
	// get array values 
	for (rapidjson::SizeType i = 0; i < array.Size(); i++)
	{
		if (!array[i].IsString())
		{

			LOG("error reading json data (not a float) %s", name.c_str());
			return false;
		}

		data.push_back(array[i].GetString());
	}

	return true;
}

bool pb::json::Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data)
{
	if (value.HasMember(name.c_str()) == false) return false;
	// check if 'name' member exists and is an array with 2 elements 
	if (!value[name.c_str()].IsArray())
	{
		LOG("error reading json data vector int %s", name.c_str());
		return false;

	}

	// create json array object 
	auto& array = value[name.c_str()];
	// get array values 
	for (rapidjson::SizeType i = 0; i < array.Size(); i++)
	{
		if (!array[i].IsInt())
		{

			LOG("error reading json data (not a float) %s", name.c_str());
			return false;
		}

		data.push_back(array[i].GetInt());
	}
	return true;
}