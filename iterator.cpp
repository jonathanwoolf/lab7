#include "iterator.h"

using namespace std;

//Operator Iterator
OperatorIterator::OperatorIterator(Base* ptr) : Iterator(ptr)
{
	this->self_ptr = ptr;
}

void OperatorIterator::first()
{
	if(self_ptr->get_left())
	{
		current_ptr = self_ptr->get_left();
	}
}

void OperatorIterator::next()
{
	if(self_ptr->get_left() == current_ptr)
	{
		current_ptr = self_ptr->get_right();
	}
	else if(current_ptr == self_ptr->get_right())
	{
		current_ptr = NULL;
	}
}

bool OperatorIterator::is_done()
{
	if(current_ptr == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Base* OperatorIterator::current()
{
	return current_ptr;
}
//Unary Iterator
UnaryIterator::UnaryIterator(Base* ptr) : Iterator(ptr)
{
	this->self_ptr = ptr;
}
void UnaryIterator::first()
{
	if(self_ptr->get_left())
	{
		current_ptr = self_ptr->get_left();
	}	
}

void UnaryIterator::next()
{
	if(current_ptr == self_ptr->get_left())
	{
		current_ptr = NULL;	
	}
}

bool UnaryIterator::is_done()
{
	if(current_ptr == NULL)
	{
		return true;
	}
	return false;
}

Base* UnaryIterator::current()
{
	return current_ptr;
}
//Null Iterator
NullIterator::NullIterator(Base* ptr) : Iterator(ptr)
{
	this->self_ptr = ptr;
}

void NullIterator::first()
{}

void NullIterator::next()
{}

bool NullIterator::is_done()
{
	return true;	
}

Base* NullIterator::current()
{
	return NULL;
}

//PreOrder Iterator
PreOrderIterator::PreOrderIterator(Base* ptr) : Iterator(ptr)
{
	this->self_ptr = ptr;
}

void PreOrderIterator::first()
{
	while(iterators.size() > 0)
	{
		iterators.pop();
	}
	Iterator *it = self_ptr->create_iterator();
	it->first();
	iterators.push(it);	
}

void PreOrderIterator::next() 
{
	Iterator *it = iterators.top()->current()->create_iterator();
	it->first();
	iterators.push(it);

	while((iterators.size() > 0) && iterators.top()->is_done())
	{
		iterators.pop();
		if(iterators.empty())
		{
			break;
		}
		iterators.top()->next();		
	}
}

bool PreOrderIterator::is_done()
{
	if(iterators.empty())	
	{
        	return true;
    	}
    	return false;
}

Base* PreOrderIterator::current() 	
{
    	if(!iterators.empty()) 
	{
        	return iterators.top()->current();
    	}
    	return NULL;
}
