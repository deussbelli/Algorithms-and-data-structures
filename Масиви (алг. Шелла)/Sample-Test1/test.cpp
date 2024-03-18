#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

void shellSort(vector<int>& vec)
{
    int N = vec.size();
    for (int gap = N / 2; gap > 0; gap /= 2) //початкова відстань gap = size div 2 (or gap = gap >> 1) + далі весь час скорочується на 2
    {
        for (int i = gap; i < N; i += 1)
        {
            int vector_elements = vec[i];
            int j;
            for (j = i; j >= gap && vec[j - gap] > vector_elements; j -= gap)
            {
                vec[j] = vec[j - gap];
            }
            vec[j] = vector_elements;
        }
    }
}

void shellSort_1(int arr[], int N)
{
    for (int gap = N / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < N; i += 1)
        {
            int array_elements = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > array_elements; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = array_elements;
        }
    }
}

void bigArrayForSort()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int k = 20000;
    int* arr = new int[k];

    for (int i = 0; i < k; i++)
        arr[i] = rand();

    shellSort_1(arr, k);

    cout << "\nУпорядкований рандомно згенерований масив [Шеллом]: \n"; //вивід ліпше видалити при підрахунку швидкості
    for (int i = 0; i < k; i++)
        cout << arr[i] << " ";

    delete[] arr;

    cout << "\n\n";

    cout << "Витрачений час: " << clock() / 1000.0 << endl << endl;
}

void smallArrayForSort()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int arr[] = { 45,23,53,43,18,24,8,95,101 }, i;
    int N = sizeof(arr) / sizeof(arr[0]);

    cout << "Массив до сортування: \n";
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";

    cout << "\n";

    shellSort_1(arr, N);

    cout << "\nМасив після сортування [Шеллом]: \n";
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";

    cout << "\n\n";

    cout << "Витраченний час: " << clock() / 1000.0 << endl << endl;
}

//////////////////////////////////////////////ТЕСТУВАННЯ////////////////////////////////////////////

//невпорядкований
TEST(ShellSortTest, SortsVectorInAscendingOrder) {
    std::vector<int> vec = { 4, 2, 1, 3, 5 };
    shellSort(vec);
    ASSERT_EQ(vec, std::vector<int>({ 1, 2, 3, 4, 5 }));
}

//впорядкований
TEST(ShellSortTest, SortsSortedVector) {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    shellSort(vec);
    ASSERT_EQ(vec, std::vector<int>({ 1, 2, 3, 4, 5 }));
}

//впорядкований з нулем
TEST(ShellSortTest, SortsVectorWithZero) {
    std::vector<int> vec = { 4, 2, 1, 3, 5, 0 };
    shellSort(vec);
    ASSERT_EQ(vec, std::vector<int>({ 0, 1, 2, 3, 4, 5 }));
}

//з повторенням
TEST(ShellSortTest, SortsVectorWithTheSameNumbers) {
    std::vector<int> vec = { 1, 2, 4, 1, 7, 2, 7, 2, 8, 1 };
    shellSort(vec);
    ASSERT_EQ(vec, std::vector<int>({ 1, 1, 1, 2, 2, 2, 4, 7, 7, 8 }));
}

//навпаки
TEST(ShellSortTest, SortsVectorInReserveOrder) {
    std::vector<int> vec = { 5, 4, 3, 2, 1 };
    shellSort(vec);
    ASSERT_EQ(vec, std::vector<int>({ 1, 2, 3, 4, 5 }));
}

//пустий
TEST(ShellSortTest, SortsEmptyVector) {
    std::vector<int> vec;
    shellSort(vec);
    ASSERT_TRUE(vec.empty());
}


/////////////////////////////////////////ТЕСТУВАННЯ НА ПРАКТИЦІ///////////////////////////////////////
int test() //змінити назву на main
{
    //smallArrayForSort();

    //bigArrayForSort();

    system("pause");
    return 0;
}