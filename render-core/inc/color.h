#pragma once

struct color{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

static constexpr color Gray = { 45, 45, 45, 0xFF };
static constexpr color Black = { 100, 149, 237, 0xFF };
static constexpr color Cyan = { 0, 255, 255, 0xFF };
static constexpr color Yellow = { 255, 255, 0, 0xFF };
static constexpr color Magenta = { 255, 0, 255, 0xFF };
static constexpr color Green = { 0, 255, 0, 0xFF };
static constexpr color Red = { 255, 0, 0, 0xFF };
static constexpr color Blue = { 0, 0, 255, 0xFF };
static constexpr color Orange = { 255, 165, 0, 0xFF };