// version 1.0
// author Joseph Mbayi
// This is a program that multiplies permutations 
// reference algorithm A from Donald E knuth's art of computer programming pg 166
//  written  20 october 2020
#include"Standardlib.h"
using cycles = std::list<std::pair<char, bool>>; // this will be the list to hold the cycles to be multiplied
// therefore the name cycles
//  A pair will hold the value and the status ,whether its tagged or not 
// a tagged pair will have a true in second variable of the pair
void create_list(cycles *container) { // function  creates a list of permutations to be multiplied
	std::cout << "enter cycles to be multiplied(as a continues string) " << std::endl;
	std::cout << "(abd)(afg) or (123)(789)" << std::endl;
	std::string s; // variable to hold cycles
	std::cin >> s;
	uint8_t left=0, right=0;// this will hold the number of left and right parenthesis
	int8_t count=0;
	for (int i = 0; i< s.size();++i) { // loop through the characters and  create a pair of each and store in a list 
		// of pairs
		if (s[i] == '(') { ++count; ++left; }
		if (s[i] == ')') { --count; ++right; }
		auto p = std::make_pair(s[i], false);
		container->push_back(p);
	}
	if (count < 0) {
		throw std::runtime_error(" left parenthesis missing somewhere");
	}
	if (count > 0) {
		throw std::runtime_error("right parenthesis missing somewhere");
	}
	return;
}
// function prepares the list of characters  for the propagate function 
// this matches algorithm A line A1
void initialize(cycles * container) {
	// loop through the entire list  tagging right parenthesis  and replacing left parenthesis
	char previous=' ';
	for (auto  i= container->begin(); i!=container->end();i++) {
		if (previous == '(') {
			previous = i->first;
		}
		if (i->first == '(') {
			previous = '(';
			i->second = true;
	     }
		if (i->first == ')') {
			i ->first = previous;
			i ->second = true;
		}
	}
	
	return;
} 
// function finds the next  character to be labbeled as the start of the next iteration
// does so by finding untagged elements, the ones where the pair has a false in the second variable
decltype(auto) find_start(cycles::iterator begin,cycles::iterator end) {
	//find untagged element
	// if one is found return a pointer to it
	while (begin != end) {
		if (begin->second == false) {
			return begin;
		}
		 else {
			++begin;
		 }
	}
	// if the entire loop has been iterated through  return an iterator to the last 
	// element
	return end;

}
void propagate(cycles* container) {
	// outer while loop looks for the start of a new cycles after the first has been found
	
	while (true) {
		auto start = find_start(container->begin(), container->end());
		if (start == container->end()) { // if the entire list has been tagged return to the calling function
			break; }
		start->second = true;
		// output the left parenthesis and the start value
		std::cout << '(' << start->first;
		auto current = start;
		++current;
		// inner while loop iterates through the list to find all elements of a cycle and returns to
		// the outer while loop to find start of the next cycle
		while (true) {
			auto next = current;
			++next;
			auto Iter = std::find_if(next, container->end(), 
				// lambda expression
				[current](std::pair<char, bool> c) {return (c.first == current->first);	});// proceed to the right untill
			// reaching the end or finding an element equal to current
		//line A5 Algorithm A
			if (Iter == container->end() && current->first != start->first) {
				std::cout << current->first;
				// iterate from the begining again 
				next = container->begin();
				// iterate untill a character equal to current is found and set iter equal to it
				Iter= std::find_if(next, container->end(), 
					[current](std::pair<char, bool> c) {return (c.first == current->first);	});

			}
			// line A5 algorithm A
			 if (Iter == container->end() && current->first == start->first) {
				std::cout << ')';
				break;
			}
			if(Iter!=container->end()) {// if an element equal to current is found it is tagged 
				// current is set to the element that follows it
				Iter->second = true;
				current = Iter;
				++current;
			}
		}
	}
	return;
}

int main() 
try{
	cycles l;// cycles defined on line 7
	create_list(&l); // create the list to be 
	initialize(&l);
	propagate(&l);
	return 0;
}
catch (std::exception& e) {
	std::cerr << e.what() << std::endl;
	return 1;
}
