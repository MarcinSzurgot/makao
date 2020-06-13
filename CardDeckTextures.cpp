#include "CardDeckTextures.hpp"

CardDeckTextures::CardDeckTextures(const std::string& directory)
{
    const auto cardDeckImages = CardDeckImages(directory);
    for (const auto& [card, image] : cardDeckImages.images())
    {
        auto texture = sf::Texture();
        texture.loadFromImage(image);
        textures_.insert({card, std::move(texture)});
    }
    backCardTexture_.loadFromImage(cardDeckImages.backImage());
}

const sf::Texture& CardDeckTextures::operator[](const Card& card) const
{
    if (const auto texture = textures_.find(card); texture == end(textures_))
    {
        throw std::logic_error("Cannot find texture for a given card. Probably not loaded proper image file.");
    }
    else
    {
        return texture->second;
    }
}

const sf::Texture& CardDeckTextures::backCardTexture() const
{
    return backCardTexture_;
}