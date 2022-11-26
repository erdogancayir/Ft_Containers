#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template < class f, class s >
	struct pair
	{
		typedef f   first_type;
		typedef s   second_type;

		first_type	first;
		second_type	second;

		explicit pair() : first(), second() {}
		template < class T1, class T2 >
		pair(const pair<T1, T2> &oth) : first(oth.first), second(oth.second) {}
		pair(const first_type &x, const second_type &y) : first(x), second(y) {}

		template < class T1, class T2>
		pair<T1,T2>	&operator=(class<T1, T2> &oth)
		{
			if (&oth != this)
			{
				this->first = oth.first;
				this->second = oth.second;
			}
			return (*this);
		};

	};
	template < class T1, class T2>
	pair<T1, T2>	make_pair(T1 x, T2 y) {return (pair<T1,T2>(x,y)); };
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& first, const pair<T1,T2>& sec) { return (first.first == sec.first && first.second == sec.second); };
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& first, const pair<T1,T2>& sec) { return !(first == sec); };
	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& first, const pair<T1,T2>& sec) { return first.first<sec.first || (!(sec.first<first.first) && first.second<sec.second); };
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& first, const pair<T1,T2>& sec) { return !(sec<first); };
	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& first, const pair<T1,T2>& sec) { return sec<first; };
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& first, const pair<T1,T2>& sec) { return !(first<sec); };
}


#endif