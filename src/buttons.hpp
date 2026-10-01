#pragma once
#include <raylib.h>


class Button {
public:
    Button(const char* texturePath, Vector2 position, float scale);
    ~Button();
    void Draw();
    bool isTouched(Vector2 mousePosition, bool mousePressed);

private:
    Texture2D texture;
    Vector2 position;
};