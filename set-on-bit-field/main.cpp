//#include <iostream>
//#include "Set.h"
//using namespace std;
//
//
//int main() {
//	Set set(100);
//    set.insert(3);
//    set.insert(6);
//    set.insert(50);
//    set.insert(99);
//    set.insert(100);
//    set.insert(101);
//    set.insert(1000);
//    cout<<"set: ";
//    set.print();
//
//    Set set2(20);
//    set2.insert(2);
//    set2.insert(3);
//    set2.insert(4);
//    cout<<"set2: ";
//    set2.print();
//
//    Set set4(1);
//    set4.insert(1);
//
//    Set empty;
//    cout<<"empty: ";
//    empty.print();
//    cout<<endl;
//
//    cout<<"set.member(3): "<<set.member(3)<<endl;
//    cout<<"set.member(4): "<<set.member(4)<<endl;
//    cout<<"empty.member(100): "<<empty.member(100)<<endl;
//
//    Set set3;
//
//    set3.setUnion(set, set2);
//    cout<<"union: ";
//    set3.print();
//
//    set3.intersection(set, set2);
//    cout<<"intersection: ";
//    set3.print();
//
//    set3.difference(set, set2);
//    cout<<"difference: ";
//    set3.print();
//
//    set3.merge(set, set4);
//    cout<<"merge: ";
//    set3.print();
//
//    set3.del(3);
//    cout<<"del(3): ";
//    set3.print();
//
//    set3.del(99);
//    cout<<"del(99): ";
//    set3.print();
//
//    set3.del(100);
//    cout<<"del(100): ";
//    set3.print();
//
//    set3.del(1);
//    cout<<"del(1): ";
//    set3.print();
//
//    cout<<"maxVal: "<<set3.maxVal()<<endl;
//    cout<<"minVal: "<<set3.minVal()<<endl;
//
//    cout<<"set2: ";
//    set2.print();
//    cout<<"set3: ";
//    set3.print();
//
//    cout<<"set2.assign(set3): ";
//    set2.assign(set3).print();
//
//    cout<<"set2.equal(set3): "<<set2.equal(set3)<<endl;
//    cout<<"set2.equal(set): "<<set2.equal(set)<<endl;
//
//    cout<<"----------------------------"<<endl;
//    Set set5(1000);
//
//    set5.insert(5);
//    set5.insert(10);
//    set5.insert(15);
//    cout<<"set5: ";
//    set5.print();
//    cout<<"set3: ";
//    set3.print();
//
//    Set res(100);
//    res.assign(set3.find(set5, 10));
//    cout<<"set3.find(set4, 10): ";
//    res.print();
//
//	return 0;
//}
