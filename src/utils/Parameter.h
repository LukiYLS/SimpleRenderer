#pragma once
#include <memory>
#include <string>
#include <map>
#include "AnyValue.h"
using std::string;
using std::map;
namespace Utils {

	class Parameter {

	public:
		typedef std::shared_ptr<Parameter> ptr;
		void addParameter(const string& name, AnyValue value) { _paras.insert(make_pair(name, value)); }
		AnyValue getValue(const string& name) {
			if (_paras.find(name) != _paras.end())
				return _paras[name];
			else
				return NULL;
		}
	private:
		map<string, AnyValue> _paras;
	};
}