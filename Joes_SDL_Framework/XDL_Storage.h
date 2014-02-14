#ifndef _PERSISTANT_STORAGE_H
#define _PERSISTANT_STORAGE_H

#include <map>
#include <sstream>
#include <stdlib.h>
using namespace std;

class XDL_Storage
{
public:
	static XDL_Storage* GetInstance();
	~XDL_Storage(void);
	void SaveInt(int _value, char* _id);//basically incharge of normalizing the int, then it calls SaveValue
	void SaveCharPointer(char* _value, char* _id);
	void SaveFloat(float _value, char* _id);

	int LoadInt(char* _id);
	char* LoadCharPointer(char* _id);
	float LoadFloat(char* _id);
private:
	static XDL_Storage* _me;
	XDL_Storage(void);
	void SaveValue(char* _value, char* _id);
	char* LoadValue(char* _id);
	
	void LoadAll();
	void SaveAll();

	map<char*,char*> _dictionary;

};

#endif
