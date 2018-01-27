#include "ImageFont.h"

void ImageFont::DirectDrawImageString(Vector3 position, Vector2 size, const char* str, ...){

	if (this->sp_->IsNull()) return;

	std::string string;

	va_list args;
	va_start(args, str);
	this->MakeString(string, str,args);
	va_end(args);

	this->DrawImageString(position,size,string);
}

void ImageFont::DrawImageString(Vector3 position, Vector2 size, std::string& string, float addalpha){

	auto itr = string.begin();
	auto e_itr = string.end();

	Vector2 scale = Vector2_Zero;
	scale.x = size.x / this->cellsize_.x;
	scale.y = size.y / this->cellsize_.y;

	Vector3 pos = position;

	Rect userect;
	int rectnum;
	int rect_x;
	int rect_y;
	int cell_x = (int)this->cellsize_.x;
	int cell_y = (int)this->cellsize_.y;

	SPRITE sp = this->sp_;

	while (itr != e_itr){

		if (*itr == '\n'){

			pos.y += size.y;
			pos.x = position.x;
			itr++;
			continue;

		}

		if (*itr < 32){

			itr++;
			continue;

		}

		rectnum = *itr - this->startnumber_;
		rect_x = rectnum % (int)this->imagecell_.x;
		rect_y = rectnum / (int)this->imagecell_.x;
		userect = RectWH(rect_x * cell_x, rect_y * cell_y, cell_x, cell_y);

		SpriteBatch.Draw(*sp, pos, userect, addalpha, Vector3_Zero, Vector3_Zero, scale);

		pos.x += size.x;
		itr++;

	}

}

void ImageFont::SetImageString(Vector3 position, Vector2 size, bool addblend, const char* str, ...){

	std::string string;

	va_list args;
	va_start(args, str);
	this->MakeString(string, str, args);
	va_end(args);

	STRINGDATA newdata = STRINGDATA(position,size,addblend,string);

	this->strdatas_.push_back(newdata);

}

void ImageFont::DrawString(){

	for (auto strdata : this->strdatas_){

		this->DrawImageString(strdata.position,strdata.size,strdata.str);

	}

}

void ImageFont::AddDrawString(float addalpha){


	for (auto strdata : this->strdatas_){

		if (strdata.addblend != true) continue;

		this->DrawImageString(strdata.position, strdata.size, strdata.str, addalpha);

	}

}

Vector2 ImageFont::GetDrawSize(Vector2 size, const char* str, ...){

	std::string string;

	va_list args;
	va_start(args, str);
	this->MakeString(string, str, args);
	va_end(args);

	int max_x = 0;
	int now_x = 0;
	int max_y = 1;

	auto itr = string.begin();
	auto e_itr = string.end();

	while (itr != e_itr){

		if (*itr == '\n'){

			max_y++;
			now_x = 0;
			continue;

		}
		else{

			now_x++;

			if (now_x > max_x)max_x = now_x;

		}

		itr++;

	}

	return Vector2(size.x * max_x,size.y * max_y);

}

void ImageFont::MakeString(std::string& inbuffer, const char* str, va_list args){

	
	int length = ::_vscprintf(str, args) + 1;
	char* buffer = new char[length];
	::_vsnprintf(buffer, length, str, args);

	inbuffer = buffer;
	delete[] buffer;

}