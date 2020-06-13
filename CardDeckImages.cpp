#include "CardDeckImages.hpp"

#include <array>
#include <string>

using namespace std::string_literals;

namespace
{

std::string filename(Suit suit)
{
    switch (suit)
    {
        case Suit::Diamond: return "diamond";
        case Suit::Club:    return "club";
        case Suit::Heart:   return "heart";
        case Suit::Spade:   return "spade";
    }
    throw std::invalid_argument("An invalid enum case value:");
}

std::string filename(Rank rank)
{
    switch (rank)
    {
        case Rank::Ace:   return "1";
        case Rank::Two:   return "2";
        case Rank::Three: return "3";
        case Rank::Four:  return "4";
        case Rank::Five:  return "5";
        case Rank::Six:   return "6";
        case Rank::Seven: return "7";
        case Rank::Eight: return "8";
        case Rank::Nine:  return "9";
        case Rank::Ten:   return "10";
        case Rank::Jack:  return "jack";
        case Rank::Queen: return "queen";
        case Rank::King:  return "king";
    }
    throw std::invalid_argument("An invalid enum case value:");
}

std::string filename(Joker joker)
{
    switch (joker)
    {
        case Joker::Red:   return "joker_red.png";
        case Joker::Black: return "joker_black.png";
    }
    throw std::invalid_argument("An invalid enum case value:");
}

std::string filename(const RegularCard& card)
{
    return filename(card.suit) + "_" + filename(card.rank) + ".png";
}

std::string filename(const Card& card)
{
    return std::visit(overload{
        [](const RegularCard& card) { return filename(card); },
        [](Joker joker)             { return filename(joker); }
    }, card);
}

std::map<Card, std::string> cardsFilenames()
{
    static const auto cardsFilenames = [&](){
        constexpr auto suits = std::array{
            Suit::Diamond,
            Suit::Club,
            Suit::Heart,
            Suit::Spade,
        };

        constexpr auto ranks = std::array{
            Rank::Ace,
            Rank::Two,
            Rank::Three,
            Rank::Four,
            Rank::Five,
            Rank::Six,
            Rank::Seven,
            Rank::Eight,
            Rank::Nine,
            Rank::Ten,
            Rank::Jack,
            Rank::Queen,
            Rank::King
        };

        auto filenames = std::map<Card, std::string>();
        for (const auto suit : suits)
        {
            for (const auto rank : ranks)
            {
                const auto card = Card(RegularCard{suit, rank});
                filenames.insert({card, filename(card)});
            }
        }

        const auto redJoker = Card(Joker::Red);
        const auto blackJoker = Card(Joker::Black);
        filenames.insert({redJoker, filename(redJoker)});
        filenames.insert({blackJoker, filename(blackJoker)});
        return filenames;
    } ();
    return cardsFilenames;
}

}

CardDeckImages::CardDeckImages(const std::string& directory)
{
    for(const auto& [card, filename] : cardsFilenames())
    {
        auto image = sf::Image();
        const auto filepath = directory + "/" + filename;
        if (!image.loadFromFile(filepath))
        {
            throw std::invalid_argument("Cannot load image at path: "s + filepath);
        }
        images_.insert({card, image});
    }

    const auto filepath = directory + "/back.png";
    if (!backImage_.loadFromFile(filepath))
    {
        throw std::invalid_argument("Cannot load back image at path: "s + filepath);
    }
}

const sf::Image& CardDeckImages::operator[](const Card& card) const
{
    if (const auto image = images_.find(card); image == end(images_))
    {
        throw std::logic_error("Cannot find image for a given card. Probably not loaded proper image file.");
    }
    else
    {
        return image->second;
    }
}