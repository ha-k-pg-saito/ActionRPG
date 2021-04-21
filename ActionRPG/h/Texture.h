#ifndef Texture_h_
#define Texture_h_

#include <map>
#include <string>
#include<iostream>

class Texture
{
public:
	//ƒVƒ“ƒOƒ‹ƒgƒ“
	static Texture* Instance()
	{
		static Texture instance;

		return &instance;
	}
	
public:
	void LoadTexture();									//‰æ‘œ‚Ì“Ç‚İ‚İ
	bool DrawTexture(std::map<std::string,int>);		//‰æ‘œ‚Ì•`‰æ

private:
	Texture() {}


};

#endif