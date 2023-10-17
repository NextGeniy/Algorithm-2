#include <iostream>
#include <iomanip>
using namespace std;
const int RUN = 32;
class DynamicArr {
    int* Arr;
public:
    int size{};
    DynamicArr() {
        size = 20;
        Arr = new int[size];
        for (int i = 0; i < size; i++) {
            Arr[i] = rand() % 100;
        }
    }
    DynamicArr(int size) {
        this->size = size;
        Arr = new int[size];
    }
    ~DynamicArr() {
        delete[] Arr; Arr = nullptr;
    }
    void AddElem(int index, int val) {
        int* temp = new int[size + 1];
        memcpy((void*)temp, (const void*)Arr, sizeof(int) * size);

        for (int i = size - 1; i >= index; i--) {
            temp[i + 1] = temp[i];
        }
        temp[index] = val;

        size++;

        if (temp != nullptr)
        {
            Arr = new int[size];
            memcpy((void*)&Arr[0], (const void*)temp, sizeof(int) * size);
        }

        delete[] temp; temp = nullptr;

    }
    void ShowArr() {
        cout << "Динамический массив: \n";
        cout << "Значение: ";
        for (int i = 0; i < size; i++) {
            cout <<setw(4) << Arr[i] << " ";
        }
        cout << "\n";
        cout << setw(10) << "Индекс: ";
        for (int i = 0; i < size; i++) {
            cout << setw(4) << i << " ";
        }
        cout << "\n\n";
    }
    void DeleteElem(int index) {
        int* temp = new int[size - 1];
        for (int i = 0; i < size; i++) {
            if (i != size) {
                if (i < index) {
                    temp[i] = Arr[i];
                }
                else if (i >= index) {
                    temp[i] = Arr[i + 1];
                }
                else {

                }
            }

        }
        size--;
        Arr = new int[size];
        for (int i = 0; i < size; i++) {
            Arr[i] = temp[i];
        }

    }
    void GetIndexArr(int data) {
        for (int i = 0; i < size; i++) {
            if (Arr[i] == data) {
                cout << i << " ";
            }
        }
        cout << "\n";
    }
    void GetDataArr(int index) {
        for (int i = 0; i < size; i++) {
            if (i == index) {
                cout << Arr[i] << " ";
            }
        }
        cout << "\n";
    }
    int GetData(int index) {
        return Arr[index];
    }
    int InputIntArr(int e)
    {
        int N;
        int m = 0, M = 0;
        if (e == 1) {
            M = size;
        }
        else {
            M = (size - 1);
        }
        for (;;) {
            if ((cin >> N).good() && (m <= N) && (N <= M)) return N;
            if (cin.fail()) {
                cin.clear();
                cout << "Неверный ввод, повторите.\n";
                cout << "Введите индекс (c 0)\n";
            }
            else {
                cout << "Число вне допустимого диапазона значений. Повторите ввод.\n";
                cout << "Введите индекс (c 0)\n";
            }
            cin.ignore(100, '\n');
        }
    }
    void SetData(int index,int value) {
        Arr[index] = value;
    }
    void InsertionSort(int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int temp = Arr[i];
            int j = i - 1;
            while (Arr[j] > temp && j >= left) {
                Arr[j + 1] = Arr[j];
                j--;
            }
            Arr[j + 1] = temp;
        }
    }

    void Merge(int l, int m, int r) {
        int len1 = m - l + 1, len2 = r - m;
        int* left = new int[len1], * right = new int[len2];
        for (int i = 0; i < len1; i++) {
            left[i] = Arr[l + i];
        }
        for (int i = 0; i < len2; i++) {
            right[i] = Arr[m + 1 + i];
        }
        int i = 0, j = 0, k = l;
        while (i < len1 && j < len2) {
            if (left[i] <= right[j]) {
                Arr[k] = left[i];
                i++;
            }
            else {
                Arr[k] = right[j];
                j++;
            }
            k++;
        }
        while (i < len1) {
            Arr[k] = left[i];
            k++;
            i++;
        }
        while (j < len2) {
            Arr[k] = right[j];
            k++;
            j++;
        }
        delete[] left;
        delete[] right;
    }

    void TimSort() {
        for (int i = 0; i < size; i += RUN) {
            InsertionSort(i, min((i + 31), (size - 1)));
        }

        for (int sized = RUN; sized < size ; sized = 2 * sized) {
 
            for (int left = 0; left < size; left += 2 * sized) {
                int mid = left + sized - 1;
                int right = min((left + 2 * sized - 1), (size - 1));
                Merge(left, mid, right);
            }
        }
    }
};
class LinckedList;
class Node {
    int Data;
    friend LinckedList;
public:
    Node* Prev, * Next;
    Node(int Data) {
        this->Data = Data;
        this->Prev = this->Next = nullptr;

    }
};
class LinckedList
{
public:
    Node* Head, * Tail;
    LinckedList() {
        Head = Tail = nullptr;
    }
    ~LinckedList() {
        while (Head != nullptr)
            DeleteFirst();
    }
    Node* CreateListRandom() {
        Node* Ptr = 0;
        int Lenght = 20;
        for (int i = 1; i <= Lenght; ++i) {
            int Data = rand() % 100;
            Node* Ptr = new Node(Data);
            Ptr->Next = Head;
            if (Head != nullptr)
                Head->Prev = Ptr;
            if (Tail == nullptr)
                Tail = Ptr;
            Head = Ptr;

        }
        return Ptr;
    }
    Node* GetIndex(int Index) {
        Node* Ptr = Head;
        int Temp = 0;
        while (Temp != Index) {
            if (Ptr == nullptr)
                return nullptr;
            Ptr = Ptr->Next;
            Temp++;
        }
        return Ptr;
    }
    int GetIndexData(int Index) {
        Node* Ptr = Head;
        int Temp = 0;
        while (Temp != Index) {
            if (Ptr == nullptr)
                return NULL;
            Ptr = Ptr->Next;
            Temp++;
        }
        return Ptr->Data;
    }
    Node* AddFirst(int Data) {
        Node* Ptr = new Node(Data);
        Ptr->Prev = Tail;
        if (Tail != nullptr)
            Tail->Next = Ptr;
        if (Head == nullptr)
            Head = Ptr;
        Tail = Ptr;
        return Ptr;
    }
    Node* AddLast(int Data) {
        Node* Ptr = new Node(Data);
        Ptr->Next = Head;
        if (Head != nullptr)
            Head->Prev = Ptr;
        if (Tail == nullptr)
            Tail = Ptr;
        Head = Ptr;
        return Ptr;
    }
    Node* Insertion(int Index, int Data) {
        Node* Right = GetIndex(Index);
        if (Right == nullptr) {
            return AddFirst(Data);
        }
        Node* Left = Right->Prev;
        if (Left == nullptr) {
            return AddLast(Data);
        }
        Node* Ptr = new Node(Data);
        Ptr->Prev = Left;
        Ptr->Next = Right;
        Left->Next = Ptr;
        Right->Prev = Ptr;
        return Ptr;
    }
    void DeleteFirst() {
        if (Head == nullptr)
            return;
        Node* Ptr = Head->Next;
        if (Ptr != nullptr)
            Ptr->Prev = nullptr;
        else
            Tail = nullptr;
        delete Head;
        Head = Ptr;
    }
    void DeleteLast() {
        if (Tail == nullptr)
            return;
        Node* Ptr = Tail->Prev;
        if (Ptr != nullptr)
            Ptr->Next = nullptr;
        else
            Head = nullptr;
        delete Tail;
        Tail = Ptr;
    }
    void Delete(int Index) {
        Node* Ptr = GetIndex(Index);
        if (Ptr == nullptr)
            return;
        if (Ptr->Prev == nullptr) {
            DeleteFirst();
            return;
        }
        if (Ptr->Next == nullptr) {
            DeleteLast();
            return;
        }
        Node* Right = Ptr->Next;
        Node* Left = Ptr->Prev;
        Left->Next = Right;
        Right->Prev = Left;
        delete Ptr;
    }
    int NumObj() {
        Node* Ptr = Head;
        int Temp = 0;
        while (Ptr != nullptr) {
            if (Ptr == nullptr)
                return NULL;
            Ptr = Ptr->Next;
            Temp++;
        }
        return Temp;
    }
    int GetDataIndex(int Data) {
        Node* Ptr = Head;
        for (int Temp = 0; Temp <= NumObj(); ++Temp) {
            if (Ptr->Data == Data)
                return Temp;
            Ptr = Ptr->Next;
        }
        return (-1);
    }
    void Output() {
        cout << "Двусвязный список:\n  ";
        Node* Ptr = Head;
        Node* Ptr2 = Head;
        int temp = 0;
        cout << "Значение: ";
        while (Ptr != nullptr) {
            cout<<setw(4) << Ptr->Data << " ";
            Ptr = Ptr->Next;

        }
        cout << "\n  ";
        cout << setw(10) << "Индекс: ";
        while (Ptr2 != nullptr) {
            cout <<setw(4) << temp << " ";
            Ptr2 = Ptr2->Next;
            temp++;
        }
        cout << "\n\n";
    }
    int InputIntList(int q)
    {
        int N;
        int m = 0;
        int M = 0;
        if (q == 1) {
            M = NumObj();
        }
        else {
            M = (NumObj() - 1);
        }
        for (;;) {
            if ((cin >> N).good() && (m <= N) && (N <= M)) return N;
            if (cin.fail()) {
                cin.clear();
                cout << "Неверный ввод, повторите.\n";
                cout << "Введите индекс (c 0)\n";
            }
            else {
                cout << "Число вне допустимого диапазона значений. Повторите ввод.\n";
                cout << "Введите индекс (c 0)\n";
            }
            cin.ignore(100, '\n');
        }
    }
    void TimSort() {
        DynamicArr TempArr(NumObj());
        Node* Ptr = Head;
        for (int i = 0; i < NumObj(); i++) {
            TempArr.SetData(i, Ptr->Data);
            Ptr = Ptr->Next;
        }
        Ptr = Head;
        TempArr.TimSort();
        for (int i = 0; i < NumObj(); i++) {
            Ptr->Data = TempArr.GetData(i);
            Ptr = Ptr->Next;
        }
    }
};
int InputInt(int M)
{
    int N;
    int m = 1;
    for (;;) {
        if ((cin >> N).good() && (m <= N) && (N <= M)) return N;
        if (cin.fail()) {
            cin.clear();
            cout << "Неверный ввод, повторите.\n";
        }
        else {
            cout << "Число вне допустимого диапазона значений. Повторите ввод.\n";
        }
        cin.ignore(100, '\n');
    }
}
int InputIntData() {

    int N;
    int m = 0, M = 32000;
    for (;;) {
        if ((cin >> N).good() && (m <= N) && (N < M)) return N;
        if (cin.fail()) {
            cin.clear();
            cout << "Неверный ввод, повторите.\n";
            cout << "Введите значение\n";
        }
        else {
            cout << "Число вне допустимого диапазона значений. Повторите ввод.\n";
            cout << "Введите значение\n";
        }
        cin.ignore(100, '\n');
    }
}
int main() {

    setlocale(0, "Rus");
    int i = 1;
    while (i != 3) {
        system("CLS");
        cout << "Меню \n";
        cout << "1. Двусвзязный список\n";
        cout << "2. Динамический массив\n";
        cout << "3. Выход\n";
        i = InputInt(3);
        switch (i) {
        case 1: {
            system("CLS");
            int q = 1;
            LinckedList MainList;
            MainList.CreateListRandom();
            while (q != 6) {
                system("CLS");
                MainList.Output();
                cout << "1.Вставка в список \n";
                cout << "2.Получение значения по индексу \n";
                cout << "3.Получение индекса по значению \n";
                cout << "4.Удаление элемента \n";
                cout << "5.Сортировка списка алгоритмом TimSort  \n";
                cout << "6.Выход \n";
                q = InputInt(6);
                switch (q) {
                case 1: {
                    int index, data;
                    cout << "Введите индекс (c 0) \n";
                    index = MainList.InputIntList(q);
                    cout << "Введите значение \n";
                    data = InputIntData();
                    MainList.Insertion(index, data);
                    break;
                }
                case 2: {
                    int index;
                    cout << "Введите индекс (c 0)\n";
                    index = MainList.InputIntList(q);
                    cout << "Значение под заданным индексом\n";
                    cout << MainList.GetIndexData(index) << "\n";
                    system("pause");
                    break;
                }
                case 3: {
                    int data;
                    cout << "Введите значение элемента \n";
                    data = InputIntData();
                    cout << "Индекс значения в списке \n";
                    cout << MainList.GetDataIndex(data) << "\n";
                    system("pause");
                    break;
                }
                case 4: {
                    int index;
                    cout << "Введите индекс \n";
                    index = MainList.InputIntList(q);
                    cout << "Список с удаленным элементом\n";
                    MainList.Delete(index);
                    break;
                }
                case 5: {
                    // << "Список отсортирован\n";
                    MainList.TimSort();
                    break;
                }
                case 6: {
                    break;
                }
                }
            }
            break;
        }
        case 2: {
            system("CLS");
            int e = 1;
            DynamicArr MainArr;
            while (e != 6) {
                system("CLS");
                MainArr.ShowArr();
                cout << "1.Вставка в массив \n";
                cout << "2.Получение значения по индексу \n";
                cout << "3.Получение индекса по значению \n";
                cout << "4.Удаление элемента \n";
                cout << "5.Сортировка массива алгоритмом TimSort \n";
                cout << "6.Выход \n";
                e = InputInt(6);
                switch (e) {
                case 1: {
                    int index, data;
                    cout << "Введите индекс (c 0)\n";
                    index = MainArr.InputIntArr(e);
                    cout << "Введите значение \n";
                    data = InputIntData();
                    MainArr.AddElem(index, data);
                    MainArr.ShowArr();
                    break;
                }
                case 2: {
                    int index;
                    cout << "Введите индекс (c 0)\n";
                    index = MainArr.InputIntArr(e);
                    cout << "Значение под заданным индексом\n";
                    MainArr.GetDataArr(index);
                    system("pause");
                    break;
                }
                case 3: {
                    int data;
                    cout << "Введите значение элемента \n";
                    data = InputIntData();
                    cout << "Индекс значения в списке \n";
                    MainArr.GetIndexArr(data);
                    system("pause");
                    break;
                }
                case 4: {
                    int index;
                    cout << "Введите индекс (c 0)\n";
                    index = MainArr.InputIntArr(e);
                    cout << "Список с удаленным элементом\n";
                    MainArr.DeleteElem(index);
                    break;
                }
                case 5: {
                    MainArr.TimSort();
                    break;
                }
                case 6: {
                    break;
                }
                }
            }
            break;
        
        }
        case 3: {
            return 0;
        }
        }
    }

}
