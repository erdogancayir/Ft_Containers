#include "../vector/vector.hpp"

namespace ft
{
    template <class Type, class Container = vector<Type> >
    class stack
    {
        public:
            typedef Type                            value_type;
            typedef Container                       container_type;
            typedef container_type::reference       reference; 
            typedef container_type::const_reference const_reference;
            typedef container_type::size_type       size_type;
        protected:
            container_type c;
        
        public:
            explicit    stack(const container_type &c_type = container_type()) : c(c_type) {}

        public:
            bool    			empty() 						{ return (!this->c.size()); };
            size_type   		size()							{ return (this->c.size()); };
			void				push( const value_type& value )	{ this->c.push_back(value); };
			void				pop()							{ this->c.pop_back(); };
			value_type			&top()							{ return (this->c.back()); };
			const value_type	&top() const					{ return (this->c.back()); };

        protected:
			template <class _T, class _C>
				friend bool operator== (const stack<_T ,_C>& lhs, const stack<_T ,_C>& rhs);
			template <class _T, class _C>
				friend bool operator!= (const stack<_T ,_C>& lhs, const stack<_T ,_C>& rhs);
			template <class _T, class _C>
				friend bool operator<  (const stack<_T ,_C>& lhs, const stack<_T ,_C>& rhs);
			template <class _T, class _C>
				friend bool operator<= (const stack<_T ,_C>& lhs, const stack<_T ,_C>& rhs);
			template <class _T, class _C>
				friend bool operator>  (const stack<_T ,_C>& lhs, const stack<_T ,_C>& rhs);
			template <class _T, class _C>
				friend bool operator>= (const stack<_T ,_C>& lhs, const stack<_T ,_C>& rhs);
    };

    template <class _T, class _C>
		bool operator== (const stack<_T ,_C>& lhs, const stack<_T ,_C>& rhs) { return (lhs.c == rhs.c); };
	template <class _T, class _C>
		bool operator!= (const stack<_T ,_C>& lhs, const stack<_T ,_C>& rhs) { return (lhs.c != rhs.c); };
	template <class _T, class _C>
		bool operator<  (const stack<_T ,_C>& lhs, const stack<_T ,_C>& rhs) { return (lhs.c < rhs.c); };
	template <class _T, class _C>
		bool operator<= (const stack<_T ,_C>& lhs, const stack<_T ,_C>& rhs) { return (lhs.c <= rhs.c); };
	template <class _T, class _C>
		bool operator>  (const stack<_T ,_C>& lhs, const stack<_T ,_C>& rhs) { return (lhs.c > rhs.c); };
	template <class _T, class _C>
		bool operator>= (const stack<_T ,_C>& lhs, const stack<_T ,_C>& rhs) { return (lhs.c >= rhs.c); };
};