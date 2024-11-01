#ifndef BUTTON_H
#define BUTTON_H

#include "SDL2/SDL.h"
#include <stdbool.h>


typedef void (*ButtonCallback)();
typedef enum {
	BUTTON_NORMAL,
	BUTTON_HOVERED,
	BUTTON_PRESSED
} ButtonState;//���ð�ť״̬
typedef struct {
	SDL_Rect rect;
	SDL_Texture* texture_button;
	SDL_Texture* hoverTexture;
	SDL_Texture* holdTexture;
	ButtonState state;
	ButtonCallback callback;//��ӻص�����ָ��
} Button;//���尴ť�ṹ��

typedef void (*EncryptFuncInt)(const char*, int);
typedef void (*EncryptFuncStr)(const char*, const char*);
typedef void (*operation_func)(const char*, const void*);

void renderButton(SDL_Renderer* renderer, Button* button);
Button createButton(ButtonState BUTTON_NORMAL,SDL_Renderer* renderer, const char* texturePath, const char* hoverTexturePath, const char* holdTexturePath, int x, int y,int w,int h, ButtonCallback callback);
//int button_clicked(SDL_Event* event, Button* buttons, int num_buttons);
bool isMouseOverButton(Button* button, int mouseX, int mouseY);
#endif
