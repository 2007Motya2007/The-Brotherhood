#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

class SearchAlgorithms {
public:
    // Линейный поиск - O(n)
    // Возвращает индекс элемента или -1 если не найден
    static int linearSearch(const vector<int>& arr, int target) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == target) {
                return i;  // Найден на позиции i
            }
        }
        return -1;  // Не найден
    }

    // Линейный поиск с улучшениями
    static int linearSearchOptimized(const vector<int>& arr, int target) {
        // 1. Проверка на пустой массив
        if (arr.empty()) return -1;

        // 2. Добавляем барьерный элемент в конец
        vector<int> temp = arr;
        temp.push_back(target);

        int i = 0;
        while (temp[i] != target) {
            i++;
        }

        // Если дошли до последнего элемента (барьерного)
        return (i == temp.size() - 1) ? -1 : i;
    }

    // Линейный поиск с возможностью нескольких вхождений
    static vector<int> linearSearchAll(const vector<int>& arr, int target) {
        vector<int> indices;

        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == target) {
                indices.push_back(i);
            }
        }

        return indices;
    }

    // Рекурсивный линейный поиск
    static int linearSearchRecursive(const vector<int>& arr, int target, int index = 0) {
        // Базовые случаи
        if (index >= arr.size()) return -1;  // Не нашли
        if (arr[index] == target) return index;  // Нашли

        // Рекурсивный вызов
        return linearSearchRecursive(arr, target, index + 1);
    }
};

// ==================== БИНАРНЫЙ ПОИСК ====================

class BinarySearchAlgorithms {
public:
    // Итеративный бинарный поиск - O(log n)
    // Работает только на отсортированном массиве
    static int binarySearchIterative(const vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;  // Предотвращает переполнение

            if (arr[mid] == target) {
                return mid;  // Найден
            }
            else if (arr[mid] < target) {
                left = mid + 1;  // Ищем в правой половине
            }
            else {
                right = mid - 1;  // Ищем в левой половине
            }
        }

        return -1;  // Не найден
    }

    // Рекурсивный бинарный поиск
    static int binarySearchRecursive(const vector<int>& arr, int target, int left, int right) {
        // Базовый случай
        if (left > right) return -1;

        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            return binarySearchRecursive(arr, target, mid + 1, right);
        }
        else {
            return binarySearchRecursive(arr, target, left, mid - 1);
        }
    }

    // Бинарный поиск первого вхождения (нижняя граница)
    static int binarySearchFirstOccurrence(const vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
        int result = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target) {
                result = mid;  // Запоминаем позицию
                right = mid - 1;  // Ищем дальше слева
            }
            else if (arr[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return result;
    }

    // Бинарный поиск последнего вхождения (верхняя граница)
    static int binarySearchLastOccurrence(const vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
        int result = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target) {
                result = mid;  // Запоминаем позицию
                left = mid + 1;  // Ищем дальше справа
            }
            else if (arr[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return result;
    }

    // Бинарный поиск в повернутом отсортированном массиве
    static int binarySearchRotated(const vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target) return mid;

            // Левая половина отсортирована
            if (arr[left] <= arr[mid]) {
                if (target >= arr[left] && target < arr[mid]) {
                    right = mid - 1;  // Ищем в левой половине
                }
                else {
                    left = mid + 1;  // Ищем в правой половине
                }
            }
            // Правая половина отсортирована
            else {
                if (target > arr[mid] && target <= arr[right]) {
                    left = mid + 1;  // Ищем в правой половине
                }
                else {
                    right = mid - 1;  // Ищем в левой половине
                }
            }
        }

        return -1;
    }

    // Поиск вставки (где должен находиться элемент)
    static int binarySearchInsertPosition(const vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target) {
                return mid;
            }
            else if (arr[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return left;  // Позиция для вставки
    }
};class BubbleSort {
public:
    // Стандартная пузырьковая сортировка - O(n?)
    static void bubbleSort(vector<int>& arr) {
        int n = arr.size();

        for (int i = 0; i < n - 1; i++) {
            // Проходим по массиву, сравнивая соседние элементы
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    // Меняем местами, если текущий больше следующего
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // Оптимизированная версия (с флагом)
    static void bubbleSortOptimized(vector<int>& arr) {
        int n = arr.size();
        bool swapped;

        for (int i = 0; i < n - 1; i++) {
            swapped = false;

            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }

            // Если за весь проход не было обменов, массив отсортирован
            if (!swapped) break;
        }
    }

    // Двунаправленная пузырьковая сортировка (шейкерная сортировка)
    static void cocktailShakerSort(vector<int>& arr) {
        bool swapped = true;
        int start = 0;
        int end = arr.size() - 1;

        while (swapped) {
            swapped = false;

            // Проход слева направо
            for (int i = start; i < end; i++) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }

            if (!swapped) break;

            swapped = false;
            end--;  // Уменьшаем правую границу

            // Проход справа налево
            for (int i = end - 1; i >= start; i--) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }

            start++;  // Увеличиваем левую границу
        }
    }

    // Рекурсивная пузырьковая сортировка
    static void bubbleSortRecursive(vector<int>& arr, int n = -1) {
        if (n == -1) n = arr.size();

        // Базовый случай
        if (n == 1) return;

        // Один проход пузырька
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
            }
        }

        // Рекурсивный вызов для оставшихся элементов
        bubbleSortRecursive(arr, n - 1);
    }

    // Визуализация сортировки
    static void bubbleSortWithVisualization(vector<int>& arr) {
        int n = arr.size();

        cout << "Начальный массив: ";
        printArray(arr);
        cout << endl;

        for (int i = 0; i < n - 1; i++) {
            cout << "Проход " << (i + 1) << ":" << endl;

            for (int j = 0; j < n - i - 1; j++) {
                cout << "  Сравниваем arr[" << j << "]=" << arr[j]
                    << " и arr[" << (j + 1) << "]=" << arr[j + 1];

                if (arr[j] > arr[j + 1]) {
                    cout << " -> меняем местами" << endl;
                    swap(arr[j], arr[j + 1]);
                }
                else {
                    cout << " -> не меняем" << endl;
                }
            }

            cout << "После прохода " << (i + 1) << ": ";
            printArray(arr);
            cout << endl;
        }
    }

    static void printArray(const vector<int>& arr) {
        for (int num : arr) {
            cout << num << " ";
        }
    }
};class MergeSort {
private:
    // Вспомогательная функция для слияния двух отсортированных массивов
    static void merge(vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        // Создаем временные массивы
        vector<int> leftArr(n1);
        vector<int> rightArr(n2);

        // Копируем данные во временные массивы
        for (int i = 0; i < n1; i++) {
            leftArr[i] = arr[left + i];
        }
        for (int j = 0; j < n2; j++) {
            rightArr[j] = arr[mid + 1 + j];
        }

        // Слияние временных массивов обратно в arr
        int i = 0;      // Индекс первого подмассива
        int j = 0;      // Индекс второго подмассива
        int k = left;   // Индекс основного массива

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

        // Копируем оставшиеся элементы leftArr, если есть
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }

        // Копируем оставшиеся элементы rightArr, если есть
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }

public:
    // Основная рекурсивная функция сортировки слиянием - O(n log n)
    static void mergeSort(vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            // Сортируем левую и правую половины
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);

            // Сливаем отсортированные половины
            merge(arr, left, mid, right);
        }
    }

    // Итеративная версия сортировки слиянием
    static void mergeSortIterative(vector<int>& arr) {
        int n = arr.size();

        // Размер текущего подмассива (1, 2, 4, 8, ...)
        for (int currSize = 1; currSize < n; currSize *= 2) {
            // Выбираем начало подмассивов
            for (int leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
                int mid = min(leftStart + currSize - 1, n - 1);
                int rightEnd = min(leftStart + 2 * currSize - 1, n - 1);

                // Сливаем подмассивы
                merge(arr, leftStart, mid, rightEnd);
            }
        }
    }

    // Слияние с использованием дополнительного массива (более чистая версия)
    static void mergeWithExtraArray(vector<int>& arr, int left, int mid, int right) {
        vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            }
            else {
                temp[k++] = arr[j++];
            }
        }

        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];

        // Копируем обратно в исходный массив
        for (i = left, k = 0; i <= right; i++, k++) {
            arr[i] = temp[k];
        }
    }

    // Сортировка слиянием с подсчетом инверсий
    static long long mergeSortWithInversions(vector<int>& arr, int left, int right) {
        if (left >= right) return 0;

        long long inversions = 0;
        int mid = left + (right - left) / 2;

        inversions += mergeSortWithInversions(arr, left, mid);
        inversions += mergeSortWithInversions(arr, mid + 1, right);

        // Слияние с подсчетом инверсий
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<int> leftArr(n1);
        vector<int> rightArr(n2);

        for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
        for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k++] = leftArr[i++];
            }
            else {
                arr[k++] = rightArr[j++];
                inversions += (n1 - i);  // Все оставшиеся элементы в leftArr больше
            }
        }

        while (i < n1) arr[k++] = leftArr[i++];
        while (j < n2) arr[k++] = rightArr[j++];

        return inversions;
    }

    // Естественное слияние (Natural Merge Sort)
    static void naturalMergeSort(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return;

        vector<int> temp(n);

        while (true) {
            // Находим все возрастающие последовательности
            int start1 = 0;
            bool sorted = true;

            while (start1 < n) {
                // Находим конец первой последовательности
                int end1 = start1;
                while (end1 + 1 < n && arr[end1] <= arr[end1 + 1]) {
                    end1++;
                }

                // Находим конец второй последовательности
                int start2 = end1 + 1;
                if (start2 >= n) {
                    // Если вторая последовательность пуста, копируем первую
                    for (int i = start1; i <= end1; i++) {
                        temp[i] = arr[i];
                    }
                    break;
                }

                int end2 = start2;
                while (end2 + 1 < n && arr[end2] <= arr[end2 + 1]) {
                    end2++;
                }

                // Сливаем две последовательности
                mergeTwoRuns(arr, temp, start1, end1, start2, end2);

                start1 = end2 + 1;
                sorted = false;
            }

            // Проверяем, отсортирован ли массив
            if (sorted) break;

            // Меняем массивы местами
            swap(arr, temp);
        }
    }

private:
    static void mergeTwoRuns(vector<int>& arr, vector<int>& temp,
        int start1, int end1, int start2, int end2) {
        int i = start1, j = start2, k = start1;

        while (i <= end1 && j <= end2) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            }
            else {
                temp[k++] = arr[j++];
            }
        }

        while (i <= end1) temp[k++] = arr[i++];
        while (j <= end2) temp[k++] = arr[j++];
    }
};class QuickSort {
public:
    // Основная функция быстрой сортировки - O(n log n) в среднем, O(n?) в худшем
    static void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            // Разделение массива и получение индекса опорного элемента
            int pi = partition(arr, low, high);

            // Рекурсивная сортировка левой и правой частей
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    // Разделение массива (опорный элемент - последний)
    static int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];  // Опорный элемент
        int i = low - 1;        // Индекс меньшего элемента

        for (int j = low; j <= high - 1; j++) {
            // Если текущий элемент меньше или равен опорному
            if (arr[j] <= pivot) {
                i++;  // Увеличиваем индекс меньшего элемента
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    // Разделение с первым элементом в качестве опорного
    static int partitionFirst(vector<int>& arr, int low, int high) {
        int pivot = arr[low];
        int i = low + 1;
        int j = high;

        while (true) {
            while (i <= j && arr[i] <= pivot) i++;
            while (i <= j && arr[j] >= pivot) j--;

            if (i >= j) break;
            swap(arr[i], arr[j]);
        }

        swap(arr[low], arr[j]);
        return j;
    }

    // Разделение со средним элементом в качестве опорного
    static int partitionMiddle(vector<int>& arr, int low, int high) {
        int mid = low + (high - low) / 2;
        swap(arr[mid], arr[high]);  // Перемещаем средний элемент в конец
        return partition(arr, low, high);
    }

    // Трехчастное разделение (для массивов с повторяющимися элементами)
    static pair<int, int> threeWayPartition(vector<int>& arr, int low, int high) {
        int pivot = arr[low];
        int lt = low;     // arr[low..lt-1] < pivot
        int gt = high;    // arr[gt+1..high] > pivot
        int i = low + 1;  // arr[lt..i-1] == pivot

        while (i <= gt) {
            if (arr[i] < pivot) {
                swap(arr[lt], arr[i]);
                lt++;
                i++;
            }
            else if (arr[i] > pivot) {
                swap(arr[i], arr[gt]);
                gt--;
            }
            else {
                i++;
            }
        }

        return { lt, gt };
    }

    // Быстрая сортировка с трехчастным разделением
    static void quickSortThreeWay(vector<int>& arr, int low, int high) {
        if (low >= high) return;

        auto [lt, gt] = threeWayPartition(arr, low, high);
        quickSortThreeWay(arr, low, lt - 1);
        quickSortThreeWay(arr, gt + 1, high);
    }

    // Итеративная быстрая сортировка (использует стек)
    static void quickSortIterative(vector<int>& arr, int low, int high) {
        stack<pair<int, int>> stk;
        stk.push({ low, high });

        while (!stk.empty()) {
            auto [l, h] = stk.top();
            stk.pop();

            if (l >= h) continue;

            int pi = partition(arr, l, h);

            // Добавляем левую и правую части в стек
            if (pi - 1 > l) {
                stk.push({ l, pi - 1 });
            }
            if (pi + 1 < h) {
                stk.push({ pi + 1, h });
            }
        }
    }

    // Быстрая сортировка с выбором опорного элемента методом медианы трех
    static void quickSortMedianOfThree(vector<int>& arr, int low, int high) {
        if (low < high) {
            // Выбираем медиану из первого, среднего и последнего элементов
            int mid = low + (high - low) / 2;

            // Сортируем три элемента
            if (arr[mid] < arr[low]) swap(arr[mid], arr[low]);
            if (arr[high] < arr[low]) swap(arr[high], arr[low]);
            if (arr[high] < arr[mid]) swap(arr[high], arr[mid]);

            // Опорный элемент теперь в arr[mid]
            swap(arr[mid], arr[high - 1]);  // Помещаем опорный перед последним

            int pi = partitionMedian(arr, low + 1, high - 1);
            quickSortMedianOfThree(arr, low, pi - 1);
            quickSortMedianOfThree(arr, pi + 1, high);
        }
    }

    static int partitionMedian(vector<int>& arr, int low, int high) {
        int pivot = arr[low - 1];  // Опорный элемент хранится в low-1
        int i = low;
        int j = high;

        while (true) {
            while (arr[i] < pivot) i++;
            while (arr[j] > pivot) j--;

            if (i >= j) break;
            swap(arr[i], arr[j]);
            i++;
            j--;
        }

        swap(arr[low - 1], arr[j]);
        return j;
    }

    // Быстрая сортировка с оптимизацией для маленьких массивов
    static void quickSortWithInsertion(vector<int>& arr, int low, int high, int threshold = 10) {
        if (high - low + 1 <= threshold) {
            insertionSort(arr, low, high);
            return;
        }

        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortWithInsertion(arr, low, pi - 1, threshold);
            quickSortWithInsertion(arr, pi + 1, high, threshold);
        }
    }

    static void insertionSort(vector<int>& arr, int low, int high) {
        for (int i = low + 1; i <= high; i++) {
            int key = arr[i];
            int j = i - 1;

            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }

            arr[j + 1] = key;
        }
    }

    // Нахождение k-го наименьшего элемента с использованием быстрой сортировки
    static int quickSelect(vector<int>& arr, int low, int high, int k) {
        if (low == high) return arr[low];

        int pi = partition(arr, low, high);
        int pos = pi - low + 1;  // Позиция опорного элемента в текущем подмассиве

        if (k == pos) {
            return arr[pi];  // Нашли k-й наименьший элемент
        }
        else if (k < pos) {
            return quickSelect(arr, low, pi - 1, k);  // Ищем в левой части
        }
        else {
            return quickSelect(arr, pi + 1, high, k - pos);  // Ищем в правой части
        }
    }
};class AlgorithmComparator {
private:
    // Генерация случайного массива
    static vector<int> generateRandomArray(int size, int minVal = 1, int maxVal = 1000) {
        vector<int> arr(size);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(minVal, maxVal);

        for (int i = 0; i < size; i++) {
            arr[i] = dis(gen);
        }

        return arr;
    }

    // Генерация почти отсортированного массива
    static vector<int> generateAlmostSortedArray(int size, int swaps = 10) {
        vector<int> arr(size);

        for (int i = 0; i < size; i++) {
            arr[i] = i + 1;
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, size - 1);

        for (int i = 0; i < swaps; i++) {
            int idx1 = dis(gen);
            int idx2 = dis(gen);
            swap(arr[idx1], arr[idx2]);
        }

        return arr;
    }

    // Генерация обратно отсортированного массива
    static vector<int> generateReverseSortedArray(int size) {
        vector<int> arr(size);

        for (int i = 0; i < size; i++) {
            arr[i] = size - i;
        }

        return arr;
    }

    // Проверка отсортированности массива
    static bool isSorted(const vector<int>& arr) {
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }

    // Измерение времени выполнения
    template<typename Func>
    static long long measureTime(Func func, vector<int>& arr) {
        auto start = high_resolution_clock::now();
        func(arr);
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count();
    }

public:
    // Сравнение алгоритмов сортировки
    static void compareSortingAlgorithms() {
        cout << "=== СРАВНЕНИЕ АЛГОРИТМОВ СОРТИРОВКИ ===" << endl;

        vector<int> sizes = { 100, 1000, 5000, 10000 };

        for (int size : sizes) {
            cout << "\n--- Размер массива: " << size << " ---" << endl;

            // Генерируем разные типы массивов
            vector<int> randomArr = generateRandomArray(size);
            vector<int> almostSortedArr = generateAlmostSortedArray(size, size / 10);
            vector<int> reverseArr = generateReverseSortedArray(size);

            // Тестируем на случайном массиве
            cout << "\n1. Случайный массив:" << endl;
            testSortingOnArray(randomArr, size);

            // Тестируем на почти отсортированном массиве
            cout << "\n2. Почти отсортированный массив:" << endl;
            testSortingOnArray(almostSortedArr, size);

            // Тестируем на обратно отсортированном массиве
            cout << "\n3. Обратно отсортированный массив:" << endl;
            testSortingOnArray(reverseArr, size);
        }
    }

    static void testSortingOnArray(vector<int> arr, int size) {
        vector<int> arrCopy;

        // Пузырьковая сортировка
        if (size <= 5000) {
            arrCopy = arr;
            long long time = measureTime([](vector<int>& a) {
                BubbleSort::bubbleSortOptimized(a);
                }, arrCopy);
            cout << "  Пузырьковая сортировка: " << time << " мкс, "
                << (isSorted(arrCopy) ? "?" : "?") << endl;
        }

        // Сортировка слиянием
        arrCopy = arr;
        long long time = measureTime([size](vector<int>& a) {
            MergeSort::mergeSort(a, 0, size - 1);
            }, arrCopy);
        cout << "  Сортировка слиянием: " << time << " мкс, "
            << (isSorted(arrCopy) ? "?" : "?") << endl;

        // Быстрая сортировка
        arrCopy = arr;
        time = measureTime([size](vector<int>& a) {
            QuickSort::quickSort(a, 0, size - 1);
            }, arrCopy);
        cout << "  Быстрая сортировка: " << time << " мкс, "
            << (isSorted(arrCopy) ? "?" : "?") << endl;

        // Быстрая сортировка с медианой трех
        arrCopy = arr;
        time = measureTime([size](vector<int>& a) {
            QuickSort::quickSortMedianOfThree(a, 0, size - 1);
            }, arrCopy);
        cout << "  Быстрая сортировка (медиана трех): " << time << " мкс, "
            << (isSorted(arrCopy) ? "?" : "?") << endl;
    }

    // Сравнение алгоритмов поиска
    static void compareSearchAlgorithms() {
        cout << "\n=== СРАВНЕНИЕ АЛГОРИТМОВ ПОИСКА ===" << endl;

        vector<int> sizes = { 1000, 10000, 100000, 1000000 };

        for (int size : sizes) {
            cout << "\n--- Размер массива: " << size << " ---" << endl;

            // Создаем отсортированный массив
            vector<int> arr = generateRandomArray(size);
            sort(arr.begin(), arr.end());

            // Выбираем случайный элемент для поиска
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dis(0, size - 1);
            int target = arr[dis(gen)];

            // Тестируем линейный поиск (на неотсортированной копии)
            vector<int> unsortedArr = generateRandomArray(size);
            long long time = measureTime([&](vector<int>& a) {
                SearchAlgorithms::linearSearch(a, target);
                }, unsortedArr);
            cout << "  Линейный поиск (неотсортированный): " << time << " мкс" << endl;

            // Тестируем бинарный поиск (итеративный)
            time = measureTime([&](vector<int>& a) {
                BinarySearchAlgorithms::binarySearchIterative(a, target);
                }, arr);
            cout << "  Бинарный поиск (итеративный): " << time << " мкс" << endl;

            // Тестируем бинарный поиск (рекурсивный)
            time = measureTime([&](vector<int>& a) {
                BinarySearchAlgorithms::binarySearchRecursive(a, target, 0, size - 1);
                }, arr);
            cout << "  Бинарный поиск (рекурсивный): " << time << " мкс" << endl;
        }
    }

    // Демонстрация работы всех алгоритмов
    static void demonstrateAllAlgorithms() {
        cout << "=== ДЕМОНСТРАЦИЯ ВСЕХ АЛГОРИТМОВ ===" << endl;

        // Создаем тестовый массив
        vector<int> arr = { 64, 34, 25, 12, 22, 11, 90, 88, 75, 50 };
        cout << "\nИсходный массив: ";
        printArray(arr);

        // Линейный поиск
        cout << "\n\n1. ЛИНЕЙНЫЙ ПОИСК:" << endl;
        int target = 22;
        int index = SearchAlgorithms::linearSearch(arr, target);
        cout << "   Ищем " << target << ": ";
        if (index != -1) {
            cout << "найден на позиции " << index << endl;
        }
        else {
            cout << "не найден" << endl;
        }

        // Бинарный поиск (требуется отсортированный массив)
        cout << "\n2. БИНАРНЫЙ ПОИСК:" << endl;
        vector<int> sortedArr = arr;
        sort(sortedArr.begin(), sortedArr.end());
        cout << "   Отсортированный массив: ";
        printArray(sortedArr);

        index = BinarySearchAlgorithms::binarySearchIterative(sortedArr, target);
        cout << "\n   Ищем " << target << ": ";
        if (index != -1) {
            cout << "найден на позиции " << index << endl;
        }
        else {
            cout << "не найден" << endl;
        }

        // Пузырьковая сортировка
        cout << "\n3. ПУЗЫРЬКОВАЯ СОРТИРОВКА:" << endl;
        vector<int> arr1 = arr;
        cout << "   До сортировки: ";
        printArray(arr1);
        BubbleSort::bubbleSortOptimized(arr1);
        cout << "\n   После сортировки: ";
        printArray(arr1);

        // Сортировка слиянием
        cout << "\n\n4. СОРТИРОВКА СЛИЯНИЕМ:" << endl;
        vector<int> arr2 = arr;
        cout << "   До сортировки: ";
        printArray(arr2);
        MergeSort::mergeSort(arr2, 0, arr2.size() - 1);
        cout << "\n   После сортировки: ";
        printArray(arr2);

        // Быстрая сортировка
        cout << "\n\n5. БЫСТРАЯ СОРТИРОВКА:" << endl;
        vector<int> arr3 = arr;
        cout << "   До сортировки: ";
        printArray(arr3);
        QuickSort::quickSort(arr3, 0, arr3.size() - 1);
        cout << "\n   После сортировки: ";
        printArray(arr3);
    }

    static void printArray(const vector<int>& arr) {
        for (int num : arr) {
            cout << num << " ";
        }
    }
};