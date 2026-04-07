#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <unordered_set>
#include <vector>

enum class CardKind {
  Heart,
  Diamond,
  Club,
  Spade,
};

enum class CardValue {
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
  Ace,
};

struct Card {
  CardKind kind;
  CardValue value;

  /**
  Fonction de hachage pour la carte. Qui retourne un nombre entier unique pour
  chaque carte (entre 0 et 51 vu qu'il y a 52 cartes dans un jeu standard).
  Pour cela, on peut utiliser la formule suivante :
  hash = numéro de la couleur * 13 + numéro de la valeur
  Où le numéro de la couleur est un entier entre 0 et 3
  Où le numéro de la valeur est un entier entre 0 et 12
  */
  size_t hash() const {
    return static_cast<size_t>(kind) * 13 + static_cast<size_t>(value);
  };
};

namespace std {
template <> struct hash<Card> {
  size_t operator()(Card const &card) const { return card.hash(); }
};
} // namespace std

bool operator==(const Card &a, const Card &b) {
  return a.kind == b.kind && a.value == b.value;
}

std::vector<Card> get_cards(size_t const size) {
  std::vector<Card> cards{};
  cards.reserve(size);
  for (size_t i{0}; i < size; ++i) {
    cards.push_back({static_cast<CardKind>(rand() % 4),
                     static_cast<CardValue>(rand() % 13)});
  }
  return cards;
}

std::string card_name(Card const &card) {
  std::string name{};

  unsigned int card_value{(static_cast<unsigned int>(card.value) + 2) % 14};

  if (card_value < 10) {
    name += '0' + std::to_string(card_value);
  } else if (card_value == 10) {
    name += "10";
  } else if (card_value == 11) {
    name += 'J';
  } else if (card_value == 12) {
    name += 'Q';
  } else if (card_value == 13) {
    name += 'K';
  }

  name += " of ";

  if (card.kind == CardKind::Heart) {
    name += "Heart";
  } else if (card.kind == CardKind::Diamond) {
    name += "Diamond";
  } else if (card.kind == CardKind::Club) {
    name += "Club";
  } else if (card.kind == CardKind::Spade) {
    name += "Spade";
  }
  return name;
}

int main() {
  srand(time(0));
  std::unordered_set<Card> card_set;
  auto cards = get_cards(100);

  for (const auto &card : cards) {
    std::cout << card_name(card) << " - Hash : " << std::hash<Card>{}(card)
              << std::endl;
    card_set.insert(card);
  }

  return 0;
}