#pragma once

#include <iostream>
#include <string_view>
#include <type_traits>
#include <variant>

template<typename E>
concept Enumerable = std::is_enum_v<E>;

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

enum class CardType
{
    Regular,
    Joker
};

enum class Suit
{
    Diamond,
    Club,
    Heart,
    Spade,
};

enum class Rank
{
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
};

enum class Joker
{
    Red,
    Black,
};

constexpr std::string_view string(Suit suit)
{
    switch (suit)
    {
        case Suit::Diamond: return "Suit::Diamond";
        case Suit::Club:    return "Suit::Club";
        case Suit::Heart:   return "Suit::Heart";
        case Suit::Spade:   return "Suit::Spade";
    }
    throw std::invalid_argument("An invalid enum case.");
}

constexpr std::string_view string(Rank rank)
{
    switch (rank)
    {
        case Rank::Ace:   return "Rank::Ace";
        case Rank::Two:   return "Rank::Two";
        case Rank::Three: return "Rank::Three";
        case Rank::Four:  return "Rank::Four";
        case Rank::Five:  return "Rank::Five";
        case Rank::Six:   return "Rank::Six";
        case Rank::Seven: return "Rank::Seven";
        case Rank::Eight: return "Rank::Eight";
        case Rank::Nine:  return "Rank::Nine";
        case Rank::Ten:   return "Rank::Ten";
        case Rank::Jack:  return "Rank::Jack";
        case Rank::Queen: return "Rank::Queen";
        case Rank::King:  return "Rank::King";
    }
    throw std::invalid_argument("An invalid enum case.");
}

constexpr std::string_view string(CardType type)
{
    switch (type)
    {
        case CardType::Regular: return "CardType::Regular"; 
        case CardType::Joker:   return "CardType::Joker";   
    }
    throw std::invalid_argument("An invalid enum case.");
}

constexpr std::string_view string(Joker color)
{
    switch (color)
    {
        case Joker::Red:   return "Joker::Red";
        case Joker::Black: return "Joker::Black";
    }
    throw std::invalid_argument("An invalid enum case.");
}

template<Enumerable E>
constexpr std::underlying_type_t<E> integer(E value)
{
    return static_cast<std::underlying_type_t<E>>(value);
}

template<Enumerable E> constexpr bool operator< (E lhs, E rhs) { return integer(lhs) < integer(rhs); }
template<Enumerable E> constexpr bool operator> (E lhs, E rhs) { return integer(rhs) < integer(lhs); }
template<Enumerable E> constexpr bool operator<=(E lhs, E rhs) { return !(lhs > rhs); }   
template<Enumerable E> constexpr bool operator>=(E lhs, E rhs) { return !(lhs < rhs); }   
template<Enumerable E> constexpr bool operator==(E lhs, E rhs) { return integer(lhs) == integer(rhs); }
template<Enumerable E> constexpr bool operator!=(E lhs, E rhs) { return !(lhs == rhs); }   

template<Enumerable E>
std::ostream& operator<<(std::ostream& os, E value)
{
    return os << string(value);
}

struct RegularCard
{
    Suit suit;
    Rank rank;

    friend constexpr bool operator<(const RegularCard& lhs, const RegularCard& rhs)
    {
        return lhs.suit != rhs.suit 
               ? lhs.suit < rhs.suit
               : lhs.rank < rhs.rank;
    }

    friend std::ostream& operator<<(std::ostream& os, const RegularCard& card)
    {
        return os << "RegularCard(" << string(card.suit) << ", " << string(card.rank) << ")";
    }
};

using Card = std::variant<RegularCard, Joker>;

constexpr bool operator<(const Card& lhs, const Card& rhs)
{
    return std::visit(overload {
        [](Joker lhs, Joker rhs)             { return lhs < rhs; },
        [](RegularCard lhs, RegularCard rhs) { return lhs < rhs; },
        [](RegularCard, Joker)               { return true; },
        [](auto, auto)                       { return false; }
    }, lhs, rhs);
}

inline std::ostream& operator<<(std::ostream& os, const Card& card)
{
    return std::visit(overload {
        [&os](Joker       card) -> std::ostream& { return os << card; },
        [&os](RegularCard card) -> std::ostream& { return os << card; }
    }, card);
}