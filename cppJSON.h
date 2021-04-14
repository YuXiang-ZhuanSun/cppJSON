#include<bits/stdc++.h>
using namespace std;


enum TYPE {
	INT = 0,
	DOUBLE = 1,
	BOOL = 2,
	CHARS = 3,
	STRING = 4,
	JSON_LIST = 5,
	VEC = 6
};

class cppJSON_list;
template<typename T>
TYPE get_type(T v) {

	if (typeid(v) == typeid(bool)) {
		return BOOL;
	} else if (typeid(v) == typeid(double)) {
		return DOUBLE;
	} else if (typeid(v) == typeid(int)) {
		return INT;
	} else if (typeid(v) == typeid(const char *) ) {
		return CHARS;
	} else if (typeid(v) == typeid(string)) {
		return STRING;
	} else if (typeid(v) == typeid(cppJSON_list*)) {
		return JSON_LIST;
	} else {
		return VEC;
	}
}

ostream & operator<<(ostream & os, const string & s) {
	os << '\"' << s.c_str() << '\"';
	return os;
}


template<typename T>
ostream & operator<<(ostream & os, const vector<T> &v) {
	os << '[';
	int size = v.size() - 1;
	for (int i = 0; i < size; i++) {
		os << v[i] << ',';
	}
	os << v[v.size() - 1] << ']';
	return os;
}


class cppJSON {
	public:
		cppJSON* pre;
		cppJSON* next;
		TYPE type;
		string name;


		cppJSON(string s, TYPE t, cppJSON* p = NULL, cppJSON* n = NULL): pre(p), next(n), type(t), name(s) {

		}
		virtual void print() { }
		virtual~cppJSON() { }
};

template<typename T>
class cppJSON_element: public cppJSON {
	public:
		T value;
		cppJSON_element(string s, TYPE t, T v): cppJSON(s, t), value(v) { }
		void print() {
			if (type != JSON_LIST) {
				if (type == CHARS) {
					cout << '\"' << value << '\"';
				} else if (type == BOOL) {
					cout << boolalpha << value;
				} else {
					cout << value;
				}
				if (next) {
					cout << ',' << endl;
				} else {

					cout << endl;
				}
			}
		}
		~cppJSON_element() { }
};

class cppJSON_list {
	public:
		cppJSON *head;
		cppJSON *tail;

		cppJSON_list() {
			head = NULL;
			tail = NULL;
		}
		cppJSON_list(cppJSON *n) {
			head = tail = n;
		}
		
		~cppJSON_list() {
			while(head){
				cppJSON* c=head;
				head=head->next;
				delete c;
			}
		} 

		cppJSON* find(string s) {
			cppJSON* n = head;
			while (n != NULL && n->name != s) {
				n = n->next;
			}
			return n;
		}

		void push_back_cppJSON(cppJSON*n) {
			if (tail == NULL) {
				head = tail = n;
				n->pre = n->next = NULL;
			} else {
				n->pre = tail;
				n->next = NULL;
				tail->next = n;
				tail = n;
			}
		}



		//add
		template<typename T>
		void push_back_cppJSON_element(string s, T v) {
			cppJSON_element<T>* ne = new cppJSON_element<T>(s, get_type(v), v);
			cppJSON* n = ne;
			push_back_cppJSON(n);

		}

		//update
		template<typename T>
		void update_cppJSON_element(string s, T v) {
			cppJSON *n0 = find(s);
			if (!n0) {
				cout << "not found the JSON named " << s << endl;
				return;
			}
			cppJSON_element<T>* ne = new cppJSON_element<T>(s, get_type(v), v);

			cppJSON* n = ne;
			if (n0 == head) {
				head = n;
			}
			if (n0 == tail) {
				tail = n;
			}
			if (n0->pre) {
				n0->pre->next = n;
				n->pre = n0->pre;
			}
			if (n0->next) {
				n0->next->pre = n;
				n->next = n0->next;
			}
			delete n0;
		}

		//delete
		void delete_cppJSON(string s) {
			cppJSON* n = find(s);
			if (!n) {
				cout << "not found the JSON named " << s << endl;
				return ;
			}
			if (!n->pre) {
				head = n->next;
			} else {
				n->pre->next = n->next;
			}
			if (!n->next) {
				tail = n->pre;
			} else {
				n->next->pre = n->pre;
			}
			delete n;
		}


		void print_cppJSON(string s) {
			cppJSON* n = find(s);
			if (!n) {
				cout << "not found the JSON named " << s << endl;
				return ;
			}
			cout << '\"' << n->name << '\"' << ':';
			n->print();
		}


		void print(int level = 0, int islast = 1) {
			int new_islast;
			cppJSON* n = head;
			for (int i = 0; i < level; i++) {
				cout << "    ";
			}
			cout << '{' << endl;
			while (n) {
				for (int i = 0; i < level; i++) {
					cout << "    ";
				}

				cout << n->name << ':';
				if (n->type == JSON_LIST) {
					if (n->next) {
						new_islast = 0;
					}
					cppJSON_element<cppJSON_list*>* ne = dynamic_cast<cppJSON_element<cppJSON_list*>*>(n);
					cout << endl;
					ne->value->print(level + 1, new_islast);
				} else {
					n->print();
				}
				n = n->next;
			}
			for (int i = 0; i < level; i++) {
				cout << "    ";
			}
			cout << '}';
			if (!islast) {
				cout << ',';
			}
			cout << endl;
		}

};

static string skip(const char *s0) {
	string s;
	int i = 0;
	while (s0[i] != '\0') {
		if (s0[i] != ' ' && s0[i] != '\t') {
			s.push_back(s0[i]);
		}
		if (s0[i] == '\"') {
			i++;
			while (s0[i] != '\"') {
				s.push_back(s0[i]);
				i++;
			}
			s.push_back(s0[i]);
		}
		i++;
	}
	return s;
}

double s_to_double(const string s) {
	istringstream iss(s);
	double num;
	iss >> num;
	return num;
}

int s_to_int(const string s) {
	istringstream iss(s);
	int num;
	iss >> num;
	return num;
}



cppJSON_list* parse_str(string s, cppJSON_list* l) {
	unsigned int i = 1;
	while (s[i] != '}') {
		//get name
		int len = 0;
		if (s[i] != '\"') {
			return NULL;
		}
		i++;
		while (s[i + len] != '\"') {
			len++;
		}
		string name = s.substr(i, len);
		i = i + len + 1;
		if (s[i] != ':') {
			return NULL;
		}
		i++;

		//get value
		if (s[i] == '{') {
			len = 1;
			while (s[i + len] != '}') {
				len++;
			}
			cppJSON_list* nl = new cppJSON_list();
			if (!parse_str(s.substr(i, len + 1), nl)) {
				return NULL;
			}
			l->push_back_cppJSON_element(name, nl);
			i = i + len + 1;
		}
		if (s[i] == 'f') {
			if (s.substr(i, 5) == "false") {
				l->push_back_cppJSON_element(name, false);
				i += 5;
			} else {
				return NULL;
			}
		}
		if (s[i] == 't') {

			if (s.substr(i, 4) == "true") {
				l->push_back_cppJSON_element(name, true);
				i += 4;
			} else {
				return NULL;
			}
		}
		if (s[i] <= '9' && s[i] >= '0') {
			len = 1;
			while (s[i + len] <= '9' && s[i + len] >= '0') {
				len++;
			}
			if (s[i + len] == '.') {
				len++;
				while (s[i + len] <= '9' && s[i + len] >= '0') {
					len++;
				}
				double vd = s_to_double(s.substr(i, len));
				l->push_back_cppJSON_element(name, vd);
				i =	i + len;
			} else {
				int vi = s_to_int(s.substr(i, len));
				l->push_back_cppJSON_element(name, vi);
				i = i + len;
			}

		}
		if (s[i] == '\"') {
			len = 1;
			while (s[i + len] != '\"') {
				len++;
			}
			l->push_back_cppJSON_element(name, s.substr(i + 1, len - 1));
			i = i + len + 1;
		}
		if (s[i] == ',') {
			i++;
		} else {
			return l;
		}
	}
	return l;
}

cppJSON_list * cppJSON_Parse(const char *s0) {
	string s = skip(s0);
	if (s[0] == '{') {
		cppJSON_list *l = new cppJSON_list();
		return parse_str(s, l);
	} else {
		return NULL;
	}

}
