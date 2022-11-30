#include <vector>
#include <map>
#include <stack>
#include <exception>
#include <utility>
#include "vector/vector.hpp"
#include "map/map.hpp"
#include "stack/stack.hpp"

#define nextLine std::cout << "█▄░█ █▀▀ ▀▄▀ ▀█▀   ▀█▀ █▀▀ █▀ ▀█▀   █▀▀ ▄▀█ █▀ █▀▀\n█░▀█ ██▄ █░█ ░█░   ░█░ ██▄ ▄█ ░█░   █▄▄ █▀█ ▄█ ██▄\n\te̳c̳a̳y̳i̳r̳\n" << std::endl

#ifndef Kocaeli
#define Kocaeli ft
#endif

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

int main()
{
	{
		Kocaeli::map<char,int> first;

		first['a']=10;
		first['b']=30;
		first['c']=50;
		first['d']=70;

		Kocaeli::map<char,int> second (first.begin(),first.end());

		Kocaeli::map<char,int> third (second);

		Kocaeli::map<char,int,classcomp> fourth;                 // class as Compare

		bool(*fn_pt)(char,char) = fncomp;
		Kocaeli::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	}	
	nextLine;
	{
		Kocaeli::map<char, int> first;
		Kocaeli::map<char, int> second;
		first['x'] = 8;
		first['y'] = 16;
		first['z'] = 32;
		second = first;				  // second now contains 3 ints
		first = Kocaeli::map<char, int>(); // and first is now empty
		std::cout << "Size of first: " << first.size() << '\n';
		std::cout << "Size of second: " << second.size() << '\n';
	}
	nextLine;
	{
		Kocaeli::map<char, int> mymap;
		mymap['b'] = 100;
		mymap['a'] = 200;
		mymap['c'] = 300;
		// show content:
		for (Kocaeli::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "mymap.size() is " << mymap.size() << '\n';
	}
	nextLine;
	{
		Kocaeli::map<char, std::string> mymap;
		mymap['a'] = "an element";
		mymap['b'] = "another element";
		mymap['c'] = mymap['b'];
		std::cout << "mymap['a'] is " << mymap['a'] << '\n';
		std::cout << "mymap['b'] is " << mymap['b'] << '\n';
		std::cout << "mymap['c'] is " << mymap['c'] << '\n';
		std::cout << "mymap['d'] is " << mymap['d'] << '\n';
		std::cout << "mymap now contains " << mymap.size() << " elements.\n";
		std::cout << "mymap.size() is " << mymap.size() << '\n';
		// mymap.prettyPrint();
	}
	nextLine;
	{
		Kocaeli::map<char, int> mymap;
		// first insert function version (single parameter):
		mymap.insert(Kocaeli::pair<char, int>('a', 100));
		mymap.insert(Kocaeli::pair<char, int>('z', 200));
		Kocaeli::pair<Kocaeli::map<char, int>::iterator, bool> ret;
		ret = mymap.insert(Kocaeli::pair<char, int>('z', 500));
		if (ret.second == false)
		{
			std::cout << "element 'z' already existed";
			std::cout << " with a value of " << ret.first->second << '\n';
		}
		else
		{
			std::cout << "element 'z' created";
			std::cout << " with a value of " << ret.first->second << '\n';
		}
		// second insert function version (with hint position):
		Kocaeli::map<char, int>::iterator it = mymap.begin();
		mymap.insert(it, Kocaeli::pair<char, int>('b', 300)); // max efficiency inserting
		mymap.insert(it, Kocaeli::pair<char, int>('c', 400));
		// third insert function version (range insertion):
		Kocaeli::map<char, int> anothermap;
		anothermap.insert(mymap.begin(), mymap.find('c'));
		std::cout << mymap.size() << std::endl;
		// showing contents:
		std::cout << "mymap contains:\n";
		for (it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "anothermap contains:\n";
		for (it = anothermap.begin(); it != anothermap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		// mymap.prettyPrint();
	}
	nextLine;
	{
		Kocaeli::map<char, int> mymap;
		Kocaeli::map<char, int>::iterator it;
		mymap['a'] = 50;
		mymap['b'] = 100;
		mymap['c'] = 150;
		mymap['d'] = 200;
		// mymap.print();
		it = mymap.find('b');
		if (it != mymap.end())
			mymap.erase(it);
		// mymap.print();
		// print content:
		std::cout << "elements in mymap:" << '\n';
		std::cout << "a => " << mymap.find('a')->second << '\n';
		std::cout << "c => " << mymap.find('c')->second << '\n';
		std::cout << "d => " << mymap.find('d')->second << '\n';
		// std::cout << "d => " << mymap.find('b')->second << '\n';
	}
	nextLine;
	{
		Kocaeli::map<int, int> mymap;
		Kocaeli::map<int, int>::iterator it;
		// insert some values:
		mymap[1] = 10;
		mymap[7] = 20;
		mymap[8] = 30;
		mymap[10] = 40;
		mymap[77] = 50;
		mymap[6] = 60;
		// mymap.print();
		nextLine;
		it = mymap.find(6);
		mymap.erase(it);	// erasing by iterator
		mymap.erase(10);	// erasing by key
		// mymap.print();
		it = mymap.find(8);
		mymap.erase(it, mymap.end()); // erasing by range
		// show content:
		for (it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	nextLine;
	{
		Kocaeli::map<char, int> foo, bar;
		foo['x'] = 100;
		foo['y'] = 200;
		bar['a'] = 11;
		bar['b'] = 22;
		bar['c'] = 33;
		foo.swap(bar);
		std::cout << "foo contains:\n";
		for (Kocaeli::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
		std::cout << "bar contains:\n";
		for (Kocaeli::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	nextLine;
	{
		Kocaeli::map<char, int> mymap;
		Kocaeli::map<char, int>::iterator itlow, itup;
		mymap['a'] = 20;
		mymap['b'] = 40;
		mymap['c'] = 60;
		mymap['d'] = 80;
		mymap['f'] = 100;
		itlow = mymap.lower_bound('f'); // itlow points to b
		itup = mymap.upper_bound('d');	// itup points to e (not d!)

		std::cout << itlow->first << std::endl;
		std::cout << itup->first << std::endl;
		mymap.erase(itlow, itup); // erases [itlow,itup)
		// print content:
		for (Kocaeli::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	nextLine;
	{
		Kocaeli::map<char, int> mymap;
		mymap['a'] = 10;
		mymap['b'] = 20;
		mymap['c'] = 30;
		Kocaeli::pair<Kocaeli::map<char, int>::iterator, Kocaeli::map<char, int>::iterator> ret;
		ret = mymap.equal_range('b');
		std::cout << "lower bound points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << '\n';
		std::cout << "upper bound points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << '\n';
	}
	nextLine;
	{
		int psize;
		Kocaeli::map<char, int> mymap;
		Kocaeli::pair<const char, int> *p;

		// allocate an array of 5 elements using mymap's allocator:
		p = mymap.get_allocator().allocate(5);

		// assign some values to array
		psize = sizeof(Kocaeli::map<char, int>::value_type) * 5;

		std::cout << "The allocated array has a size of " << psize << " bytes.\n";

		mymap.get_allocator().deallocate(p, 5);
	}
	nextLine;
	{
		std::map<char, int> foo, bar;
		foo['a'] = 100;
		foo['b'] = 200;
		bar['a'] = 10;
		bar['z'] = 1000;

		// foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
		if (foo == bar)
			std::cout << "foo and bar are equal\n";
		if (foo != bar)
			std::cout << "foo and bar are not equal\n";
		if (foo < bar)
			std::cout << "foo is less than bar\n";
		if (foo > bar)
			std::cout << "foo is greater than bar\n";
		if (foo <= bar)
			std::cout << "foo is less than or equal to bar\n";
		if (foo >= bar)
			std::cout << "foo is greater than or equal to bar\n";
	}
	nextLine;
	{
		Kocaeli::map<int, int> mp;
		for (int i = 0; i < 5; i++)
		{
			mp.insert(Kocaeli::make_pair(i, i * 2));
		}
		// mp.print();
		Kocaeli::map<int, int>::iterator it = mp.begin();
		mp.insert(Kocaeli::make_pair(-1, 2));
		std::cout << it->first << " " << it->second <<  std::endl;
		// mp.print();
		for (; it != mp.end(); it++)
		{
			std::cout << it->first << " " << it->second << std::endl;
		}
	}
	std::cout << "\e[1;91m===============\n";
	std::cout << "\e[1;91m█▀▄▀█ █▀▀█ █▀▀█ \n█░▀░█ █▄▄█ █░░█ \n▀░░░▀ ▀░░▀ █▀▀▀\necayir\n";
	std::cout << "\e[1;91m===============\n";
}
