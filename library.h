#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

/*
    nhung gi toi se co gang lam sau day:
    voi bai dung bang:
    cot la noi chua du lieu co the la kieu du lieu bat ki
    hang la noi chua con tro tro toi cac cot ung voi stt cua hang
    bang la noi chua n cot va m hang. n duoc xac dinh. m co the thay doi trong thoi gian chay
    o la noi giao giua cot va hang
*/


template<typename ValueType> struct Cell
{
public:
        template <typename CellType> friend class Col;
        template <typename CellType> friend class Row;
        ValueType val;
        Cell<ValueType> (ValueType);
        bool operator== (Cell<ValueType> other) {
            return val == other.val;
        }
};
template <typename CellType> class Col;
template <typename CellType> Col<CellType>& operator+(const Col<CellType> &, const Col<CellType> &);

template <typename CellType> class Col
{
    private:
        string name;
        vector<Cell<CellType>> cells;
    public:
        string &Name = name;
        vector<Cell<CellType>> &Cells = cells;

//        using iterator = typename std::vector<CellType>::iterator;
//        using const_iterator = typename std::vector<CellType>::const_iterator;

        Col () = default;
        Col (Col&&) = default ;                    //move
        Col& operator=(Col&&) = default;
        Col (Col const &) = default;               //copy
        Col& operator=(Col const &);
        ~Col() = default;

        template<typename CellTypeTemp> Col(initializer_list<CellTypeTemp>) = delete;
        template<typename CellTypeTemp> Col& operator=(initializer_list<CellTypeTemp>) = delete;

        Col (string);

        Col& operator+= (const Col<CellType>);
        Col& operator-= (const Col<CellType>);
        Col& operator*= (const Col<CellType>);
        Col& operator/= (const Col<CellType>);

        friend Col operator+<>(Col const &, Col<CellType> const &);

        void setName(string);
        void addCell(CellType);
        void addCells(vector<CellType>);
        void rmvCell(const Cell<CellType>);
};

//
//
//template <typename CellType> class Row
//{
//    private:
//        void addCell(vector<Cell<CellType>>);
//    public:
//        vector<Cell<CellType>*> cells; // cell se tro toi cac thanh vien cua mang val cau truc col
//        Row();
//        ~Row();
//        Cell<CellType>& operator[](const int);
//        void addCell(const CellType);
//        void rmvCell(const CellType);
//};

//class Table
//{
//    private:
//
//
//        int colAmount{0};
//        int rowAmount{0};
//    public:
//    //    vector<Col<T>> cols;
//    //    vector<Row<T>> rows;
//    //    Table<T>();
//    //    ~Table<T>();
//    //    Cell<T>& operator()(const int,const int);
//    //    void setCell(T ival); // ham nay se dat gia tri cua mot cell
//    //    Cell<T> getCell(const int);
//    //    void addCol();
//    //    void addRow();
//    //    void rmvCol();
//    //    void rmvRow();
//};
//
int main()
{
    Col<int> a("A");
    cout << a.Name;
//    test.addCell(Cell<int> (1));
//    test.addCell(Cell<int> (13));
//    test.addCell(Cell<int> (15));
//    int i = 1;
//    int j = 13;
//    testcol.addCell(i);
//    testcol.addCell(j);
    a.addCell(1);
    a.addCell(2);
    a.addCell(3);

    Col<int> b("B");
    b.addCells(vector<int> {-1, -2, -3, -5});

    for (auto cell : a.Cells)
    {
        cout << endl << cell.val;
    }

    cout << endl << b.Name;
    for (auto cell : b.Cells)
    {
        cout << endl << cell.val;
    }

    system("pause");

    cout << endl << a.Name;
    a = a + b;
    for (auto cell : a.Cells)
    {
        cout << endl << cell.val;
    }

//    cout << a.Cells[0].val;

//    Cell<int> test(1);
//    test = Cell<int> (1);
//    cout << test.val;
    system("pause");
}


//Cell
template<typename ValueType> Cell<ValueType>::Cell(ValueType ival) : val{ival} {};

// Col
template<typename CellType> Col<CellType>::Col(string iname) : name{iname}, cells{} {};
template<typename CellType> void Col<CellType>::setName(string iname) { Name = iname; };
template<typename CellType> void Col<CellType>::addCell(CellType iCellValue) {
    cells.push_back(Cell<CellType>(iCellValue));
}
template<typename CellType> void Col<CellType>::addCells(vector<CellType> icells){
    for (auto &cell: icells){
        cells.push_back(Cell<CellType> (cell));
    }
}
template<typename CellType> Col<CellType>& Col<CellType>::operator+= (const Col<CellType> otherCol){

    for (int i = 0, j = 0; i != Cells.size(); ++i, ++j){
        Cells[i].val += otherCol.Cells[j].val;
    }
    return *this;
}
template<typename CellType> Col<CellType>& Col<CellType>::operator-= (const Col<CellType> otherCol){

    for (int i = 0, j = 0; i != Cells.size(); ++i, ++j){
        Cells[i].val -= otherCol.Cells[j].val;
    }
    return *this;
}
template<typename CellType> Col<CellType>& Col<CellType>::operator*= (const Col<CellType> otherCol){

    for (int i = 0, j = 0; i != Cells.size(); ++i, ++j){
        Cells[i].val *= otherCol.Cells[j].val;
    }
    return *this;
}
template<typename CellType> Col<CellType>& Col<CellType>::operator/= (const Col<CellType> otherCol){

    for (int i = 0, j = 0; i != Cells.size(); ++i, ++j){
        Cells[i].val /= otherCol.Cells[j].val;
    }
    return *this;
}
template<typename CellType> Col<CellType> operator+(Col<CellType> const &a, Col<CellType> const &b){
    Col<CellType> temp = a;
    temp += b;
    return temp;
}
template<typename CellType> Col<CellType>& Col<CellType>::operator=(Col<CellType> const &a){
    Name = a.name;
    for (int i = 0; i != Cells.size(); ++i){
        Cells[i].val = a.Cells[i].val;
    }
}
//Col& operator=(Col const &);
//template<typename CellType> Col<CellType> & operator-(const Col<CellType> &a, const Col<CellType> &b){
//    Col<CellType> temp = a;
//    temp -= b;
//    return temp;
//}
//template<typename CellType> Col<CellType> & operator*(const Col<CellType> &a, const Col<CellType> &b){
//    Col<CellType> temp = a;
//    temp *= b;
//    return temp;
//}
//template<typename CellType> Col<CellType> & operator/(const Col<CellType> &a, const Col<CellType> &b){
//    Col<CellType> temp = a;
//    temp /= b;
//    return temp;
//}

//Col operator+ (const Col<CellType>);
//
//// Row
//template<typename T> Table::Row<T>::Row() : cells{} {};
//template<typename T> Table::Row<T>::~Row() {
//    cells.~vector();
//}
//template<typename T> Table::Cell<T>& Table::Row<T>::operator[] (const int index){
//    return cells[index];
//}
//template<typename T> void Table::Row<T>::addCell(vector<Cell<T>> icells){
//    for (auto &cell: icells){
//        cells.push_back(cell);
//    }
//}


//Table::Table() {
//    cols.push_back({})
//};
//template<typename T> Table<T>::~Table() {
//    cols.~vector();
//    rows.~vector();
//}
//template<typename T> Cell<T>& operator()(const int rowIndex, const int colIndex){
//    return
//}
