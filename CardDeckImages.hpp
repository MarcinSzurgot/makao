#pragma once

#include "CardsTypes.hpp"

#include <SFML/Graphics/Image.hpp>

#include <map>

struct CardDeckImages
{
    CardDeckImages(const std::string& directory);

    const sf::Image& operator[](const Card& card) const;
    const sf::Image& backImage() const { return backImage_; }
    const std::map<Card, sf::Image>& images() const { return images_; }

private:
    std::map<Card, sf::Image> images_;
    sf::Image backImage_;
};