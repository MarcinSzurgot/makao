#pragma once

#include "CardDeckImages.hpp"

#include <SFML/Graphics/Texture.hpp>

struct CardDeckTextures
{
    CardDeckTextures(const std::string& directory);
    const sf::Texture& operator[](const Card& card) const;
    const sf::Texture& backCardTexture() const;

private:
    std::map<Card, sf::Texture> textures_;
    sf::Texture backCardTexture_;
};