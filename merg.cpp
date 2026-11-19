#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <utility>
#include <clocale>
using namespace std;

void sort_bubble(vector<int>& array) {
    int n = array.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

void sort_selection(vector<int>& array) {
    int n = array.size();

    for (int i = 0; i < n - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }

        swap(array[i], array[min_index]);
    }
}

void sort_insertion(vector<int>& array) {
    int n = array.size();

    for (int i = 1; i < n; i++) {
        int element = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > element) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = element;
    }
}

void sort_gnome(vector<int>& array) {
    int n = array.size();
    int i = 0;

    while (i < n) {
        if (i == 0 || array[i] >= array[i - 1]) {
            i++;
        }
        else {
            swap(array[i], array[i - 1]);
            i--;
        }
    }
}

int partition(vector<int>& array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }

    swap(array[i + 1], array[high]);

    return i + 1;
}

void quickSort(vector<int>& array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

int linear_search_index(const vector<int>& array, int element) {
    for (int i = 0; i < array.size(); i++) {
        if (array[i] == element) {
            return i;
        }
    }

    return -1;
}

int binary_search_index(const vector<int>& array, int element) {
    int left = 0;
    int right = array.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == element) {
            return mid;
        }
        else if (array[mid] < element) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}

pair<int, int> search_min_max(const vector<int>& array) {
    int min_element = array[0];
    int max_element = array[0];

    for (int i = 1; i < array.size(); i++) {
        if (array[i] < min_element) {
            min_element = array[i];
        }

        if (array[i] > max_element) {
            max_element = array[i];
        }
    }

    return { min_element, max_element };
}

pair<int, int> search_min_max_sort(const vector<int>& array) {
    return { array[0], array[array.size() - 1] };
}

vector<int> search_average_min_max(const vector<int>& array, int average) {
    vector<int> indexes;

    for (int i = 0; i < array.size(); i++) {
        if (array[i] == average) {
            indexes.push_back(i);
        }
    }

    return indexes;
}

pair<int, int> less_a_more_b(const vector<int>& array, int a, int b) {
    int less = 0;
    int more = 0;

    for (int i = 0; i < array.size(); i++) {
        if (array[i] < a) {
            less++;
        }

        if (array[i] > b) {
            more++;
        }
    }

    return { less, more };
}

pair<int, int> less_a_more_b_binary(const vector<int>& array, int a, int b) {
    int left = 0;
    int right = array.size() - 1;
    int less = 0;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (array[mid] < a) {
            less = mid + 1;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    left = 0;
    right = array.size() - 1;
    int more = 0;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (array[mid] <= b) {
            left = mid + 1;
        }
        else {
            more = array.size() - mid;
            right = mid - 1;
        }
    }

    return { less, more };
}

void switch_places(vector<int>& array, int first, int second) {
    swap(array[first], array[second]);
}

int delete_kr3(vector<int>& array) {
    int count = 0;

    for (int i = 0; i < array.size(); i++) {
        if (array[i] % 3 == 0) {
            array[i] = 0;
            count++;
        }
    }

    return count;
}

vector<int> random_array(int n = 100) {
    static mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(-99, 99);

    vector<int> array;

    for (int i = 0; i < n; i++) {
        array.push_back(dist(gen));
    }

    return array;
}

void printArray(const vector<int>& array) {
    for (int i = 0; i < array.size(); i++) {
        cout << array[i] << " ";
    }

    cout << endl;
}

double measure_sort_time(
    const vector<int>& array,
    void (*sort_function)(vector<int>&),
    int repetitions
) {
    double total_time = 0;

    for (int i = 0; i < repetitions; i++) {
        vector<int> copy_array = array;

        auto start = chrono::steady_clock::now();

        sort_function(copy_array);

        auto end = chrono::steady_clock::now();

        total_time += chrono::duration_cast<chrono::microseconds>(
            end - start
        ).count();
    }

    return total_time / repetitions;
}

double measure_quick_sort_time(const vector<int>& array, int repetitions) {
    double total_time = 0;

    for (int i = 0; i < repetitions; i++) {
        vector<int> copy_array = array;

        auto start = chrono::steady_clock::now();

        quickSort(copy_array, 0, copy_array.size() - 1);

        auto end = chrono::steady_clock::now();

        total_time += chrono::duration_cast<chrono::microseconds>(
            end - start
        ).count();
    }

    return total_time / repetitions;
}

double measure_min_max_time(const vector<int>& array, int repetitions) {
    double total_time = 0;

    for (int i = 0; i < repetitions; i++) {
        auto start = chrono::steady_clock::now();

        search_min_max(array);

        auto end = chrono::steady_clock::now();

        total_time += chrono::duration_cast<chrono::microseconds>(
            end - start
        ).count();
    }

    return total_time / repetitions;
}

double measure_min_max_sort_time(const vector<int>& array, int repetitions) {
    double total_time = 0;

    for (int i = 0; i < repetitions; i++) {
        auto start = chrono::steady_clock::now();

        search_min_max_sort(array);

        auto end = chrono::steady_clock::now();

        total_time += chrono::duration_cast<chrono::microseconds>(
            end - start
        ).count();
    }

    return total_time / repetitions;
}

double measure_average_time(
    const vector<int>& array,
    int average,
    int repetitions
) {
    double total_time = 0;

    for (int i = 0; i < repetitions; i++) {
        auto start = chrono::steady_clock::now();

        search_average_min_max(array, average);

        auto end = chrono::steady_clock::now();

        total_time += chrono::duration_cast<chrono::microseconds>(
            end - start
        ).count();
    }

    return total_time / repetitions;
}

double measure_search_time(
    const vector<int>& array,
    int element,
    int (*search_function)(const vector<int>&, int),
    int repetitions
) {
    double total_time = 0;

    for (int i = 0; i < repetitions; i++) {
        auto start = chrono::steady_clock::now();

        search_function(array, element);

        auto end = chrono::steady_clock::now();

        total_time += chrono::duration_cast<chrono::microseconds>(
            end - start
        ).count();
    }

    return total_time / repetitions;
}

double measure_count_time(
    const vector<int>& array,
    int a,
    int b,
    pair<int, int> (*count_function)(const vector<int>&, int, int),
    int repetitions
) {
    double total_time = 0;

    for (int i = 0; i < repetitions; i++) {
        auto start = chrono::steady_clock::now();

        count_function(array, a, b);

        auto end = chrono::steady_clock::now();

        total_time += chrono::duration_cast<chrono::microseconds>(
            end - start
        ).count();
    }

    return total_time / repetitions;
}

double measure_exchange_time(
    const vector<int>& array,
    int first,
    int second,
    int repetitions
) {
    vector<int> copy_array = array;

    auto start = chrono::steady_clock::now();

    for (int i = 0; i < repetitions; i++) {
        switch_places(copy_array, first, second);
    }

    auto end = chrono::steady_clock::now();

    double total_time = chrono::duration_cast<chrono::microseconds>(
        end - start
    ).count();

    return total_time / repetitions;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<int> array;
    bool created = false;

    int choice;

    do {
        cout << "\n========== МЕНЮ ==========" << endl;
        cout << "1. Создать случайный массив" << endl;
        cout << "2. Вывести массив" << endl;
        cout << "3. Сравнить время сортировок" << endl;
        cout << "4. Найти минимум и максимум" << endl;
        cout << "5. Найти среднее между минимумом и максимумом" << endl;
        cout << "6. Подсчитать числа меньше a и больше b" << endl;
        cout << "7. Сравнить линейный и бинарный поиск" << endl;
        cout << "8. Обменять два элемента" << endl;
        cout << "9. Заменить числа, кратные трём, на нули" << endl;
        cout << "0. Выход" << endl;

        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Программа завершена." << endl;
        }

        else if (choice == 1) {
            array = random_array(100);
            created = true;

            cout << "Массив создан:" << endl;
            printArray(array);
        }

        else if (choice >= 2 && choice <= 9 && !created) {
            cout << "Сначала создайте массив." << endl;
        }

        else if (choice == 2) {
            printArray(array);
        }

        else if (choice == 3) {
            int repetitions = 100;

            cout << "\nСреднее время сортировок (мкс):" << endl;

            cout << "Пузырьковая: "
                 << measure_sort_time(array, sort_bubble, repetitions) << endl;

            cout << "Выбором: "
                 << measure_sort_time(array, sort_selection, repetitions) << endl;

            cout << "Вставками: "
                 << measure_sort_time(array, sort_insertion, repetitions) << endl;

            cout << "Гномья: "
                 << measure_sort_time(array, sort_gnome, repetitions) << endl;

            cout << "Быстрая: "
                 << measure_quick_sort_time(array, repetitions) << endl;
        }

        else if (choice == 4) {
            vector<int> sorted_array = array;

            quickSort(sorted_array, 0, sorted_array.size() - 1);

            pair<int, int> result = search_min_max(array);
            pair<int, int> result_sort = search_min_max_sort(sorted_array);

            int repetitions = 1000;

            double time1 = measure_min_max_time(array, repetitions);

            double time2 = measure_min_max_sort_time(
                sorted_array, repetitions
            );

            cout << "Минимум: " << result.first << endl;
            cout << "Максимум: " << result.second << endl;

            cout << "Время поиска в исходном массиве: "
                 << time1 << " мкс" << endl;

            cout << "Время поиска в отсортированном массиве: "
                 << time2 << " мкс" << endl;

            if (result == result_sort) {
                cout << "Результаты совпадают." << endl;
            }
            else {
                cout << "Результаты не совпадают!" << endl;
            }
        }

        else if (choice == 5) {
            vector<int> sorted_array = array;

            quickSort(sorted_array, 0, sorted_array.size() - 1);

            pair<int, int> min_max = search_min_max(array);

            int average = round((min_max.first + min_max.second) / 2.0);

            vector<int> indexes = search_average_min_max(array, average);

            cout << "Среднее значение: " << average << endl;

            cout << "Индексы совпадающих элементов: ";

            if (indexes.empty()) {
                cout << "Совпадений нет.";
            }
            else {
                for (int i = 0; i < indexes.size(); i++) {
                    cout << indexes[i] << " ";
                }
            }

            cout << endl;
            cout << "Количество совпадений: " << indexes.size() << endl;

            int repetitions = 1000;

            double time1 = measure_average_time(
                array, average, repetitions
            );

            double time2 = measure_average_time(
                sorted_array, average, repetitions
            );

            cout << "Время поиска в исходном массиве: "
                 << time1 << " мкс" << endl;

            cout << "Время поиска в отсортированном массиве: "
                 << time2 << " мкс" << endl;
        }

        else if (choice == 6) {
            vector<int> sorted_array = array;

            quickSort(sorted_array, 0, sorted_array.size() - 1);

            int a, b;

            cout << "Введите число a: ";
            cin >> a;

            cout << "Введите число b: ";
            cin >> b;

            pair<int, int> result = less_a_more_b(sorted_array, a, b);

            pair<int, int> result_binary =
                less_a_more_b_binary(sorted_array, a, b);

            cout << "Линейный подсчёт:" << endl;
            cout << "Элементов меньше a: " << result.first << endl;
            cout << "Элементов больше b: " << result.second << endl;

            cout << "Бинарный подсчёт:" << endl;
            cout << "Элементов меньше a: " << result_binary.first << endl;
            cout << "Элементов больше b: " << result_binary.second << endl;

            if (result == result_binary) {
                cout << "Результаты совпадают." << endl;
            }
            else {
                cout << "Результаты не совпадают!" << endl;
            }

            int repetitions = 1000;

            double time1 = measure_count_time(
                sorted_array, a, b, less_a_more_b, repetitions
            );

            double time2 = measure_count_time(
                sorted_array, a, b, less_a_more_b_binary, repetitions
            );

            cout << "Время линейного подсчёта: "
                 << time1 << " мкс" << endl;

            cout << "Время бинарного подсчёта: "
                 << time2 << " мкс" << endl;
        }

        else if (choice == 7) {
            vector<int> sorted_array = array;

            quickSort(sorted_array, 0, sorted_array.size() - 1);

            int element;

            cout << "Введите число для поиска: ";
            cin >> element;

            int linear_index = linear_search_index(array, element);

            int binary_index = binary_search_index(sorted_array, element);

            int repetitions = 1000;

            double time1 = measure_search_time(
                array, element, linear_search_index, repetitions
            );

            double time2 = measure_search_time(
                sorted_array, element, binary_search_index, repetitions
            );

            cout << "Линейный поиск: ";

            if (linear_index == -1) {
                cout << "элемент не найден." << endl;
            }
            else {
                cout << "элемент найден, индекс: "
                     << linear_index << endl;
            }

            cout << "Бинарный поиск: ";

            if (binary_index == -1) {
                cout << "элемент не найден." << endl;
            }
            else {
                cout << "элемент найден, индекс: "
                     << binary_index << endl;
            }

            cout << "Время линейного поиска: "
                 << time1 << " мкс" << endl;

            cout << "Время бинарного поиска: "
                 << time2 << " мкс" << endl;
        }

        else if (choice == 8) {
            int first, second;

            cout << "Введите первый индекс: ";
            cin >> first;

            cout << "Введите второй индекс: ";
            cin >> second;

            if (first < 0 || first >= array.size() ||
                second < 0 || second >= array.size()) {

                cout << "Неверные индексы." << endl;
            }
            else {
                int repetitions = 100000;

                double time = measure_exchange_time(
                    array, first, second, repetitions
                );

                cout << "Время одного обмена: "
                     << time << " мкс" << endl;

                switch_places(array, first, second);

                cout << "Массив после обмена:" << endl;
                printArray(array);
            }
        }

        else if (choice == 9) {
            int count = delete_kr3(array);

            cout << "Количество заменённых элементов: "
                 << count << endl;

            cout << "Массив после замены:" << endl;
            printArray(array);
        }

    } while (choice != 0);

    return 0;
}
