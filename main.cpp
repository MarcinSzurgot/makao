#include "CardsTypes.hpp"
#include "CardDeckImages.hpp"
#include "CardDeckTextures.hpp"

#include <SFML/Graphics.hpp>

#include <array>
#include <algorithm>
#include <memory>
#include <vector>
#include <map>

namespace
{

std::unique_ptr<sf::RenderWindow> window()
{
    constexpr auto windowTitle = "makao";
    constexpr auto framerateLimit = 50.f;
    const auto videoMode = sf::VideoMode(800u, 600u);

    auto window = std::make_unique<sf::RenderWindow>(videoMode, windowTitle);
    window->setFramerateLimit(framerateLimit);
    return window;
}

}

// my cards
// oponents cards
// cards at the table
// cards stack

struct CardsCollectionView : sf::Drawable, sf::Transformable
{
    CardsCollectionView(const CardDeckTextures& cardDeckTextures,
                        const std::vector<Card>& cards)
    {
        sprites_.reserve(size(cards));

        auto offset = sf::Vector2f();
        for (const auto& card : cards)
        {
            sprites_.emplace_back(sf::Sprite(cardDeckTextures[card]));
            sprites_.back().setPosition(offset);
            offset.x += sprites_.back().getTexture()->getSize().x;
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        for (const auto& sprite : sprites_)
        {
            target.draw(sprite, states);
        }
    }

private:
    std::vector<sf::Sprite> sprites_;
};

int main()
{
    const auto cardsTextures = CardDeckTextures("cards");
    auto cardsCollectionView = CardsCollectionView(cardsTextures, {
        Joker::Black,
        RegularCard{Suit::Club, Rank::Jack},
        RegularCard{Suit::Club, Rank::Jack},
        RegularCard{Suit::Heart, Rank::Ace},
        RegularCard{Suit::Spade, Rank::Queen},
        RegularCard{Suit::Diamond, Rank::Three},
        Joker::Red,
    });
    cardsCollectionView.scale(0.5f, 0.5f);
    for (auto window = ::window(); window->isOpen(); window->display())
    {
        for (auto event = sf::Event(); window->pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        window->clear();
        window->draw(cardsCollectionView);
    }
    return 0;
}