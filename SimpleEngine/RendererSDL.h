#pragma once
#include <SDL.h>
#include <vector>
#include "Vector2.h"
#include "Actor.h"
#include "IRenderer.h"

// Compilation + rapide, si pas d'appel de constructeur
//class Window;
//struct Rectangle;

class RendererSDL : public IRenderer
{
public:
	/*
	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};
	*/

	RendererSDL() = default;
	virtual ~RendererSDL();
	RendererSDL(const RendererSDL&) = delete;
	RendererSDL& operator = (const RendererSDL&) = delete;

	bool initialize(Window& window);

	void beginDraw();
	void draw();
	void endDraw();
	IRenderer::Type type() { return Type::SDL; }

	void drawRect(const Rectangle& rect);
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprites();
	void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcTect, Vector2 origin, Flip flip) const;

	inline SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }
	void close();

private:
	SDL_Renderer* SDLRenderer{ nullptr };
	std::vector<SpriteComponent*> sprites;
};