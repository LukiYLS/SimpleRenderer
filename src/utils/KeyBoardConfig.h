#pragma once
#include <string>
#include <map>
using std::string;
using std::map;
namespace Utils {
	class KeyBoardConfig
	{
	public:
		typedef map<string, int> container_type;
		container_type	default_keyboard_browse;
		container_type _key_map;

		KeyBoardConfig() {};
		KeyBoardConfig(configuration_service* configuration_service_);
		~KeyBoardConfig(void);

		bool load();
		int get_keycode_by_browse(string browse_);
		int get_keycode_by_keychar(string keychar_);

		string get_browse_by_keycode(int key_code);
	private:
		container_type _config_map;
		//	container_type _key_map;
		configuration_service* _configuration_service;
	};
}