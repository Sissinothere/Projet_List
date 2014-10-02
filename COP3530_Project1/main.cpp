//
//  main.cpp
//  COP3530_Project1
//
//  Created by Sissi on 10/2/14.
//  Copyright (c) 2014 Sissi. All rights reserved.
//
#include "CDAL.h"

bool equals(char &a, char &b)
{
    return (a == b);
}

void in_list( CDAL<char> list, char c, ostream& out ) {
    out << c << " is " << (list.contains( c, equals ) ? "" : "not ")
    << "in the list ";
    list.print(out);
    out << endl;
}

int main()
{
    CDAL<char> list;
    list.push_front('l');
    list.print(cout);
    cout<<endl;
    
    list.push_back('x');
    list.print(cout);
    cout<<endl;
    
    list.push_front('p');
    list.print(cout);
    cout<<endl;
    
    list.push_back('o');
    list.print(cout);
    cout<<endl;
    
    list.push_back('b');
    list.print(cout);
    cout<<endl;
    
    list.push_front('a');
    list.print(cout);
    cout<<endl;
    
    list.push_back('0');
    list.print(cout);
    cout<<endl;
    
    list.push_front('j');
    list.print(cout);
    cout<<endl;
    
    list.insert('e',0);
    list.print(cout);
    cout<<endl;
    cout<<endl;
    
    list.insert('k',1);
    list.print(cout);
    cout<<endl;
    cout<<endl;
    
    list.insert('z',3);
    list.print(cout);
    cout<<endl;
    cout<<endl;
    
    list.insert('m',6);
    list.print(cout);
    cout<<endl;
    cout<<endl;
    //cout<<"remove the last element: "<< list.pop_back()<<endl;
    list.pop_back();
    list.print(cout);
    cout<<endl;
    cout<<endl;
    
    cout<< list.pop_back()<<endl;;
    list.print(cout);
    cout<<endl;
    
    cout<< list.pop_back()<<endl;;
    list.print(cout);
    cout<<endl;
    
    
    
    cout<<"at position 7 is " << list.item_at(7)<<endl;
    
    in_list( list, 'x', cout );
    cout<<endl;
    
    list.remove(1);
    list.print(cout);
    
    list.remove(4);
    list.print(cout);
    
    return 0;
}

/*
 int main()
 {
 SDAL<char> array(5);
 
 array.push_front('x');
 array.print(cout);
 cout<<endl;
 
 array.push_front('y');
 array.print(cout);
 cout<<endl;
 
 array.push_back('z');
 array.print(cout);
 cout<<endl;
 
 array.insert('o',3);
 array.print(cout);
 cout<<endl;
 
 array.insert('c',3);
 array.print(cout);
 cout<<endl;
 
 array.insert('p',3);
 array.print(cout);
 cout<<endl;
 
 cout<<array.remove(3)<<endl;
 array.print(cout);
 cout<<endl;
 
 
 cout<<array.item_at(3)<<endl;
 
 const SDAL<char> copy_array = array;
 cout<<"print copy array: ";
 copy_array.print(cout);
 

const SDAL<char> const_array = array;
SDAL<char>::iterator iter = array.begin();

SDAL<char>::const_iterator const_iter = const_array.begin();

cout<<"iterator: \n";

*iter = 'Q';
for(iter; iter!=array.end();iter++)                                  //end before the last element. so need to tail = array[0]+index+1;
cout<<*iter<<endl;



return 0;
}
*/


/*
 int main()
 {
 cop3530::SSLL<int> l;
 
 for(int i = 0; i< 5; i++)
 l.push_front(i);
 
 l.print( std::cout );
 
 try{
 l[0] = 9;
 l[-1] = 90;          //this will stop. what we gona do to the next one.
 l[10] = 80;
 }
 catch (std::out_of_range& e)
 {
 std::cout<<e.what()<<std::endl;
 //  return temp->data;
 }
 
 
 const cop3530::SSLL<int> const_l=l;
 
 const_l.print( std::cout );
 
 return 0;
 }
 
 */
