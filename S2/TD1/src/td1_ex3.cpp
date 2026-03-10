#include <charconv>
#include <cmath>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <windows.h>

enum class Operator { ADD, SUB, MUL, DIV, POW, OPEN_PAREN, CLOSE_PAREN };

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
    } else if (token == "^") {
      result.push_back(make_token(Operator::POW));
    } else if (token == "*") {
      result.push_back(make_token(Operator::MUL));
    } else if (token == "/") {
      result.push_back(make_token(Operator::DIV));
    } else if (token == "(") {
      result.push_back(make_token(Operator::OPEN_PAREN));
    } else if (token == ")") {
      result.push_back(make_token(Operator::CLOSE_PAREN));
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
      } else if (token.op == Operator::POW) {
        stack.push(std::pow(leftOperand, rightOperand));
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

int operator_precedence(Operator const op) {
  switch (op) {
  case Operator::ADD:
  case Operator::SUB:
    return 1;

  case Operator::MUL:
  case Operator::DIV:
    return 2;

  case Operator::POW:
    return 3;

  default:
    throw std::runtime_error("Opérateur inconnu");
  }
}

std::vector<Token> infix_to_npi_tokens(std::string const &expression) {

  std::vector<std::string> words = split_string(expression);
  std::vector<Token> tokens = tokenize(words);

  std::vector<Token> output;
  std::stack<Token> operators;

  for (const Token &token : tokens) {

    if (token.type == TypeOfToken::OPERAND) {
      output.push_back(token);
    }

    else if (token.type == TypeOfToken::OPERATOR) {

      if (token.op == Operator::OPEN_PAREN) {
        operators.push(token);
      }

      else if (token.op == Operator::CLOSE_PAREN) {

        while (!operators.empty() &&
               operators.top().op != Operator::OPEN_PAREN) {
          output.push_back(operators.top());
          operators.pop();
        }

        if (operators.empty()) {
          throw std::runtime_error("Parenthèses mismatched");
        }

        operators.pop();
      }

      else {

        while (!operators.empty() &&
               operators.top().type == TypeOfToken::OPERATOR &&
               operators.top().op != Operator::OPEN_PAREN &&
               operator_precedence(operators.top().op) >=
                   operator_precedence(token.op)) {

          output.push_back(operators.top());
          operators.pop();
        }

        operators.push(token);
      }
    }
  }

  while (!operators.empty()) {

    if (operators.top().op == Operator::OPEN_PAREN ||
        operators.top().op == Operator::CLOSE_PAREN) {
      throw std::runtime_error("Parenthèses mismatched");
    }

    output.push_back(operators.top());
    operators.pop();
  }

  return output;
}

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  std::cout << "- S2 TD1 - EX03 -" << std::endl;

  std::cout << "Entrez une expression en infixe (exemple: 3 + 4 * ( 5 + 6 )): ";
  std::string expression;
  std::getline(std::cin, expression);

  try {
    std::vector<Token> npi_tokens = infix_to_npi_tokens(expression);
    float result = npi_evaluate(npi_tokens);
    for (const Token &token : npi_tokens) {
      if (token.type == TypeOfToken::OPERAND) {
        std::cout << token.value << " ";
      } else if (token.type == TypeOfToken::OPERATOR) {
        switch (token.op) {
        case Operator::ADD:
          std::cout << "+ ";
          break;
        case Operator::SUB:
          std::cout << "- ";
          break;
        case Operator::MUL:
          std::cout << "* ";
          break;
        case Operator::DIV:
          std::cout << "/ ";
          break;
        case Operator::POW:
          std::cout << "^ ";
          break;
        default:
          break;
        }
      }
    }
    std::cout << "Résultat: " << result << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Erreur: " << e.what() << std::endl;
  }

  return 0;
}