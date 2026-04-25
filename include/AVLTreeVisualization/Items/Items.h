#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include "raylib.h"
#include "raymath.h"
#pragma once

using namespace std;

struct circle {
    Vector2 pos;
    Vector2 targetPos;
    float radius;
    float thickness;
    Color color;

    circle(Vector2 pos = {0, 0}, Vector2 targetPos = {0, 0}, float radius = 0, float thickness = 0, Color color = WHITE) {
        this->pos = pos;
        this->targetPos = targetPos;
        this->radius = radius;
        this->thickness = thickness;
        this->color = color;
    }
};

struct line {
    Vector2 start;
    Vector2 targetStart;
    Vector2 end;
    Vector2 targetEnd;
    float thickness;
    Color color;

    line(Vector2 start = {0, 0}, Vector2 targetStart = {0, 0}, Vector2 end = {0, 0}, Vector2 targetEnd = {0, 0}, float thickness = 0, Color color = WHITE) {
        this->start = start;
        this->targetStart = targetStart;
        this->end = end;
        this->targetEnd = targetEnd;
        this->thickness = thickness;
        this->color = color;
    }
};

struct text {
    string str;
    Vector2 pos;
    Vector2 targetPos;
    float FontSize;
    float spacing;
    Color color;
    Font font;

    text(string str = "", Vector2 pos = {0, 0}, Vector2 targetPos = {0, 0}, float FontSize = 0, float spacing = 0, Color color = WHITE, Font font = GetFontDefault()) {
        this->str = str;
        this->pos = pos;
        this->targetPos = targetPos;
        this->FontSize = FontSize;
        this->spacing = spacing;
        this->color = color;
        this->font = font;
    }
};