#include "Event.h"


namespace Utils
{
	void Event::setName(const char* name)
	{
		_name = name;
	}
	const char* Event::getName()
	{
		return _name.c_str();
	}

	AnyValue Event::getValue(const char* key_)
	{
		return _event_value_map[key_];
	}

	void Event::setValue(const char* key_, AnyValue value_)
	{
		_event_value_map[key_] = value_;
	}

	//==================================================================

	EventManager* EventManager::m_Inst(0);
	EventManager* EventManager::Inst() {
		if (!m_Inst)
			m_Inst = new EventManager();
		return m_Inst;
	}

	Event::ptr EventManager::createEvent()
	{
		return std::make_shared<Event>();
	}

	void EventManager::sendEvent(Event::ptr event)
	{
		event_receiver_map_type::iterator it = _event_receiver_map.find(event->getName());
		if (it == _event_receiver_map.end())
		{
			return;
		}

		for (event_list_type::iterator it_ = it->second.begin(); it_ != it->second.end(); it_++)
		{
			(*it_)->receive(event);
		}
	}

	void EventManager::postEvent(Event::ptr event)
	{
		sendEvent(event);
	}

	void EventManager::registerReceiver(const char* event_name, EventReceiver::ptr event_receiver)
	{
		unRegisterReceiver(event_name, event_receiver);
		_event_receiver_map[event_name].push_back(event_receiver);
	}

	void EventManager::unRegisterReceiver(const char* event_name, EventReceiver::ptr event_receiver)
	{
		event_receiver_map_type::iterator it = _event_receiver_map.find(event_name);
		if (it == _event_receiver_map.end())
		{
			return;
		}

		it->second.remove(event_receiver);

		if (it->second.size() == 0)
		{
			_event_receiver_map.erase(it);
		}
	}

}