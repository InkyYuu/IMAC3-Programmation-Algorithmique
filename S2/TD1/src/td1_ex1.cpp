#include <charconv>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <windows.h>

std::vector<std::string> split_string(std::string const &s) {
  std::istringstream in(s); // transforme une chaîne en flux de caractères, cela
                            // simule un flux comme l'est std::cin
  // l’itérateur va lire chaque element de "in", comme un flux d'entrée, chaque
  // élément est séparé par un espace
  return std::vector<std::string>(std::istream_iterator<std::string>(in),
                                  std::istream_iterator<std::string>());
}

bool is_floating_manual(std::string const &s) {
  bool has_dot = false;
  for (char c : s) {
    if (c == '.') {
      if (has_dot)
        return false;
      has_dot = true;
    } else if (!std::isdigit(c)) {
      return false;
    }
  }
  return !s.empty();
}

bool is_floating_17(std::string const &s) {
  float value;
  auto [p, ec] = std::from_chars(s.data(), s.data() + s.size(), value);
  return ec == std::errc() && p == s.data() + s.size();
}

bool is_floating(std::string const &s, bool use_17 = true) {
  if (use_17) {
    return is_floating_17(s);
  }
  return is_floating_manual(s);
}

float npi_evaluate(std::vector<std::string> const &tokens) {
  std::stack<float> stack;
  for (const auto &token : tokens) {
    if (is_floating(token)) {
      stack.push(std::stof(token));
    }

    else if (token == "+" || token == "-" || token == "*" || token == "/") {
      if (stack.size() < 2) {
        throw std::runtime_error(
            "Expression invalide: opérateur sans suffisamment d'opérandes");
      }
      float rightOperand{stack.top()};
      stack.pop();
      float leftOperand{stack.top()};
      stack.pop();

      if (token == "+") {
        stack.push(leftOperand + rightOperand);
      } else if (token == "-") {
        stack.push(leftOperand - rightOperand);
      } else if (token == "*") {
        stack.push(leftOperand * rightOperand);
      } else if (token == "/") {
        if (rightOperand == 0) {
          throw std::runtime_error("Division par zéro");
        }
        stack.push(leftOperand / rightOperand);
      }
    } else {
      throw std::runtime_error("Token inconnu: " + token);
    }
  }
  if (stack.size() != 1) {
    throw std::runtime_error("Expression invalide: trop d'opérandes");
  }
  return stack.top();
}

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  std::cout << "- S2 TD1 - EX01 -" << std::endl;

  std::cout << "Entrez une expression en NPI (exemple: 3 4 +): ";
  std::string expression;
  std::getline(std::cin, expression);

  std::vector<std::string> tokens = split_string(expression);

  try {
    float result = npi_evaluate(tokens);
    std::cout << "Résultat: " << result << std::endl;
  } catch (const std::runtime_error &e) {
    std::cerr << "Erreur: " << e.what() << std::endl;
  }

  return 0;
}