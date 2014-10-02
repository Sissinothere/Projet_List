
// SSLL.H
//
// Singly-linked list (non-polymorphic)
//
// by Dave Small
// for COP 3530
// 201409.16 - created

#include <iostream>
//#include <stdexcept>
#include "catch.hpp"


namespace cop3530 {
    
    template <typename T>
    class SSLL  {
        
    private:
        typedef struct Node {
            T data;
            Node* next;
        }*nodePrt; // end struct Node
        
        nodePrt head;
        nodePrt tail;
        nodePrt temp;
        int listSize;
        
    public:
          //*************************************** iterator ****************************************
        class SSLL_Iter //: public std::iterator<std::forward_iterator_tag, T>
        {
        private:
            Node* here;
            
        public:
            // inheriting from std::iterator<std::forward_iterator_tag, T>
            // automagically sets up these typedefs...
            typedef T value_type;
            typedef std::ptrdiff_t difference_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::forward_iterator_tag iterator_category;
            
            // but not these typedefs...
            typedef SSLL_Iter self_type;
            typedef SSLL_Iter& self_reference;
            
            
            // src 是个参数，src包含node here,??????
            explicit SSLL_Iter( Node* start = NULL ) : here( start )
            {
                //:here(start) means here = NULL;
            }
            
            SSLL_Iter( const SSLL_Iter& src ) : here( src.here )
            {
                //this is a copy constructor, calls copy constructor of the Node* here
                
                //: here( src.here ) means here = src.here
            }
            reference operator*() const
            {
                return here->data;                  // return T&, data value can be changed
            }
            
            pointer operator->() const
            {
                return &(operator*());
            }
            
            self_reference operator=(const SSLL_Iter& src )
            {
                if(this != &src)
                    here = src.here;
                //src is a object, not pointer, so don't use ->
                return *this;       //return of object data. can be changed
                // SSLL_Iter*  : will return object's address.
            }
            
            self_reference operator++()
            {
                here = here->next;
                return *this;
            } // preincrement
            
            self_type operator++(int)
            {
                //  for(int i = 0;i<5; ++i)
                self_type temp = *this;
                //this return address of the object
                //*this returns the object itself
                this->here = here->next;
                
                return temp;
            } // postincrement
            
            bool operator==(const SSLL_Iter& rhs) const
            {
                return here == rhs.here;
            }
            bool operator!=(const SSLL_Iter& rhs) const
            {
                return here != rhs.here;
            }
        }; // end SSLL_Iter
        //   typedef SSLL_Iter iterator;
        
        //*************************************** const interator ****************************************
        
        class SSLL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
        {
        private:
            const Node* here;
            
        public:
            // inheriting from std::iterator<std::forward_iterator_tag, T>
            // automagically sets up these typedefs...
            typedef T value_type;
            typedef std::ptrdiff_t difference_type;
            //  typedef const T& reference;
            typedef const T& const_reference;   //
            
            typedef const T* pointer;
            typedef std::forward_iterator_tag iterator_category;
            
            // but not these typedefs...
            typedef SSLL_Const_Iter self_type;
            typedef SSLL_Const_Iter& self_reference;
            
            
            explicit SSLL_Const_Iter( Node* start = NULL ) : here( start ) {}
            SSLL_Const_Iter( const SSLL_Const_Iter& src ) : here( src.here ) {}
            
            const_reference operator*() const         //const 放在后面有重载函数的功能
            {
                return *this;
            }
            pointer operator->() const
            {
                return &(operator*());
            }
            
            self_reference operator=( const SSLL_Const_Iter& src )
            {
                here = src.here;
                return *this;
            }
            
            self_reference operator++()                     //reference means can change value, like *here = 5;
            {
                here = here->next;
                return *this;
            } // preincrement
            
            self_type operator++(int)
            {
                self_type temp = *this;
                this->here = here->next;
                return temp;
            } // postincrement
            
            bool operator==(const SSLL_Const_Iter& rhs) const
            {
                return here == rhs.here;
            }
            bool operator!=(const SSLL_Const_Iter& rhs) const
            {
                return here != rhs.here;
            }
        }; // end SSLL_Iter
        
        
        //*************************************** implement function ****************************************
        
        //--------------------------------------------------
        // types
        //--------------------------------------------------
        typedef std::size_t size_t;
        typedef T value_type;
        typedef SSLL_Iter iterator;
        typedef SSLL_Const_Iter const_iterator;
        //--------------------------------------------------
        // Constructors/destructor/assignment operator
        //--------------------------------------------------
        
        
        SSLL()
        {
            head = NULL;
            //head2 = NULL;
            tail = NULL;
            temp = NULL;
            listSize = 0;
        }
        
        //-----??---------------------------------------------
        SSLL( const SSLL& src )                     //copy constructor
        {
            head = src.head;
            tail = src.tail;
            temp = src.temp;
            listSize = src.listSize;
        }
        
        //------------??--------------------------------------
        ~SSLL()
        {
            // safely dispose of this SSLL's contents
            //   delete this; // give error does not work!
            //it doest not create any new, do not use delete keyword
            
        }
        
        //-----------??---------------------------------------
        SSLL& operator=( const SSLL& src ) {
            if ( &src == this ) // check for self-assignment
                return *this;     // do nothing
            
            // safely dispose of this SSLL's contents
            // populate this SSLL with copies of the other SSLL's contents
        }
        
        //--------------------------------------------------
        // member functions
        //--------------------------------------------------
        
        T replace( const T& element, int position )
        {
            T temp1;
            temp = head;
            for(int i = 0; i < position; i++)
            {
                temp = temp->next;
            }
            temp1 = temp->data;
            temp->data = element;
            
            return temp1;
        }
        
        //--------------------------------------------------
        void insert( const T& element, int position )
        {
            if(position < 0)
            {
                std::cout<< "position has larger than 0!";
            }
            else if(position >= size() && size() != 0)                  //if size = 0; can insert a value in the list,
                //if if size = 5; position = 5 cannot insert value.
            {
                std::cout<< "the list is too short to add " << element << " in the " << position << " position!";
            }
            else
            {
                nodePrt n = new Node;                       //create a new node
                n->data = element;
                temp = head;
                
                if(position == 0)                           //from beginning
                {
                    if(head != NULL)
                    {
                        push_front(element);
                    }
                    else
                    {
                        head = n;
                        tail = n;
                        tail->next = NULL;
                        listSize++;
                    }
                }
                else if(position == 1)                          //insert an number right after head
                {
                    n->next = temp->next;
                    head->next = n;
                    listSize++;
                }
                else
                {
                    for(int i = 0; i < position; i++)            // insert between two number, or add in front of the tail
                    {
                        temp = temp->next;
                        //  std::cout<< "head = null \n";
                    }
                    
                    n->next = temp->next;                       // link
                    temp->next = n;
                    if(position == listSize-1)
                    {
                        std::cout<< "here is tail\n";
                        tail = n;
                    }
                    listSize++;
                }
            }
        }
        
        //--------------------------------------------------
        void push_front( const T& element )
        {
            nodePrt n = new Node;               //create a new node
            n->data = element;
            temp = head;
            n->next = temp;
            
            head = n;
            listSize++;
        }
        
        //--------------------------------------------------
        void push_back( const T& element )
        {
            if(listSize==0)
            {
                push_front(element);
            }
            else
            {
                nodePrt n = new Node;
                n->data = element;
                
                // temp = tail;
                tail->next = n;
                //  std::cout<< "tail->data " << tail->data << std::endl;
                //   n->next = NULL;
                tail = n;
                listSize++;
            }
        }
        
        //--------------------------------------------------
        T pop_front()                                                     //return the first number and then delete it
        {
            T tempData = head->data;
            remove(0);
            return tempData;
        }
        
        //--------------------------------------------------
        T pop_back()
        {
            T tempData = tail->data;
            remove(listSize-1);
            return tempData;
        }
        
        //--------------------------------------------------
        T remove( int position )
        {
            T tempData;
            temp = head;
            if(position < 0)
            {
                std::cout<< "deleting position need to larger than 0!";
                
            }
            else if(position == 0)                              //delete the head;
            {
                head = head -> next;
                listSize--;
                tempData = temp->data;
            }
            else if(position > listSize-1)
            {
                std::cout<< "position has already delete!";
            }
            else                                                   //delete the middle
            {
                std::cout<< "..........";
                std::cout<< listSize ;
                
                for(int i = 0; i < position-1; i++)
                {
                    std::cout<< "deleting!"<<std::endl;
                    temp = temp->next;                              //goes to the position->next node
                }
                
                if(position == (listSize - 1))                    // delete the tail
                {
                    std::cout<< listSize << "deleting tail!";
                    temp->next = NULL;
                    tempData = tail->data;
                    tail = temp;
                    listSize--;
                }
                else                                            //delete in middle element
                {
                    tempData = temp->next->data;
                    temp->next = temp->next->next;
                    listSize--;
                }
            }
            return tempData;
        }
        
        //--------------------------------------------------
        T item_at( int position ) const
        {
            T tempData;
            
            if(position < 0)
            {
                std::cout<< "position has larger than 0!";
            }
            else if(position >= size())                  //if size = 0; can insert a value in the list,
                //if if size = 5; position = 5 cannot insert value.
            {
                std::cout<< "the list has not reach the" << position << " position!";
            }
            else
            {
                nodePrt temp1 = head;
                
                for(int i = 0; i < position; i++)
                {
                    temp1=temp1->next;
                }
                tempData = temp1->data;
            }
            return tempData;
        }
        
        //--------------------------------------------------
        bool is_empty() const
        {
            if(listSize == 0)
                return true;
            else
                return false;
        }
        
        //--------------------------------------------------
        size_t size() const                                        //const function cannot assign variable
        {
            return listSize;
        }
        
        //--------------------------------------------------
        void clear()
        {
            temp = head;
            for(int i = 0; i < listSize; i++)
            {
                temp->data = NULL;
                temp = temp->next;
            }
            // listSize = 0;
        }
        
        //--------------------------------------------------
        bool contains( const T& element, bool equals( const T& a, const T& b  ) ) const
        {
            nodePrt temp1 = head;
            while(temp1 != NULL)
            {
                if( equals(element,temp1->data))
                    return true;
                else
                {
                    temp1 = temp1->next;
                }
            }
            return false;
        }
        
        //--------------------------------------------------
        std::ostream& print( std::ostream& out ) const          // Private value cannot change in the const function
        {
            if(is_empty())
                out<< "<empty list>";
            else
            {
                nodePrt temp1 = head;                           //need to create a new variable.
                out << "[";
                while(temp1 != NULL)
                {
                    out<< temp1->data << ", ";
                    temp1 = temp1->next;
                }
                out<<"]"<<std::endl;
            }
            return out;
        }
        
        //==============================================================
        iterator begin()
        { return SSLL_Iter( head ); }
        
        iterator end()
        { return SSLL_Iter(tail); }
        
        const_iterator begin() const { return SSLL_Const_Iter(head); }
        const_iterator end() const { return SSLL_Const_Iter(); }
        
         //*************************************** implement part 3  ****************************************
       
        T& operator[] (int i)                                           //return value can be changed
        {
            //nodePrt temp1;

        
                if(i>=0 && i < listSize)
                {
                    std::cout<<"in else statement !\n";
                    temp = head;
                    for(int j = 0; j < i; j++)
                    {
                        temp=temp->next;
                    }
                     return temp->data;
                }
                else
                    throw std::out_of_range("can not less than 0 or lager than the size");
        }
        
        T const& operator[](int i) const                                     //return value cannot be changed
        {
            return item_at(i);
        }
        
    }; //end class SSLL
} // end namespace cop3530int main()
