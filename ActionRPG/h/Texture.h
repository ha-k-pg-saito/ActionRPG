#include <map>
#include <string>
#ifndef Texture_h_
#define Texture_h_

class Texture
{
public:
	static Texture* Instance()
	{
		static Texture instance;

		return &instance;
	}
	
private:
	bool DrawTexture(std::map<std::string,int>);
	void LoadTexture();

private:
	Texture() {}

};

#endif