#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <map>
#include <stack>
#include <queue>

using namespace std;
using namespace chrono;

// ==================== О-НОТАЦИЯ: ПРИМЕРЫ РАЗНОЙ СЛОЖНОСТИ ====================

class ComplexityExamples {
public:
    // O(1) - Константная сложность
    static int constantTime(int n) {
        return n * n;  // Одна операция
    }

    // O(log n) - Логарифмическая сложность
    static int logarithmicTime(int n) {
        int count = 0;
        while (n > 0) {
            n /= 2;  // Делим пополам на каждом шаге
            count++;
        }
        return count;
    }

    // O(n) - Линейная сложность
    static int linearTime(int n) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += i;  // n операций
        }
        return sum;
    }

    // O(n log n) - Линейно-логарифмическая сложность
    static void linearithmicTime(vector<int>& arr) {
        // Пример: сортировка слиянием или быстрая сортировка
        sort(arr.begin(), arr.end());  // O(n log n)
    }

    // O(n?) - Квадратичная сложность
    static int quadraticTime(int n) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                sum += i * j;  // n * n операций
            }
        }
        return sum;
    }

    // O(2^n) - Экспоненциальная сложность
    static int exponentialTime(int n) {
        if (n <= 1) return 1;
        return exponentialTime(n - 1) + exponentialTime(n - 2);  // Фибоначчи
    }

    // O(n!) - Факториальная сложность
    static int factorialTime(int n) {
        if (n <= 1) return 1;
        int count = 0;
        for (int i = 0; i < n; i++) {
            count += factorialTime(n - 1);  // Очень медленно!
        }
        return count;
    }
};

// ==================== ИЗМЕРЕНИЕ ВРЕМЕНИ ВЫПОЛНЕНИЯ ====================

template<typename Func>
void measureTime(const string& name, Func func, int n) {
    auto start = high_resolution_clock::now();
    func(n);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << name << " (n=" << n << "): "
        << duration.count() << " микросекунд" << endl;
}

void demonstrateComplexity() {
    cout << "=== ДЕМОНСТРАЦИЯ О-НОТАЦИИ ===" << endl;

    vector<int> testSizes = { 10, 100, 1000, 10000 };

    for (int n : testSizes) {
        cout << "\n--- n = " << n << " ---" << endl;

        // O(1)
        measureTime("O(1) - Константная", [](int n) {
            ComplexityExamples::constantTime(n);
            }, n);

        // O(log n)
        if (n <= 1000000) {
            measureTime("O(log n) - Логарифмическая", [](int n) {
                ComplexityExamples::logarithmicTime(n);
                }, n);
        }

        // O(n)
        measureTime("O(n) - Линейная", [](int n) {
            ComplexityExamples::linearTime(n);
            }, n);

        // O(n log n) - сортировка
        if (n <= 10000) {
            vector<int> arr(n);
            generate(arr.begin(), arr.end(), rand);

            auto start = high_resolution_clock::now();
            ComplexityExamples::linearithmicTime(arr);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            cout << "O(n log n) - Сортировка: " << duration.count() << " микросекунд" << endl;
        }

        // O(n?)
        if (n <= 1000) {
            measureTime("O(n?) - Квадратичная", [](int n) {
                ComplexityExamples::quadraticTime(n);
                }, n);
        }

        // O(2^n) - только для маленьких n
        if (n <= 30) {
            measureTime("O(2^n) - Экспоненциальная", [](int n) {
                ComplexityExamples::exponentialTime(n);
                }, n);
        }

        // O(n!) - только для очень маленьких n
        if (n <= 10) {
            measureTime("O(n!) - Факториальная", [](int n) {
                ComplexityExamples::factorialTime(n);
                }, n);
        }
    }
}

// ==================== КЛАССЫ СЛОЖНОСТИ ====================

class ComplexityClasses {
public:
    // Класс P: Полиномиальные задачи

    // Линейный поиск - O(n)
    static int linearSearch(const vector<int>& arr, int target) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == target) return i;
        }
        return -1;
    }

    // Сортировка пузырьком - O(n?)
    static void bubbleSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // Быстрая сортировка - O(n log n) в среднем
    static void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    // Задача о сумме подмножества (NP-полная)
    // Проверка, существует ли подмножество с суммой target
    static bool subsetSum(const vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

        // Базовый случай: сумма 0 всегда достижима
        for (int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }

        // Заполнение таблицы динамического программирования
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= target; j++) {
                if (j < nums[i - 1]) {
                    dp[i][j] = dp[i - 1][j];
                }
                else {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
                }
            }
        }

        return dp[n][target];
    }

    // Задача коммивояжера (TSP) - NP-трудная
    static int travelingSalesman(const vector<vector<int>>& graph, int n) {
        // Минимальный путь через все города (полный перебор)
        vector<int> cities(n);
        for (int i = 0; i < n; i++) cities[i] = i;

        int minPath = INT_MAX;

        do {
            int currentPath = 0;

            // Вычисляем длину пути для текущей перестановки
            for (int i = 0; i < n - 1; i++) {
                int from = cities[i];
                int to = cities[i + 1];
                currentPath += graph[from][to];
            }

            // Возвращаемся в начальный город
            currentPath += graph[cities[n - 1]][cities[0]];

            minPath = min(minPath, currentPath);

        } while (next_permutation(cities.begin() + 1, cities.end()));

        return minPath;
    }
};

// ==================== РЕКУРСИВНЫЕ АЛГОРИТМЫ ====================

class RecursiveAlgorithms {
private:
    static map<int, long long> fibCache;  // Кэш для чисел Фибоначчи

public:
    // 1. Факториал - O(n)
    static long long factorial(int n) {
        // Базовый случай
        if (n <= 1) return 1;

        // Рекурсивный случай
        return n * factorial(n - 1);
    }

    // 2. Числа Фибоначчи
    // Наивная рекурсия - O(2^n)
    static long long fibonacciNaive(int n) {
        if (n <= 1) return n;
        return fibonacciNaive(n - 1) + fibonacciNaive(n - 2);
    }

    // С мемоизацией (кэшированием) - O(n)
    static long long fibonacciMemoization(int n) {
        if (n <= 1) return n;

        // Проверяем, есть ли значение в кэше
        if (fibCache.find(n) != fibCache.end()) {
            return fibCache[n];
        }

        // Вычисляем и сохраняем в кэш
        long long result = fibonacciMemoization(n - 1) + fibonacciMemoization(n - 2);
        fibCache[n] = result;

        return result;
    }

    // Итеративная версия - O(n)
    static long long fibonacciIterative(int n) {
        if (n <= 1) return n;

        long long a = 0, b = 1;
        for (int i = 2; i <= n; i++) {
            long long temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    }

    // 3. Бинарный поиск - O(log n)
    static int binarySearch(const vector<int>& arr, int target, int left, int right) {
        // Базовый случай: элемент не найден
        if (left > right) return -1;

        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;  // Элемент найден
        }
        else if (arr[mid] > target) {
            // Ищем в левой половине
            return binarySearch(arr, target, left, mid - 1);
        }
        else {
            // Ищем в правой половине
            return binarySearch(arr, target, mid + 1, right);
        }
    }

    // 4. Ханойские башни - O(2^n)
    static void towerOfHanoi(int n, char fromRod, char toRod, char auxRod) {
        if (n == 1) {
            cout << "Переместить диск 1 с " << fromRod << " на " << toRod << endl;
            return;
        }

        towerOfHanoi(n - 1, fromRod, auxRod, toRod);
        cout << "Переместить диск " << n << " с " << fromRod << " на " << toRod << endl;
        towerOfHanoi(n - 1, auxRod, toRod, fromRod);
    }

    // 5. Наибольший общий делитель (НОД) - O(log min(a, b))
    static int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    // 6. Степень числа - O(log n)
    static double power(double x, int n) {
        if (n == 0) return 1;
        if (n == 1) return x;

        double half = power(x, n / 2);

        if (n % 2 == 0) {
            return half * half;
        }
        else if (n > 0) {
            return x * half * half;
        }
        else {
            return (half * half) / x;
        }
    }

    // 7. Генерация всех перестановок - O(n!)
    static void generatePermutations(vector<int>& arr, int start, vector<vector<int>>& result) {
        if (start == arr.size() - 1) {
            result.push_back(arr);
            return;
        }

        for (int i = start; i < arr.size(); i++) {
            swap(arr[start], arr[i]);
            generatePermutations(arr, start + 1, result);
            swap(arr[start], arr[i]);  // Backtrack
        }
    }

    // 8. Обход дерева в глубину (DFS)
    struct TreeNode {
        int value;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    static void dfs(TreeNode* node) {
        if (node == nullptr) return;

        // Прямой обход (pre-order)
        cout << node->value << " ";
        dfs(node->left);
        dfs(node->right);
    }

    // 9. Обход дерева в ширину (BFS) - итеративный
    static void bfs(TreeNode* root) {
        if (root == nullptr) return;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            cout << current->value << " ";

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

    // 10. Сортировка слиянием - O(n log n)
    static void mergeSort(vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);

            merge(arr, left, mid, right);
        }
    }

    static void merge(vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<int> leftArr(n1), rightArr(n2);

        for (int i = 0; i < n1; i++)
            leftArr[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            rightArr[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            }
            else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
};

// Инициализация статического члена
map<int, long long> RecursiveAlgorithms::fibCache;

// ==================== АНАЛИЗ СЛОЖНОСТИ РЕКУРСИИ ====================

class RecursionAnalysis {
public:
    // Анализ рекуррентных соотношений

    // Пример 1: T(n) = T(n-1) + O(1) ? O(n)
    // Факториал
    static void linearRecurrence(int n) {
        if (n <= 0) return;
        cout << n << " ";
        linearRecurrence(n - 1);
    }

    // Пример 2: T(n) = T(n/2) + O(1) ? O(log n)
    // Бинарный поиск
    static int logarithmicRecurrence(int n, int target) {
        if (n == 0) return -1;

        int mid = n / 2;
        if (mid == target) return mid;

        if (target < mid) {
            return logarithmicRecurrence(mid, target);
        }
        else {
            int result = logarithmicRecurrence(n - mid - 1, target - mid - 1);
            return result == -1 ? -1 : mid + 1 + result;
        }
    }

    // Пример 3: T(n) = 2T(n/2) + O(n) ? O(n log n)
    // Сортировка слиянием
    static void nLogNRecurrence(vector<int>& arr, int l, int r) {
        if (l >= r) return;

        int mid = l + (r - l) / 2;
        nLogNRecurrence(arr, l, mid);
        nLogNRecurrence(arr, mid + 1, r);

        // O(n) операция слияния
        vector<int> temp(r - l + 1);
        int i = l, j = mid + 1, k = 0;

        while (i <= mid && j <= r) {
            if (arr[i] <= arr[j]) temp[k++] = arr[i++];
            else temp[k++] = arr[j++];
        }

        while (i <= mid) temp[k++] = arr[i++];
        while (j <= r) temp[k++] = arr[j++];

        for (int idx = 0; idx < k; idx++) {
            arr[l + idx] = temp[idx];
        }
    }

    // Пример 4: T(n) = 2T(n-1) + O(1) ? O(2^n)
    // Все подмножества
    static void exponentialRecurrence(vector<int>& nums, int index, vector<int>& current) {
        if (index == nums.size()) {
            cout << "{ ";
            for (int num : current) cout << num << " ";
            cout << "}" << endl;
            return;
        }

        // Не включаем текущий элемент
        exponentialRecurrence(nums, index + 1, current);

        // Включаем текущий элемент
        current.push_back(nums[index]);
        exponentialRecurrence(nums, index + 1, current);
        current.pop_back();
    }

    // Метод подстановки для анализа рекурсии
    static void analyzeRecurrence() {
        cout << "\n=== АНАЛИЗ РЕКУРРЕНТНЫХ СООТНОШЕНИЙ ===" << endl;

        cout << "\n1. T(n) = T(n-1) + O(1)" << endl;
        cout << "   Решение: T(n) = O(n) (Арифметическая прогрессия)" << endl;

        cout << "\n2. T(n) = T(n/2) + O(1)" << endl;
        cout << "   Решение: T(n) = O(log n) (Геометрическая прогрессия)" << endl;

        cout << "\n3. T(n) = 2T(n/2) + O(n)" << endl;
        cout << "   Решение: T(n) = O(n log n) (Теорема о рекуррентных соотношениях)" << endl;

        cout << "\n4. T(n) = 2T(n-1) + O(1)" << endl;
        cout << "   Решение: T(n) = O(2^n) (Экспоненциальный рост)" << endl;

        cout << "\n5. T(n) = T(n-1) + T(n-2) + O(1)" << endl;
        cout << "   Решение: T(n) = O(?^n), где ? = (1+?5)/2 ? 1.618" << endl;
    }
};

// ==================== ПРАКТИЧЕСКИЕ ПРИМЕРЫ ====================

class PracticalExamples {
public:
    // 1. Поиск пути в лабиринте (DFS)
    static bool mazeSolver(vector<vector<int>>& maze, int x, int y, int targetX, int targetY) {
        int rows = maze.size();
        int cols = maze[0].size();

        // Базовые случаи
        if (x < 0 || x >= rows || y < 0 || y >= cols) return false;
        if (maze[x][y] == 0) return false;  // Стена
        if (maze[x][y] == 2) return false;  // Уже посещали
        if (x == targetX && y == targetY) return true;  // Нашли выход

        // Помечаем как посещенную
        maze[x][y] = 2;

        // Рекурсивно ищем в 4 направлениях
        if (mazeSolver(maze, x + 1, y, targetX, targetY)) return true;
        if (mazeSolver(maze, x - 1, y, targetX, targetY)) return true;
        if (mazeSolver(maze, x, y + 1, targetX, targetY)) return true;
        if (mazeSolver(maze, x, y - 1, targetX, targetY)) return true;

        // Backtrack
        maze[x][y] = 1;
        return false;
    }

    // 2. Задача о рюкзаке (0/1 Knapsack)
    static int knapsack(const vector<int>& weights, const vector<int>& values, int capacity, int n) {
        // Базовые случаи
        if (n == 0 || capacity == 0) return 0;

        // Если вес текущего предмета больше вместимости, пропускаем его
        if (weights[n - 1] > capacity) {
            return knapsack(weights, values, capacity, n - 1);
        }
        else {
            // Возвращаем максимум из двух случаев:
            // 1. Не берем текущий предмет
            // 2. Берем текущий предмет
            int withoutItem = knapsack(weights, values, capacity, n - 1);
            int withItem = values[n - 1] + knapsack(weights, values, capacity - weights[n - 1], n - 1);
            return max(withoutItem, withItem);
        }
    }

    // 3. Размен монет (Coin Change)
    static int coinChange(const vector<int>& coins, int amount) {
        if (amount == 0) return 0;
        if (amount < 0) return -1;

        int minCoins = INT_MAX;

        for (int coin : coins) {
            int subProblem = coinChange(coins, amount - coin);
            if (subProblem != -1) {
                minCoins = min(minCoins, subProblem + 1);
            }
        }

        return minCoins == INT_MAX ? -1 : minCoins;
    }

    // 4. Числа Каталана
    static int catalanNumber(int n) {
        if (n <= 1) return 1;

        int result = 0;
        for (int i = 0; i < n; i++) {
            result += catalanNumber(i) * catalanNumber(n - i - 1);
        }
        return result;
    }

    // 5. Поиск всех комбинаций скобок
    static void generateParentheses(int n, int open, int close, string current) {
        if (current.length() == n * 2) {
            cout << current << endl;
            return;
        }

        if (open < n) {
            generateParentheses(n, open + 1, close, current + "(");
        }

        if (close < open) {
            generateParentheses(n, open, close + 1, current + ")");
        }
    }
};

// ==================== ГЛАВНАЯ ФУНКЦИЯ ====================

int main() {
    cout << "АЛГОРИТМЫ И СЛОЖНОСТЬ В C++" << endl;
    cout << "==========================\n" << endl;

    // Демонстрация О-нотации
    demonstrateComplexity();

    // Демонстрация рекурсивных алгоритмов
    cout << "\n\n=== РЕКУРСИВНЫЕ АЛГОРИТМЫ ===" << endl;

    // 1. Факториал
    cout << "\n1. ФАКТОРИАЛ (O(n)):" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << i << "! = " << RecursiveAlgorithms::factorial(i) << endl;
    }

    // 2. Числа Фибоначчи
    cout << "\n2. ЧИСЛА ФИБОНАЧЧИ:" << endl;
    cout << "Наивная рекурсия (O(2^n)):" << endl;
    for (int i = 0; i <= 10; i++) {
        cout << "fib(" << i << ") = " << RecursiveAlgorithms::fibonacciNaive(i) << endl;
    }

    cout << "\nС мемоизацией (O(n)):" << endl;
    for (int i = 0; i <= 20; i++) {
        cout << "fib(" << i << ") = " << RecursiveAlgorithms::fibonacciMemoization(i) << endl;
    }

    // 3. Бинарный поиск
    cout << "\n3. БИНАРНЫЙ ПОИСК (O(log n)):" << endl;
    vector<int> sortedArr = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
    int target = 13;
    int index = RecursiveAlgorithms::binarySearch(sortedArr, target, 0, sortedArr.size() - 1);
    cout << "Ищем " << target << " в массиве: ";
    for (int num : sortedArr) cout << num << " ";
    cout << "\nНайден на позиции: " << index << endl;

    // 4. Ханойские башни
    cout << "\n4. ХАНОЙСКИЕ БАШНИ (O(2^n)):" << endl;
    int disks = 3;
    cout << "Решение для " << disks << " дисков:" << endl;
    RecursiveAlgorithms::towerOfHanoi(disks, 'A', 'C', 'B');

    // 5. Сортировка слиянием
    cout << "\n5. СОРТИРОВКА СЛИЯНИЕМ (O(n log n)):" << endl;
    vector<int> arr = { 38, 27, 43, 3, 9, 82, 10 };
    cout << "Исходный массив: ";
    for (int num : arr) cout << num << " ";

    RecursiveAlgorithms::mergeSort(arr, 0, arr.size() - 1);

    cout << "\nОтсортированный массив: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    // 6. НОД
    cout << "\n6. НАИБОЛЬШИЙ ОБЩИЙ ДЕЛИТЕЛЬ (O(log min(a,b))):" << endl;
    int a = 56, b = 98;
    cout << "НОД(" << a << ", " << b << ") = " << RecursiveAlgorithms::gcd(a, b) << endl;

    // 7. Практические примеры
    cout << "\n\n=== ПРАКТИЧЕСКИЕ ПРИМЕРЫ ===" << endl;

    // Задача о рюкзаке
    vector<int> weights = { 1, 2, 3 };
    vector<int> values = { 10, 15, 40 };
    int capacity = 6;
    int maxValue = PracticalExamples::knapsack(weights, values, capacity, weights.size());
    cout << "\nЗАДАЧА О РЮКЗАКЕ:" << endl;
    cout << "Максимальная ценность при вместимости " << capacity << ": " << maxValue << endl;

    // Размен монет
    vector<int> coins = { 1, 2, 5 };
    int amount = 11;
    int minCoins = PracticalExamples::coinChange(coins, amount);
    cout << "\nРАЗМЕН МОНЕТ:" << endl;
    cout << "Минимальное количество монет для суммы " << amount << ": " << minCoins << endl;

    // Числа Каталана
    cout << "\nЧИСЛА КАТАЛАНА:" << endl;
    for (int i = 0; i <= 6; i++) {
        cout << "C" << i << " = " << PracticalExamples::catalanNumber(i) << endl;
    }

    // Генерация скобок
    cout << "\nВСЕ ВАЛИДНЫЕ СКОБКИ ДЛЯ n=3:" << endl;
    PracticalExamples::generateParentheses(3, 0, 0, "");

    // Анализ рекуррентных соотношений
    RecursionAnalysis::analyzeRecurrence();

    // Классы сложности
    cout << "\n\n=== КЛАССЫ СЛОЖНОСТИ ===" << endl;
    cout << "P (Полиномиальные): задачи, решаемые за полиномиальное время" << endl;
    cout << "   Примеры: сортировка, поиск, кратчайший путь" << endl;
    cout << "\nNP (Недетерминированные полиномиальные):" << endl;
    cout << "   Задачи, решение которых можно проверить за полиномиальное время" << endl;
    cout << "   Примеры: задача о сумме подмножества, раскраска графа" << endl;
    cout << "\nNP-полные: самые сложные задачи в NP" << endl;
    cout << "   Пример: задача коммивояжера, задача о выполнимости булевых формул (SAT)" << endl;

    cout << "\n==========================" << endl;
    cout << "Демонстрация завершена!" << endl;

    return 0;
}