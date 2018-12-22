#include "CamerControl.h"
#include "InputDefine.h"
#include <cstring>
namespace Utils
{
	CameraControl::CameraControl(Camera* camera)
	{
		_camera = (Camera::ptr)camera;
		
		_last_x_pos = 0;
		_last_y_pos = 0;

		_lb_pressing = false;
		_mb_pressing = false;
		_rb_pressing = false;
	}
	void CameraControl::receive(Event::ptr event)
	{		
		if (strcmp(event->getName(), "mouse.event") == 0)
		{
			mouse_event_vector events = event->getValue("mouse.event");
			for (unsigned int i = 0; i < events._event_num; ++i)
			{
				mouse_event mouse_work = events._mouse_events[i];

				switch (mouse_work.mouse_status)
				{
				case LB_DOWN:
				{
					_lb_pressing = true;
					break;
				}
				case LB_UP:
				{
					_lb_pressing = false;
					break;
				}
				case M_WHEEL:
				{
					double value = mouse_work.wheelvalue * _camera->getPosition().length()*0.001;

					_camera->translateOnZ(value);
				}
				case RB_DOWN:
				{
					_rb_pressing = true;
					break;
				}
				case RB_UP:
				{
					_rb_pressing = false;
					break;
				}
				case M_MOVE:
				{
					if (_lb_pressing)
					{
						int dx = mouse_work.xpos - _last_x_pos;
						int dy = mouse_work.ypos - _last_y_pos;
						_camera->rotateOnAxisFixedPosition(Vector3D(1.0,0.0,0.0),dy*0.001);
						_camera->rotateOnAxisFixedPosition(Vector3D(0.0,1.0,0.0),-dx*0.001);
						//_camera->yaw(-dy*0.001);
						//_camera->pitch(dx*0.001);
					}
					else if (_mb_pressing)
					{
						//int dx = mouse_work.xpos - _last_x_pos;

					}
					else if (_rb_pressing)
					{
						int dx = mouse_work.xpos - _last_x_pos;
						int dy = mouse_work.ypos - _last_y_pos;
						_camera->roll(dx * 0.001);
						_camera->yaw(dy*0.001);
					}
					break;
				}
					
				}
				_last_x_pos = mouse_work.xpos;
				_last_y_pos = mouse_work.ypos;
			}
		}
		else if (strcmp(event->getName(), "keyboard.event") == 0)
		{
			char key = event->getValue("keyboard.event");
			switch (key)
			{
			case 'W':
			{
				_camera->translateOnAxis(_camera->getDirection(), 0.0001*_camera->getPosition().length());
				break;
			}
			case 'A':
			{
				_camera->translateOnAxis(_camera->getRight(), -0.0001*_camera->getPosition().length());
				break;
			}
			case 'S':
			{
				_camera->translateOnAxis(_camera->getDirection(), -0.0001*_camera->getPosition().length());
				break;
			}
			case 'D':
			{
				_camera->translateOnAxis(_camera->getRight(), 0.0001*_camera->getPosition().length());
				break;
			}
			default:
				break;
			}
		}
	}
}