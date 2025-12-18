#include "math_operations.h"
#include <cmath>
#include <algorithm>
#include <cctype>
#include <sstream>

namespace MathLib {

    const double Geometry::PI = 3.14159265358979323846;

    // ============= Calculator =============
    int Calculator::add(int a, int b) {
        return a + b;
    }

    int Calculator::subtract(int a, int b) {
        return a - b;
    }

    int Calculator::multiply(int a, int b) {
        return a * b;
    }

    double Calculator::divide(int a, int b) {
        if (b == 0) {
            throw std::runtime_error("Division by zero");
        }
        return static_cast<double>(a) / b;
    }

    int Calculator::factorial(int n) {
        if (n < 0) {
            throw std::invalid_argument("Factorial is not defined for negative numbers");
        }
        if (n == 0 || n == 1) {
            return 1;
        }

        int result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

    bool Calculator::isPrime(int number) {
        if (number <= 1) return false;
        if (number == 2) return true;
        if (number % 2 == 0) return false;

        for (int i = 3; i * i <= number; i += 2) {
            if (number % i == 0) {
                return false;
            }
        }
        return true;
    }

    int Calculator::gcd(int a, int b) {
        a = std::abs(a);
        b = std::abs(b);

        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    int Calculator::lcm(int a, int b) {
        if (a == 0 || b == 0) return 0;
        return std::abs(a * b) / gcd(a, b);
    }

    double Calculator::average(const std::vector<double>& numbers) {
        if (numbers.empty()) {
            throw std::invalid_argument("Cannot calculate average of empty collection");
        }

        double sum = 0;
        for (double num : numbers) {
            sum += num;
        }
        return sum / numbers.size();
    }

    int Calculator::max(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            throw std::invalid_argument("Cannot find max of empty collection");
        }

        int maxVal = numbers[0];
        for (size_t i = 1; i < numbers.size(); ++i) {
            if (numbers[i] > maxVal) {
                maxVal = numbers[i];
            }
        }
        return maxVal;
    }

    int Calculator::min(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            throw std::invalid_argument("Cannot find min of empty collection");
        }

        int minVal = numbers[0];
        for (size_t i = 1; i < numbers.size(); ++i) {
            if (numbers[i] < minVal) {
                minVal = numbers[i];
            }
        }
        return minVal;
    }

    double Calculator::standardDeviation(const std::vector<double>& numbers) {
        if (numbers.size() < 2) {
            throw std::invalid_argument("Need at least 2 numbers for standard deviation");
        }

        double avg = average(numbers);
        double variance = 0;

        for (double num : numbers) {
            variance += (num - avg) * (num - avg);
        }

        variance /= (numbers.size() - 1); // Sample standard deviation
        return std::sqrt(variance);
    }

    // ============= StringUtils =============
    std::string StringUtils::reverse(const std::string& str) {
        std::string reversed = str;
        std::reverse(reversed.begin(), reversed.end());
        return reversed;
    }

    bool StringUtils::isPalindrome(const std::string& str) {
        std::string cleanStr;
        // Remove spaces and convert to lowercase
        for (char c : str) {
            if (!std::isspace(c)) {
                cleanStr += std::tolower(c);
            }
        }

        std::string reversed = reverse(cleanStr);
        return cleanStr == reversed;
    }

    std::string StringUtils::toUpper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
            [](unsigned char c) { return std::toupper(c); });
        return result;
    }

    std::string StringUtils::toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
            [](unsigned char c) { return std::tolower(c); });
        return result;
    }

    int StringUtils::countVowels(const std::string& str) {
        int count = 0;
        std::string vowels = "aeiouAEIOU";

        for (char c : str) {
            if (vowels.find(c) != std::string::npos) {
                ++count;
            }
        }
        return count;
    }

    std::vector<std::string> StringUtils::split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;

        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }

        return tokens;
    }

    // ============= Geometry =============
    double Geometry::circleArea(double radius) {
        if (radius < 0) {
            throw std::invalid_argument("Radius cannot be negative");
        }
        return PI * radius * radius;
    }

    double Geometry::circleCircumference(double radius) {
        if (radius < 0) {
            throw std::invalid_argument("Radius cannot be negative");
        }
        return 2 * PI * radius;
    }

    double Geometry::rectangleArea(double width, double height) {
        if (width < 0 || height < 0) {
            throw std::invalid_argument("Dimensions cannot be negative");
        }
        return width * height;
    }

    double Geometry::triangleArea(double base, double height) {
        if (base < 0 || height < 0) {
            throw std::invalid_argument("Dimensions cannot be negative");
        }
        return 0.5 * base * height;
    }

    double Geometry::distanceBetweenPoints(double x1, double y1, double x2, double y2) {
        double dx = x2 - x1;
        double dy = y2 - y1;
        return std::sqrt(dx * dx + dy * dy);
    }

} // namespace MathLib