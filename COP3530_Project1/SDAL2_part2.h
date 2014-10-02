
/*
 a = 0;
 b = a++;
 c = ++a;
 b = 0;
 c = 2;
 a = 2;
 */

#include <iostream>
using namespace std;

template<class T>
class SDAL
{
private:
    int index;
    int arraySize;
    T **array = new T*[1];                                  //T* array; pints to the head of the array
                                                            // T* array[arraySize] is not points to head.
    bool checkFull()
    {
        if(index == arraySize-1)
            return true;
        else
            return false;
    }
    
    bool needDelete()
    {
        if(arraySize>=100 && (index+1) <= arraySize/2)
            return true;
        else
            return false;
    }
    
    void changeSize()
    {
        if(checkFull())
        {
            cout<<"array is full\n";
            T *tempArray = new T[arraySize];                //create a temparray to store the array value
            for(int i = 0; i < arraySize; i++)
                tempArray[i] = array[0][i];
            delete[] array[0];
            
            arraySize = 1.5*arraySize;
            cout<<"array Size is now "<< arraySize;
            
            array[0] = new T[arraySize];                    //resize the array[];
            for(int i = 0; i < arraySize; i++)              //copy temparray to array;
                array[0][i] = tempArray[i];
            delete[] tempArray;
        }
        else if(needDelete())
        {
            T *tempArray = new T[index+1];
            for(int i = 0; i < index+1; i++)
                tempArray[i] = array[0][i];
            delete[] array[0];
            
            arraySize = arraySize/2;
            
            array[0] = new T[arraySize];
            for(int i = 0; i < index+1; i++)
                array[0][i] = tempArray[i];
            delete[] tempArray;
        }
    }
public:
    
    //***************************************iterator*********************************************
    
    class SDAL_Iter
    {
        private:
            T* here;
        public:
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef SDAL_Iter self_type;
            typedef SDAL_Iter& self_reference;
        
      //  typedef SDAL_Iter():
        SDAL_Iter(const SDAL_Iter& src):here(src.here){}                    //copy constructor
        explicit SDAL_Iter(const pointer start):here(start){}
        
        reference operator*() const{
            return *here;                                           //accee to the data, and return
        }
        
        pointer operator->() const{
            return &(operator*());
        }
        
        self_reference operator++()
        {
            here++;
            return *this;                                           // return SDAL_Iter& = *this
        }
        
        self_type operator++(int){
            self_type temp = *this;
            here++;
            return temp;
        }
        
        self_reference operator=(const SDAL_Iter& src)
        {
            here = src.here;
            return *this;                                           // *this return object data, data can change
        }
        
        bool operator==(const self_type& rhs) const{
            return here == rhs.here;
        }
        
        bool operator!=(const self_type& rhs) const{
            return here!=rhs.here;
        }
        
        
            //explicit SDAL_Iter
    };
    
    //***********************************const iterator*******************************************
    
    class SDAL_Const_Iter
    {
    private:
        T* here;
    public:
        typedef  T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef SDAL_Iter self_type;
        typedef SDAL_Iter& self_reference;
        
        //  typedef SDAL_Iter():
        SDAL_Const_Iter(const SDAL_Const_Iter& src):here(src.here){}
        explicit SDAL_Const_Iter(T* start):here(start){}
        
        reference operator*() const{
            return *here;
        }
        
        pointer operator->() const{
            return &(operator*());
        }
        
        self_reference operator++()
        {
            here++;                                        //because array has constant memory address, so increase by 1
            return *this;
        }
        
        self_type operator++(int){
            self_type temp = here;
            here++;
            return temp;
        }
        
        self_reference operator=(const SDAL_Const_Iter& src)
        {
            here = src.here;
            return *this;                                  // *this return object data, data can change
        }
        
        bool operator==(const self_type& rhs) const{
            return here == rhs.here;
        }
        
        bool operator!=(const self_type& rhs) const{
            return here!=rhs.here;
        }
        
        
        //explicit SDAL_Iter
    };
    
//***********************************public functions***************************************
    
    typedef SDAL_Iter iterator;
    typedef SDAL_Const_Iter const_iterator;
    
    SDAL()
    {
        arraySize = 50;
        array[0] = new T[arraySize];
        index = -1;
    }
    SDAL(int arraySize)
    {
        this->arraySize = arraySize;
        array[0] = new T[arraySize];
        index = -1;
    }
    SDAL(const SDAL& src):index(src.index),arraySize(src.arraySize),array(src.array){}
    
    void replace(T element, int position);
    void insert( T element, int position);
    void push_back(T element);
    void push_front(T element);
    T remove(int position);
    T pop_back();
    T pop_front();
    T item_at(int position);
    bool is_empty();
    int size();
    void clear();
    bool contains(T element, bool equals( T& a, T& b));
    ostream& print( ostream& out);
    iterator begin(){ return iterator(array[0]);}       // array[0] = &(array[0][0]) it's an address of the head
    iterator end(){ return iterator(array[0]+index+1);}
    const_iterator begin() const { return const_iterator(array[0]);}
    const_iterator end() const { return const_iterator(array[0]+index+1);}
    
};

//********************************implement function**********************************

template <class T>
void SDAL<T>::replace(T element, int position)
{
    array[position-1] = element;
}

template <class T>
void SDAL<T>::insert(T element, int position)
{
    if(position < 0)
        cout<<"cannot insert to a negative position\n";
    else if(position>index+1)
        cout<<"Error! cannot insert to this position\n";
    else
    {
        if(position == index+1)
            push_back(element);
        else if(position == 0)
            push_front(element);
        else
        {
            cout<<"insert else\n";
            changeSize();
            T temp = array[0][position];
            T temp2;
            array[0][position] = element;
           // cout<<array[0][position]<<endl;
            for(int i = position; i <index; i++)
            {
                temp2 = array[0][i+1];
               // cout<<temp2<<" \t";
                array[0][i+1] = temp;
              //  cout<<temp<<" \t";
                temp = temp2;
            }
            index++;
            array[0][index] = temp;
        }
    }
}

template <class T>
void SDAL<T>::push_back(T element)
{
    changeSize();                                       //check if array is full or wast too much memory
    array[0][index+1] = element;
    index++;
}

template <class T>
void SDAL<T>::push_front(T element)
{
 //   changeSize();
    if(is_empty())
    {
        array[0][0] = element;
    }
    else
    {
        T tempNext, temp;
        temp = array[0][0];
        array[0][0] = element;
        for(int i = 1; i <= index+1; i++)
        {
            tempNext = array[0][i];                        //copy the value of array[i] to tempNext
            array[0][i] = temp;                            //replace the array[i] to value temp
            temp = tempNext;                             //assign temp get the value of tempNext;
        }
    }
    index++;
}

template <class T>
T SDAL<T>::remove(int position)
{
    if(position < 0)
        cout<<"Error! position cannot be < 0\n";
    else if(position > index)
        cout<<"Error! no element in this position\n";
    else
    {
        if(position == 0)
            pop_front();
        else if(position == index)
            pop_back();
        else
        {
            for(int i = position; i < index; i++)
            {
                array[0][i] = array[0][i+1];
            }
            index--;
        }
    }
}

template <class T>
T SDAL<T>::pop_back()
{
    T temp = array[0][index];
    index--;
    
    return temp;
}


template <class T>
T SDAL<T>::pop_front()                                  //return the first element and deleted it.
{
    T temp = array[0][0];
    for(int i = 0; i < index; i++)
    {
        array[0][i] = array[0][i+1];
    }
    index--;
    
    return temp;
}

template <class T>
T SDAL<T>::item_at(int position)
{
    if(position<0 || position > index)
        cout<<"error!"<<endl;
    else
        return array[0][position];
}

template <class T>
bool SDAL<T>::is_empty()
{
    if(index == -1)
        return true;
    else
        return false;
}

template <class T>
int SDAL<T>::size()
{
    return (index+1);
}


template <class T>
void SDAL<T>::clear()
{
    for(int i = 0; i <=index; i++)
    {
        array[0][i] = NULL;
    }
    index = -1;
}

template <class T>
bool SDAL<T>::contains(T element, bool equals( T& a, T& b))
{
    int temp = 0;
    while(temp > index)
    {
        if(equals(element,array[0][temp]))
            return true;
        else
            temp++;
    }
    return false;
}

template <class T>
ostream& SDAL<T>::print( ostream& out)
{
    if(is_empty())
        out<< "<empty list>";
    else
    {
        out << "[";
        for(int i = 0; i <= index; i++)
        {
            out<<array[0][i];
            if(i != index)
                out<<",";
        }
        out<<"]";
    }
    return out;
}

//***************************************** main function ***********************************

