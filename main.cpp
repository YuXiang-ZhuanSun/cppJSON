#include <iostream>
#include "cppJSON.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	cppJSON_list * l = new cppJSON_list();
	l->push_back_cppJSON_element("name", "Jiyu Zhu");
	l->push_back_cppJSON_element("age", 20);
	vector<int> a(3, 100);
	l->push_back_cppJSON_element("scores", a);
	l->print();

	cout << endl << endl << "ÐÞ¸Ä²âÊÔ:" << endl << endl;
	a[2] = 99;
	l->update_cppJSON_element("scores", a);
	l->push_back_cppJSON_element("rank", 0.01);
	l->print();

	l->delete_cppJSON("age");
	l->print();

	cout  << endl << endl << "Ì×ÍÞ²âÊÔ:" << endl << endl;

	cppJSON_list * l2 = new cppJSON_list();

	l2->push_back_cppJSON_element("IEEE", "Life Fellow");
	vector<string> companies = {"Apple", "Xiaomi"};
	l2->push_back_cppJSON_element("companies", companies);
	string s("Turing Prize");
	l2->push_back_cppJSON_element("Award", s);

	l->push_back_cppJSON_element("Other Info", l2);
	l->print();









	return 0;
}
