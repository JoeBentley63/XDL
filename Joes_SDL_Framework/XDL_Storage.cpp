#include "XDL_Storage.h"

XDL_Storage* XDL_Storage::_me;

XDL_Storage::XDL_Storage(void)
{
}

XDL_Storage::~XDL_Storage(void)
{

}

XDL_Storage* XDL_Storage::GetInstance()
{
	if(_me!=NULL)
	{
		_me = new XDL_Storage();
	}
	return _me;
}
void XDL_Storage::SaveInt(int _value, char* _id)
{
	stringstream strs;
	strs << _value;
	string temp_str = strs.str();
	char* _normalized = (char*) temp_str.c_str();
	SaveValue(_normalized,_id);
}
void XDL_Storage::SaveCharPointer(char* _value, char* _id)
{
	SaveValue(_value,_id);
}
void XDL_Storage::SaveFloat(float _value, char* _id)
{
	char _normalized[32];
	sprintf(_normalized,"%f",_value);
	
	SaveValue(_normalized,_id);
}

void XDL_Storage::SaveValue(char* _value, char* _id)
{
	if(_dictionary.find(_id)!=_dictionary.end())//first we see if the image the player is requesting is already loaded.
	{
		//already in the dictionary
		_dictionary.at(_id) = _value;
	}
	else
	{
		_dictionary.insert(std::make_pair(_id,_value));//add it to the dictionary
	}
	
}

int XDL_Storage::LoadInt(char* _id)
{
	char* _normalized = LoadValue(_id);
	if(_normalized == NULL)
	{
		return NULL;
	}
	return atoi(_normalized);
}
char* XDL_Storage::LoadCharPointer(char* _id)
{
	char* _normalized = LoadValue(_id);
	if(_normalized == NULL)
	{
		return NULL;
	}
	return _normalized;
}
float XDL_Storage::LoadFloat(char* _id)
{
	char* _normalized = LoadValue(_id);
	if(_normalized == NULL)
	{
		return NULL;
	}
	return atof(_normalized);
}

char* XDL_Storage::LoadValue(char* _id)
{
	if(_dictionary.find(_id)!=_dictionary.end())//first we see if the image the player is requesting is already loaded.
	{
		//cout<<"Found in Dictionary----------------------------------------------------------------";
		return _dictionary.find(_id)->second;//if already loaded, then return it.
	}
	return NULL;
}