#include <iostream>
#include "cppJSON.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {

	//样例：创建,修改,打印JSON
	cppJSON_list * l = new cppJSON_list();
	l->push_back_cppJSON_element("name", "Jiyu Zhu");
	l->push_back_cppJSON_element("age", 20);
	vector<int> a(3, 100);
	l->push_back_cppJSON_element("scores", a);
	l->print();

	cout << endl << endl << "修改测试:" << endl << endl;
	a[2] = 99;
	l->update_cppJSON_element("scores", a);
	l->push_back_cppJSON_element("rank", 0.01);
	l->print();

	l->delete_cppJSON("age");
	l->print();

	cout  << endl << endl << "套娃测试:" << endl << endl;

	cppJSON_list * l2 = new cppJSON_list();

	l2->push_back_cppJSON_element("IEEE", "Life Fellow");
	vector<string> companies = {"Apple", "Xiaomi"};
	l2->push_back_cppJSON_element("companies", companies);
	string s("Turing Prize");
	l2->push_back_cppJSON_element("Award", s);

	l->push_back_cppJSON_element("Other Info", l2);
	l->push_back_cppJSON_element("age", 70);
	l->push_back_cppJSON_element("alive", true);
	l->print();

	//解析JSON

	cout << endl << endl << "解析JSON测试：" << endl;
	const char *message =
	    "{                              \
	    \"name\":\"mculo   ver666\",   \
	    \"age\": 22,                \
	    \"weight\": 55.5,           \
	    \"address\":                \
	        {                       \
	            \"country\": \"China\",\
	            \"zip-code\": 111111\
	        },                      \
	    \"skill\": \"c++\",\
	    \"student\": false          \
	}";

	const char * m = "  {\"asdf\":true}";

	cppJSON_list *l3 = cppJSON_Parse(message);

	if (l3) {
		l3->print();
	}





	return 0;
}
