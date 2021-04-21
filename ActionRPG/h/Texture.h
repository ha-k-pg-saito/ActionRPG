#ifndef Texture_h_
#define Texture_h_

#include <map>
#include <string>
#include<iostream>

class Texture
{
public:
	//シングルトン
	static Texture* Instance()
	{
		static Texture instance;

		return &instance;
	}
	
public:
	void LoadTexture();									//画像の読み込み
	bool DrawTexture(std::map<std::string,int>);		//画像の描画

private:
	Texture() {}


};

#endif