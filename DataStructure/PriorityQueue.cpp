//優先度付きキュー
#include <vector>
template <typename T>
class PriorityQueue
{
private:
    int _size;
    int _tail;
    std::vector<T> _tree;
    
    int parent(int index) {return (index - 1) / 2;}
    int left(int index) {return 2 * index + 1;}
    int right(int index) {return 2 * index + 2;}
    
    void up_heap(int index)
    {
        T value = _tree[index];
        while(index > 0 && _tree[parent(index)] < value)
        {
            _tree[index] = _tree[parent(index)];
            index = parent(index);
        }
        _tree[index] = value;
    }
    void down_heap(int index)
    {
        T value = _tree[index];
        int larger;
        while(true)
        {
            if(left(index) < _tail)
            {
                if(right(index) < _tail && _tree[left(index)] < _tree[right(index)])
                    larger = right(index);
                else
                    larger = left(index);
                
                if(value < _tree[larger])
                {
                    _tree[index] = _tree[larger];
                    index = larger;
                }
                else
                    break;
            }
            else
                break;
        }
        _tree[index] = value;
    }
    
public:
    explicit PriorityQueue(int size = 0) {init(size);}
    void init(int size = 0)
    {
        _size = size;
        _tail = 0;
        _tree.assign(size, T{});
    }
    
    void insert(T value)
    {
        if(_tail == _size)
        {
            _tree.emplace_back(value);
            up_heap(_tail);
            ++_tail, ++_size;
        }
        else
        {
            _tree[_tail] = value;
            up_heap(_tail);
            ++_tail;
        }
    }
    T extract(void)
    {
        T value = _tree[0];
        _tree[0] = _tree[--_tail];
        down_heap(0);
        return value;
    }
    T top(void) {return _tree[0];}
    
    bool empty(void) {return _tail == 0;}
    int size(void) {return _tail;}
};

/*
template <typename T>
class PriorityQueue
{
    //サイズを指定して初期化(不足分は適宜補充される)
    PriorityQueue(int size = 0);
    void init(int size = 0);
    
    //データを挿入
    void insert(T value);
    //最も優先度の高いデータを取り出して返す
    T extract(void);
    //最も優先度の高いデータを返す
    T top(void);
    
    //キューが空ならtrueを返す
    bool empty(void);
    //キューに挿入されているデータの個数を返す
    int size(void);
};
*/

/////

#include <iostream>
using namespace std;
int main(void)
{
    PriorityQueue<int> pq(10);
    
    int input;
    while(true)
    {
        cout << "command?(1:insert / 2:extract / 3:top / 4:size / 9:end program): ";
        do
        {
            cin >> input;
        } while(input != 1 && input != 2 && input != 3 && input != 4 && input != 9);
        
        switch(input)
        {
        case 1:
            cout << "value?(int): ";
            cin >> input;
            pq.insert(input);
            cout << "inserted " << input << "\n\n";
            break;
            
        case 2:
            if(pq.empty())
            {
                cout << "priority queue is empty\n\n";
                break;
            }
            cout << "extracted " << pq.extract() << "\n\n";
            break;
            
        case 3:
            if(pq.empty())
            {
                cout << "priority queue is empty\n\n";
                break;
            }
            cout << "top value is " << pq.top() << "\n\n";
            break;
            
        case 4:
            cout << "size of priority queue is " << pq.size() << "\n\n";
            break;
            
        case 9:
            return 0;
        }
    }
}
