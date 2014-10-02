



#include <iostream>
using namespace std;

template <class T>
class CDAL
{
private:
    typedef struct Node{
       // T data[3];                                   //data stores array
        T* data = new T[3];                             //for resize temp->data = new T[3/2];
        Node* next;
    }*nodePrt;
    
    nodePrt head = new Node;
    nodePrt temp, tail;

    int nodeSize, listSize, index, actualNodeSize;
   
    void listChange()
    {
        if(index == 2)                                                         //add node
        {
            nodePrt n = new Node;
            temp = tail;
            temp->next = n;
            tail = n;
            tail->next = NULL;
            nodeSize++;
            actualNodeSize++;
            index = -1;
        }
    }
    void checkDeleteNode()
    {
        if(index==-1)
        {
            nodeSize--;
            index = 2;
            //move the tail to the previos node;
            temp = head;
            while(temp->next!=tail)
                temp = temp->next;
            tail = temp;
            temp = temp->next;
            delete temp;
            tail->next = NULL;
        }
        cout<<"in deletenode(), node is "<<nodeSize<<endl;
    }
    
    int indexNode(int position)                                 //return current index postion of the node
    {
        if(listSize <= 2)
            return 0;
        else
            return position/3;
    }
    int indexArray(int position)                                //return current index position of the array
    {
        return position%3;
    }
    void checkError(int position)
    {
        try {
            if(position < 0 || position > listSize-1)
                throw out_of_range("out of range!!! error!!!");
        } catch (out_of_range &e) {
            cout << e.what() <<endl;
        }
    }
    
public:
    CDAL(){
        
        temp = NULL;
        tail = head;
        nodeSize = 0;
        actualNodeSize = 0;
        listSize = 0;
        index = -1;
    }
   // ~CDAL();
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
};


template <class T>
void CDAL<T>::replace(T element, int position)
{
    int node = indexNode(position);
    int indPosition = indexArray(position);
    temp = head;
    
    for(int i = 0; i < node; i++)
    {
        temp = temp->next;
    }
    temp->data[indPosition] = element;
}

template <class T>
void CDAL<T>::insert( T element, int position)
{
    
    int node = indexNode(position);                             //how many nodes that the position in
    int indPosition = indexArray(position);                     //in which index position
    
    if(position < 0 || position > listSize)
        cout<<"Error!"<<endl;
    else if(position == 0)
        push_front(element);
    else if(position == listSize)
        push_back(element);
    else
    {
        listChange();                                       //while change size, index = -1. so  wehn
        index++;
    //    cout<<"in the insert, index is "<<index<<'\n'<<endl;
        //move the node to the position node
        temp = head;
      
//        nodePrt temp2 = temp;
        T *Array = new T[listSize+1];                   //store all the element in the array
     
//        T store = element;                                                //copy the element to the Temp array.
        int ArrayIndex = 0;
        //copy the all the elements befroe the insert elemets
        
  //      cout<<"node in insert is "<<node<<endl;
  //      cout<<"indPosition in insert is "<<indPosition<<endl;
        for(int i = 0; i <=node; i++)
        {
            if(i == node)
            {
                for(int i = 0; i < indPosition; i++)
                {
                    Array[ArrayIndex] = temp->data[i];
                    ArrayIndex++;
                }
            }
            else
            {
                for(int i = 0; i < 3; i++)
                {
                    Array[ArrayIndex] = temp->data[i];
                    ArrayIndex++;
                }
                temp = temp->next;
            }
            
        }
        //store the change element
        cout<<"placed array index is "<<ArrayIndex<<endl;
        Array[ArrayIndex] = element;
        ArrayIndex++;
        
        //continue complete the copy array in the current node
        
        //what if the arrayIndx is in the last element?
        //need a if else statement here
        for(int i = indPosition; i < 3;i++)
        {
            Array[ArrayIndex] = temp->data[i];
             ArrayIndex++;
        }
        
        //add the rest of the elment in the other node
        while(temp->next != NULL)
        {
            temp= temp->next;
            for(int i = 0; i < 3; i++)                   //copy the rest of the node
            {
                Array[ArrayIndex] = temp->data[i];
                ArrayIndex++;
            }
        }
        
        //replace the original nodes
        
        temp = head;
        ArrayIndex = 0;
        for(int i = 0; i <= nodeSize; i++)              //
        {
            if(temp->next != NULL)
            {
                for(int j = 0; j < 3; j++)
                {
                    temp->data[j] = Array[ArrayIndex];
                    ArrayIndex++;
                }
            }
            else
            {
                for(int i = 0; i <=index; i++)
                {
                    temp->data[i] = Array[ArrayIndex];
                    ArrayIndex++;
                    //     cout<<"the last element of the node is "<<temp->data[i]<<endl;
                }
                temp->data[index+1] = Array[ArrayIndex];
            }
            temp = temp->next;
        }
        
       
        
    //print temp array------------------------
        
        for(int i= 0; i < listSize+1;i++)
            cout<<Array[i]<<" ";
        cout<<endl;
    
        delete[] Array;
      
    
        listSize++;
    }
 //   cout<<"after inser, index is "<<index<<endl;
}

template <class T>
void CDAL<T>::push_back(T element)
{
    listChange();
    int node = indexNode(listSize+1);                           //add 1 because it need to add one ore in the list
 //   cout<<"node is "<<node<<endl;
    int indPosition = indexArray(listSize);                     //return current next index array position,
    //   cout<<"inposition is "<<indPosition<<endl;
    temp = head;                                                //move to the empty node position
    for(int i = 0; i < node; i++)
    {
        temp = temp->next;
    }
    temp->data[indPosition] = element;
    
    listSize++;
    index++;
}

template <class T>
void CDAL<T>::push_front(T element)
{
    listChange();
    if(index == -1)                                             //node array is empty
    {
        head->data[0]=element;
    }
    else if(listSize <= 2)                                      //list size less than 49. still in the same node
    {
        T temp1 = head->data[0];                                //store the first element
        head->data[0] = element;
        T tempNext;
        for(int i = 1; i <= index+1; i++)                         //shift to the right
        {
            tempNext = head->data[i];
            head->data[i] = temp1;
            temp1 = tempNext;
        }
    }
    else
    {
        T *Array = new T[listSize+1];
        Array[0] = element;
        temp = head;                                                //copy the element to the Temp array.
        int ArrayIndex = 0;
        for(int i = 0; i <= nodeSize; i++)
        {
            if(temp->next != NULL)
            {
                for(int j = 0; j < 3; j++)
                {
                    Array[ArrayIndex+1] = temp->data[j];
                    ArrayIndex++;
                }
            }
            else
            {
                for(int i = 0; i <=index; i++)
                {
                    
                    Array[ArrayIndex+1] =  temp->data[i];
                    ArrayIndex++;
                }
            }
            temp = temp->next;
        }
        
        // change all the elements in the list
        temp = head;
        ArrayIndex = 0;
        for(int i = 0; i <= nodeSize; i++)
        {
            if(temp->next != NULL)
            {
                for(int j = 0; j < 3; j++)
                {
                   temp->data[j] = Array[ArrayIndex];
                   ArrayIndex++;
                }
            }
            else
            {
                for(int i = 0; i <=index; i++)
                {
                    temp->data[i] = Array[ArrayIndex];
                    ArrayIndex++;
               //     cout<<"the last element of the node is "<<temp->data[i]<<endl;
                }
                 temp->data[index+1] = Array[ArrayIndex];
            }
            temp = temp->next;
        }

        //print temp array------------------------
        /*
        for(int i= 0; i < listSize+1;i++)
            cout<<Array[i]<<" ";
        cout<<endl;
         */
        delete[] Array;
    }
    index++;
    listSize++;
}

template <class T>
T CDAL<T>::remove(int position)
{
    int node = indexNode(position);                             //how many nodes that the position in
    int indPosition = indexArray(position);                     //in which index position
    T pop = NULL;
    checkError(position);
    
    if(position == 0)
        return pop_front();
    else if(position == listSize)
        return pop_back();
    else
    {
        //******************** create an new array to store all the changed element with order ***********************
       
        T *Array = new T[listSize-1];
        temp = head;                                                //copy the element to the Temp array.
        int ArrayIndex = 0;
       
        for(int i = 0; i <= node; i++)
        {
            if(i != node)                                           //copy all node's element before the node contains the deleted element
            {
                for(int j = 0; j < 3; j++)
                {
                    Array[ArrayIndex++] = temp->data[j];
                  //  ArrayIndex++;
                }
            }
            else
            {
                pop = temp->data[indPosition];
                
                for(int i = 0; i < indPosition; i++)                //in the node that containst the delete element, copy the elements before the deleted one
                {
                    Array[ArrayIndex++] = temp->data[i];
                  //  ArrayIndex++;
                }
                
                for(int j = indPosition+1; j < 3; j++)
                {
                    Array[ArrayIndex++] = temp->data[j];
                }
            }
            temp = temp->next;
        }
        
        // copy all elements after the node
        
        for(int i = node+1; i <= nodeSize; i++)
        {
            if(temp->next != NULL)
            {
                for(int j = 0; j < 3; j++)
                {
                    Array[ArrayIndex++] = temp->data[j];
                   // ArrayIndex++;
                }
            }
            else
            {
                for(int i = 0; i <=index; i++)
                {
                    Array[ArrayIndex++] =  temp->data[i];
                   // ArrayIndex++;
                }
            }
            temp = temp->next;
        }
        
        // change all the elements in the list
        temp = head;
        ArrayIndex = 0;
        for(int i = 0; i <= nodeSize; i++)
        {
            if(temp->next != NULL)
            {
                for(int j = 0; j < 3; j++)
                {
                    temp->data[j] = Array[ArrayIndex];
                    ArrayIndex++;
                }
            }
            else
            {
                for(int i = 0; i <=index-1; i++)                                        // what if index-1 = -1?
                {
                    temp->data[i] = Array[ArrayIndex];
                    ArrayIndex++;
                    //     cout<<"the last element of the node is "<<temp->data[i]<<endl;
                }
            }
            temp = temp->next;
        }
        delete[] Array;
        index--;
        listSize--;
        listChange();
        checkDeleteNode();
      //  return pop;
    }
    return pop;
}

template <class T>
T CDAL<T>::pop_back()
{
    temp = head;
    cout<<"index is "<<index<<endl;
    cout<<"nodeSize is "<<nodeSize<<endl;
    
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
     T temp1 = temp->data[index];

    index--;
    listSize--;
    
    checkDeleteNode();                  //thrink the node

    return temp1;
}

template <class T>
T CDAL<T>::pop_front()
{
    listChange();
    checkError(listSize);

    T *Array = new T[listSize+1];
    temp = head;                                                //copy the element to the Temp array.
    int ArrayIndex = 0;
    for(int i = 0; i <= nodeSize; i++)
    {
        if(temp->next != NULL)
        {
            for(int j = 0; j < 3; j++)
            {
                Array[ArrayIndex++] = temp->data[j];
            }
        }
        else
        {
            for(int i = 0; i <=index; i++)
            {
                Array[ArrayIndex++] =  temp->data[i];
            }
        }
            temp = temp->next;
        }
        
        // change all the elements in the list
        temp = head;
        ArrayIndex = 0;
        for(int i = 0; i <= nodeSize; i++)
        {
            if(temp->next != NULL)
            {
                for(int j = 0; j < 3; j++)
                {
                    temp->data[j] = Array[ArrayIndex];
                    ArrayIndex++;
                }
            }
            else
            {
                for(int i = 0; i <=index; i++)
                {
                    temp->data[i] = Array[ArrayIndex];
                    ArrayIndex++;
                    //     cout<<"the last element of the node is "<<temp->data[i]<<endl;
                }
                temp->data[index+1] = Array[ArrayIndex];
            }
            temp = temp->next;
        }
        
        //print temp array------------------------
        /*
         for(int i= 0; i < listSize+1;i++)
         cout<<Array[i]<<" ";
         cout<<endl;
         */
        delete[] Array;
    }
    index--;
    listSize--;
    return head->data[0];
}

template <class T>
T CDAL<T>::item_at(int position)
{
  //  temp = NULL;
    if(position<0 || position>=listSize)
        throw out_of_range("error! position is out of range!");
    else
    {
        int node = indexNode(position);
        int indPosition = indexArray(position);                         //
        temp = head;
    //    cout<<"node is "<<node<<endl;
    
        for(int i = 0; i <= node; i++)
        {
            if(i==node)
            {
                return temp->data[indPosition];
            }
            temp = temp->next;
        }
    }
    return NULL;                             //control may reach end of non-void function
}

template <class T>
bool CDAL<T>::is_empty()
{
    if(index == -1)
        return true;
    else
        return false;
}


template <class T>
int CDAL<T>::size()
{
    return listSize;
}

template <class T>
void CDAL<T>::clear()
{
  //  delete node;
}

template <class T>
bool CDAL<T>::contains(T element, bool equals( T& a, T& b))
{

    temp = head;
    for(int i = 0; i <= nodeSize; i++)                          //loop over all the nodes and search for nodes
    {
        if(i!=nodeSize)
        {
            for(int i = 0; i < 3; i++)
           {
               if(equals(element,temp->data[i]))
               {
                 //  cout<<"equal equation"<<endl;
                   return true;
               }
           }
                temp = temp->next;
        }
        else
        {
            for(int i = 0; i <= index; i++)
            {
              //  cout<<"temp->data[i] "<< temp->data[i]<<endl;
                if(equals(element,temp->data[i]))
                {
              //   cout<<"equal equation"<<endl;
                    return true;
                }
            }
        }
    }
    
    return false;
}

template <class T>
ostream& CDAL<T>::print( ostream& out)
{
    if(is_empty())
        out<< "<empty list>";
    else
    {
        cout<<"in print nodeSize: " << nodeSize<<endl;
        cout<<"in print index: "<< index <<endl;
        out<< "[";
        temp = head;
        for(int i = 0; i <= nodeSize; i++)
        {
            if(temp->next != NULL)
            {
                for(int j = 0; j < 3; j++)
                {
                    out<<temp->data[j]<<",";
                }
            }
            else
            {
               // cout<<"in print else statement"<<endl;
                for(int i = 0; i <=index; i++)
                {
                    out<<temp->data[i];
                    if(i!=index)
                        cout<<",";
                }
                out<<"]";
            }
            temp = temp->next;
        }
    }
        return out;
}



