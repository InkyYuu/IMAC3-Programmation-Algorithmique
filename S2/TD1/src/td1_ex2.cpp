#include <charconv>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <windows.h>

enum class Operator { ADD, SUB, MUL, DIV };

enum class TypeOfToken { OPERATOR, OPERAND };

struct Token {
  TypeOfToken type;
  float value;
  Operator op;
};

bool is_floating(std::string const &s) {
  float value;
  auto [p, ec] = std::from_chars(s.data(), s.data() + s.size(), value);
  return ec == std::errc() && p == s.data() + s.size();
}

Token make_token(float value) {
  return Token{TypeOfToken::OPERAND, value, Operator::ADD};
}

Token make_token(Operator op) { return Token{TypeOfToken::OPERATOR, 0.0f, op}; }

std::vector<Token> tokenize(std::vector<std::string> const &tokens) {
  std::vector<Token> result;
  for (const auto &token : tokens) {
    if (is_floating(token)) {
      result.push_back(make_token(std::stof(token)));
    } else if (token == "+") {
      result.push_back(make_token(Operator::ADD));
    } else if (token == "-") {
      result.push_back(make_token(Operator::SUB));
    } else if (token == "*") {
      result.push_back(make_token(Operator::MUL));
    } else if (token == "/") {
      result.push_back(make_token(Operator::DIV));
    } else {
      throw std::runtime_error("Token inconnu: " + token);
    }
  }
  return result;
}

float npi_evaluate(std::vector<Token> const &tokens) {
  std::stack<float> stack;
  for (const Token &token : tokens) {
    if (token.type == TypeOfToken::OPERAND) {
      stack.push(token.value);
    }

    else if (token.type == TypeOfToken::OPERATOR) {
      if (stack.size() < 2) {
        throw std::runtime_error(
            "Expression invalide: opérateur sans suffisamment d'opérandes");
      }
      float rightOperand{stack.top()};
      stack.pop();
      float leftOperand{stack.top()};
      stack.pop();

      if (token.op == Operator::ADD) {
        stack.push(leftOperand + rightOperand);
      } else if (token.op == Operator::SUB) {
        stack.push(leftOperand - rightOperand);
      } else if (token.op == Operator::MUL) {
        stack.push(leftOperand * rightOperand);
      } else if (token.op == Operator::DIV) {
        if (rightOperand == 0) {
          throw std::runtime_error("Division par zéro");
        }
        stack.push(leftOperand / rightOperand);
      }
    } else {
      throw std::runtime_error("Token de type inconnu");
    }
  }
  if (stack.size() != 1) {
    throw std::runtime_error("Expression invalide: trop d'opérandes");
  }
  return stack.top();
}

std::vector<std::string> split_string(std::string const &s) {
  std::istringstream in(s); // transforme une chaîne en flux de caractères, cela
                            // simule un flux comme l'est std::cin
  // l’itérateur va lire chaque element de "in", comme un flux d'entrée, chaque
  // élément est séparé par un espace
  return std::vector<std::string>(std::istream_iterator<std::string>(in),
                                  std::istream_iterator<std::string>());
}

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  std::cout << "- S2 TD1 - EX02 -" << std::endl;

  std::cout << "Entrez une expression en NPI (exemple: 3 4 +): ";
  std::string expression;
  std::getline(std::cin, expression);

  std::vector<std::string> tokens = split_string(expression);

  try {
    std::vector<Token> tokenized_tokens = tokenize(tokens);
    float result = npi_evaluate(tokenized_tokens);
    std::cout << "Résultat: " << result << std::endl;
  } catch (const std::runtime_error &e) {
    std::cerr << "Erreur: " << e.what() << std::endl;
  }

  return 0;
}