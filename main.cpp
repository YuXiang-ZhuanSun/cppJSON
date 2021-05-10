#include "cppJSON.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {

	//新建JSON结构 
	cppJSON_list * l = new cppJSON_list();
	l->push_back_cppJSON_element("name", "Jiyu Zhu");
	l->push_back_cppJSON_element("age", 20);
	vector<int> a(3, 100);
	l->push_back_cppJSON_element("scores", a);
	l->print();

	cout << endl << endl << "增删改查:" << endl << endl;
	a[2] = 99;
	l->update_cppJSON_element("scores", a);
	l->push_back_cppJSON_element("rank", 0.01);
	l->print();

	l->delete_cppJSON("age");
	l->print();

	cout  << endl << endl << "嵌套结构:" << endl << endl;

	cppJSON_list * l2 = new cppJSON_list();
	cppJSON_list * l21 = new cppJSON_list();

	l2->push_back_cppJSON_element("IEEE", "Life Fellow");
	vector<string> companies = {"Apple", "Xiaomi"};
	vector<string> universities = {"SJTU", "XJTU"};
	l2->push_back_cppJSON_element("companies", companies);
	string s("Turing Prize");
	l2->push_back_cppJSON_element("award", s);
	l21->push_back_cppJSON_element("universities",universities);
	l21->push_back_cppJSON_element("country","China");
	l2->push_back_cppJSON_element("education",l21); 

	l->push_back_cppJSON_element("other Info", l2);
	l->push_back_cppJSON_element("age", 70);
	l->push_back_cppJSON_element("alive", true);
	l->print();

	//字符串解析JSON

	cout << endl << endl << "解析JSON字符串" << endl;
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

	delete l3;

    cout << endl << endl << "解析多层嵌套JSON字符串，" << endl;
	const char * me = 
		    "{                              \
		    \"name\":\"mculo   ver666\",   \
		    \"age\": 22,                \
		    \"weight\": 55.5,           \
		    \"address\":                \
		        {                       \
		            \"country\": \"China\",\
		            \"zip-code\": 111111,\
		            \"city\":          \
					    {                  \
							\"Shanghai\":1,  \
							\"Beijing\":2    \
						}               \
		        },                      \
		    \"skill\": \"c++\",\
		    \"student\": false          \
		}";

	cppJSON_list *l4 = cppJSON_Parse(me);

	if (l4) {
		l4->print();
	}

	delete l4;
    

	return 0;
}
