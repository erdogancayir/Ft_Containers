#include "vector.hpp"
#include "reverse_iterator.hpp"
#include "iterator.hpp"
#include "vector"
#include "iterator"

#define ecayir ft
#define Vector vector

int main()
{
    {
        std::cout << "~~~~~~~~~~ Vector Constructors ~~~~~~~~~~" << std::endl;
        ecayir::Vector<int> first;
        ecayir::Vector<int> iter;
        ecayir::Vector<int> sec(5, 1907);
        ecayir::Vector<int> th(sec.begin(), sec.end());
        ecayir::Vector<int> ft(th);

        int array[] = {1, 9, 0, 7};
        ecayir::Vector<int> fifth (array, array + sizeof(array) / 4);
        std::cout << "The contents of fifth are:" << std::endl;
        for (ecayir::Vector<int>::iterator _iter = ft.begin(); _iter != ft.end(); _iter++)
            std::cout << " " << *_iter;
        std::cout << std::endl;
    }
    {
        std::cout << "~~~~~~~~~~ Vector Assign content (operator=) ~~~~~~~~~~" << std::endl;
        ecayir::Vector<int> ecole(5, 5);
        ecayir::Vector<int> Kocaeli(2, 2);
        ecole = Kocaeli;
        ecole = ecayir::Vector<int>();
        std::cout << "Ecole size: " << ecole.size() << "\n";
        std::cout << "Kocaeli size: " << Kocaeli.size() << "\n";
    }
    {
        std::cout << "~~~~~~~~~~ Return iterator to beginning ~~~~~~~~~~" << std::endl;
        ecayir::Vector<int> vec;
        for (int i=1; i<=5; i++)
            vec.push_back(i);
        ecayir::Vector<int>::iterator _itt = vec.begin();
        for (_itt = vec.begin() ; _itt != vec.end(); _itt++)
            std::cout << " " << *_itt;
        std::cout << std::endl;
    }
    {
        std::cout << "~~~~~~~~~~  reverse iterator to reverse beginning ~~~~~~~~~~" << std::endl;
	    ecayir::Vector<int> myvector1 (5);  // 5 default-constructed ints
	    int i1=0;
	    ecayir::Vector<int>::reverse_iterator rit1 = myvector1.rbegin();
	    for (; rit1!= myvector1.rend(); ++rit1)
	    	*rit1 = ++i1;
	    std::cout << "myvector contains:";
	    for (ecayir::Vector<int>::iterator it1 = myvector1.begin(); it1 != myvector1.end(); ++it1)
	    	std::cout << ' ' << *it1;
	    std::cout << '\n';
    }
    {
        std::cout << "~~~~~~~~~~  Return maximum size ~~~~~~~~~~" << std::endl;
        ecayir::Vector<int> myvector1;
	    for (int i=0; i<100; i++) myvector1.push_back(i);
	    std::cout << "size: " << myvector1.size() << "\n";
	    std::cout << "capacity: " << myvector1.capacity() << "\n";
	    std::cout << "max_size: " << myvector1.max_size() << "\n";
    }
    {
        std::cout << "~~~~~~~~~~  Change size ~~~~~~~~~~" << std::endl;
		ecayir::Vector<int> myvector1;
		for (int i=1;i<10;i++) myvector1.push_back(i);
		myvector1.resize(9);
		myvector1.resize(12,100);
		myvector1.resize(11);
		std::cout << myvector1.size() << std::endl;
		std::cout << "myvector contains:";
		for (size_t i=0;i<myvector1.size();i++)
			std::cout << ' ' << myvector1[i];
		std::cout << '\n';
    }
    {
        std::cout << "~~~~~~~~~~ Test whether vector is empty ~~~~~~~~~~" << std::endl;
        ecayir::Vector<int> myvector1;
	    int sum1 (0);
	    for (int i=1;i<=10;i++) myvector1.push_back(i);
	    while (!myvector1.empty())
	    {
	    	sum1 += myvector1.back();
	    	myvector1.pop_back();
	    }
	    std::cout << "total: " << sum1 << '\n';
    }
    {
        std::cout << "~~~~~~~~~~ Request a change in capacity ~~~~~~~~~~" << std::endl;
	    ecayir::Vector<int>::size_type sz1;
	    ecayir::Vector<int> foo1;
	    sz1 = foo1.capacity();
	    std::cout << "making foo grow:\n";
	    for (int i=0; i<100; ++i) {
	    	foo1.push_back(i);
	    	if (sz1!=foo1.capacity()) {
	    	    sz1 = foo1.capacity();
	    	    std::cout << "capacity changed: " << sz1 << '\n';
	    	}
	    }
	    ecayir::Vector<int> bar1;
	    sz1 = bar1.capacity();
	    bar1.reserve(100);   // this is the only difference with foo above
	    std::cout << "making bar grow:\n";
	    for (int i=0; i<100; ++i) {
	    	bar1.push_back(i);
	    	if (sz1!=bar1.capacity()) {
	    	sz1 = bar1.capacity();
	    	std::cout << "capacity changed: " << sz1 << '\n';
	    	}
	    }
    }
    {
        std::cout << "~~~~~~~~~~ Access element ~~~~~~~~~~" << std::endl;
        ecayir::Vector<int> myvector1 (10);
	    ecayir::Vector<int>::size_type sz1 = myvector1.size();
	    for (unsigned i=0; i<sz1; i++) myvector1[i]=i;
	    for (unsigned i=0; i<sz1/2; i++)
	    {
	    	int temp1;
	    	temp1 = myvector1[sz1-1-i];
	    	myvector1[sz1-1-i]=myvector1[i];
	    	myvector1[i]=temp1;
	    }
	    std::cout << "myvector contains:";
	    for (unsigned i=0; i<sz1; i++)
	    	std::cout << ' ' << myvector1[i];
	    std::cout << '\n';
    }
    {
        std::cout << "------------- Access element -------------" << std::endl;
	    ecayir::Vector<int> myvector1 (10);
	    for (unsigned i=0; i<myvector1.size(); i++)
	    	myvector1.at(i)=i;
	    std::cout << "myvector contains:";
	    for (unsigned i=0; i<myvector1.size(); i++)
	    	std::cout << ' ' << myvector1.at(i);
	    std::cout << '\n';
    }
    {
        std::cout << "~~~~~~~~~~ Access first element ~~~~~~~~~~" << std::endl;
	    ecayir::Vector<int> myvector1;
	    myvector1.push_back(78);
	    myvector1.push_back(16);
	    myvector1.front() -= myvector1.back();
	    std::cout << "myvector.front() is now " << myvector1.front() << '\n';
    }
    {
        std::cout << "~~~~~~~~~~ Access last element ~~~~~~~~~~" << std::endl;
        ecayir::Vector<int> myvector1;
	    myvector1.push_back(10);
	    while (myvector1.back() != 0)
	    {
	    	myvector1.push_back ( myvector1.back() -1 );
	    }
	    std::cout << "myvector contains:";
	    for (unsigned i=0; i<myvector1.size() ; i++)
	    	std::cout << ' ' << myvector1[i];
	    std::cout << '\n';
    }
    {
        std::cout << "~~~~~~~~~~ Assign vector content ~~~~~~~~~~" << std::endl;
        ecayir::Vector<int> first1;
	    ecayir::Vector<int> second1;
	    ecayir::Vector<int> third1;
	    first1.assign (7,100);
	    ecayir::Vector<int>::iterator it1;
	    it1=first1.begin()+1;
	    second1.assign (it1,first1.end()-1);
	    int myints1[] = {1776,7,4};
	    third1.assign (myints1,myints1+3);
	    std::cout << "Size of first: " << int (first1.size()) << '\n';
	    std::cout << "Size of second: " << int (second1.size()) << '\n';
	    std::cout << "Size of third: " << int (third1.size()) << '\n';
    }
    {
        std::cout << "~~~~~~~~~~ Clear content ~~~~~~~~~~" << std::endl;
	    ecayir::Vector<int> myvector1;
		myvector1.push_back (100);
		myvector1.push_back (200);
		myvector1.push_back (300);
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector1.size(); i++)
			std::cout << ' ' << myvector1[i];
		std::cout << '\n';
		std::cout << myvector1.size() << std::endl;
		std::cout << myvector1.capacity() << std::endl;
		myvector1.clear();
		std::cout << myvector1.size() << std::endl;
		std::cout << myvector1.capacity() << std::endl;
		myvector1.push_back (1101);
		myvector1.push_back (2202);
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector1.size(); i++)
			std::cout << ' ' << myvector1[i];
		std::cout << '\n';
    }
    {
        std::cout << "~~~~~~~~~~ Insert elements ~~~~~~~~~~" << std::endl;
		ecayir::Vector<int> myvector1(3, 100);
		std::cout << "myvector size : " << myvector1.size() << std::endl;
		std::cout << "myvector capacity: " << myvector1.capacity() << std::endl;
		ecayir::Vector<int>::iterator it1;
		it1 = myvector1.begin();
		it1 = myvector1.insert ( it1, 200 );
		myvector1.insert(it1, 2, 300);
		it1 = myvector1.begin();
		ecayir::Vector<int> anothervector1 (2,400);
		std::cout << "myvector size : " << myvector1.size() << std::endl;
		std::cout << "myvector capacity : " << myvector1.capacity() << std::endl;
		myvector1.insert (it1+2,anothervector1.begin(),anothervector1.end());
		std::cout << "myvector size : " << myvector1.size() << std::endl;
		std::cout << "myvector capacity : " << myvector1.capacity() << std::endl;
		int myarray1 [] = { 501,502,503 };
		myvector1.insert (myvector1.begin(), myarray1, myarray1+3);
		std::cout << "myvector contains:";
		for (it1=myvector1.begin(); it1<myvector1.end(); it1++)
			std::cout << ' ' << *it1;
		std::cout << '\n';
    }
	{
        std::cout << "~~~~~~~~~~ Erase elements ~~~~~~~~~~" << std::endl;
		ecayir::Vector<int> myvector1;
		for (int i=1; i<=10; i++) myvector1.push_back(i);
		std::cout << myvector1.size() << std::endl;
		std::cout << myvector1.capacity() << std::endl;
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector1.size(); ++i)
			std::cout << ' ' << myvector1[i];
		std::cout << std::endl;
		myvector1.erase (myvector1.begin() - 1);
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector1.size(); ++i)
			std::cout << ' ' << myvector1[i];
		std::cout << std::endl;
		myvector1.erase (myvector1.begin(),myvector1.begin()+3);
		std::cout << myvector1.size() << std::endl;
		std::cout << myvector1.capacity() << std::endl;
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector1.size(); ++i)
			std::cout << ' ' << myvector1[i];
		std::cout << std::endl;
	}
	{
        std::cout << "~~~~~~~~~~ Swap content ~~~~~~~~~~" << std::endl;
		ecayir::Vector<int> foo1(3, 100);   // three ints with a value of 100
		ecayir::Vector<int> bar1(5, 200);   // five ints with a value of 200
		std::cout << "Size foo1 before " << foo1.size() << std::endl;
		std::cout << "Capa foo1 before " << foo1.capacity() << std::endl;
		std::cout << "Size bar1 before " << bar1.size() << std::endl;
		std::cout << "Capa bar1 before " << bar1.capacity() << std::endl;
		foo1.swap(bar1);
		std::cout << "Size foo1 after " << foo1.size() << std::endl;
		std::cout << "Capa foo1 after " << foo1.capacity() << std::endl;
		std::cout << "Size bar1 after " << bar1.size() << std::endl;
		std::cout << "Capa bar1 after " << bar1.capacity() << std::endl;
		std::cout << "foo contains:";
		for (unsigned i=0; i<foo1.size(); i++)
			std::cout << ' ' << foo1[i];
		std::cout << '\n';
		std::cout << "bar contains:";
		for (unsigned i=0; i<bar1.size(); i++)
			std::cout << ' ' << bar1[i];
		std::cout << '\n';
	}
	{
        std::cout << "~~~~~~~~~~ Get allocator~~~~~~~~~~" << std::endl;
		ecayir::Vector<int> myvector;
		int * p;
		unsigned int i;
		p = myvector.get_allocator().allocate(5);
		for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);
		std::cout << "The allocated array contains:";
		for (i=0; i<5; i++) std::cout << ' ' << p[i];
		std::cout << '\n';
		for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p,5);
	}
	{

		ecayir::Vector<int> foo (1,200);
        std::cout << "~~~~~~~~~~ Relational operators for vector ~~~~~~~~~~" << std::endl;
		ecayir::Vector<int> bar (0);
		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}
	{
        std::cout << "~~~~~~~~~~ Exchange contents of vectors ~~~~~~~~~~" << std::endl;
		ecayir::Vector<int> foo (3,100);   // three ints with a value of 100
		ecayir::Vector<int> bar (5,200);   // five ints with a value of 200
		std::cout << "foo contains:";
		for (ecayir::Vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "bar contains:";
		for (ecayir::Vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	{
        std::cout << "~~~~~~~~~~ compare it and const-it ~~~~~~~~~~" << std::endl;
		ecayir::Vector<int> foo (3,100);   // three ints with a value of 100
		ecayir::Vector<int> bar (5,200);   // five ints with a value of 200
		std::cout << "foo contains:";
		for (ecayir::Vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "bar contains:";
		for (ecayir::Vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
}
