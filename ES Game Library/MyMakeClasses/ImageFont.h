#pragma once
#include "../ESGLib.h"
#include <vector>
#include <string>

class ImageFont{

public:
	~ImageFont() = default;

	static ImageFont& GetInstance(){

		static ImageFont instance;

		return instance;

	}

	void DirectDrawImageString(Vector3 position, Vector2 size, const char* str, ...);
	void SetImageString(Vector3 position, Vector2 size,bool addblend, const char* str, ...);
	void DrawString();
	void AddDrawString(float addalpha);

	void SrtingReset(){ this->strdatas_.clear(); }

	Vector2 GetDrawSize(Vector2 size, const char* str, ...);

	Vector2 GetCellSize() { return this->cellsize_; }

private:


	struct STRINGDATA{

		std::string str;
		Vector2 size;
		Vector3 position;
		bool addblend;

		STRINGDATA(Vector3 position, Vector2 size, bool addblend, std::string& str){

			this->str = str;
			this->size = size;
			this->position = position;
			this->addblend = addblend;

		}

	};

	void MakeString(std::string& inbuffer, const char* str, va_list args);
	void DrawImageString(Vector3 position, Vector2 size, std::string& str,float addalpha = 1.0f);


	ImageFont(){
	
		this->sp_ = GraphicsDevice.CreateSpriteFromFile(_T("font.png"));
		this->imagesize_ = Vector2(640.0f, 1280.0f);
		this->cellsize_ = Vector2(64.0f, 128.0f);
		this->imagecell_ = Vector2(10.0f, 10.0f);
		this->startnumber_ = 30;

	};

	SPRITE sp_;
	Vector2 cellsize_;
	Vector2 imagesize_;
	Vector2 imagecell_;
	int startnumber_;

	std::vector<STRINGDATA> strdatas_;
};

#define IMAGEFONT ImageFont::GetInstance()