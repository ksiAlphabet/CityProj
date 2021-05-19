#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#pragma once

class gameEngine
{
	int width, height;
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool run = true;
public:
	bool init(std::string title, int width, int height);
	bool loadData();

	void handleEvent();
	void update();
	void life();
	void render();
	void close();
	void getInfo();

	bool isRunning() { return run; }
};

class gameObject
{
public:
	SDL_Texture* mTexture;
	SDL_Renderer* renderer;

	int mWidth = 0, mHeight = 0; // wielkosci wyœwietlane
	int tWidth = 0, tHeight = 0; // wielkosci rzeczywiste tekstur
	int x, y;
public:
	gameObject(SDL_Renderer* renderer) : mTexture(nullptr), renderer(renderer), x(0), y(0) {}
	gameObject(SDL_Renderer* renderer, int x, int y) : mTexture(nullptr), renderer(renderer), x(x), y(y) {}
	~gameObject();

	void clearObject() {
		// trzeba pamiêtaæ ¿e przy u¿yciu tej funkcji trzeba na nowo ustaliæ wielkoœæ obiektu !!!
		// nie zmiena za to po³o¿enia obiektu !!!
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = mHeight = tWidth = tHeight = 0;
	}

	bool FromFile(std::string path) {
		clearObject();

		SDL_Texture* newTexture = nullptr;
		if (!mTexture)
		{
			SDL_Surface* loadedSurface = IMG_Load(path.c_str());
			if (!loadedSurface)
			{
				std::cout << "ERRO_LOAD_IMG: " << IMG_GetError() << std::endl;
			}
			else
			{
				newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
				if (!newTexture)
				{
					std::cout << "ERRO_CONVERT_TO_TEXTURE: " << SDL_GetError() << std::endl;
				}
				else
				{
					mWidth = tWidth = loadedSurface->w;
					mHeight = tHeight = loadedSurface->h;
				}

				SDL_FreeSurface(loadedSurface);
			}

			mTexture = newTexture;
		}
		return mTexture != nullptr;
	}

	void render(int x, int y ) {
		this->x = x;
		this->y = y;
		SDL_Rect renderQuad = { x, y, mWidth, mHeight };
		SDL_RenderCopy(renderer, mTexture, nullptr, &renderQuad);
	}

	void render() {
		SDL_Rect renderQuad = { x, y, mWidth, mHeight};
		SDL_RenderCopy(renderer, mTexture, nullptr, &renderQuad);
	}

	void changeSizeOfTexture(int a, int b, bool skal = true) {
		if (!skal) {
			mWidth = tWidth + a; mHeight = tHeight + b;
		}
		else {
			mWidth = tWidth * a; mHeight = tHeight * b;
		}
	}
	
	void getCenter(int& a, int& b) {
		a = x + mWidth / 2;
		b = y + mHeight / 2;
	}

	virtual void update() = 0;
};


