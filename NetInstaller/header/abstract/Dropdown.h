#if !defined _USERCONTROL_DROPDOWN

	#define _USERCONTROL_DROPDOWN
	#include "Control.h"

	class Dropdown: public Control{

		public:

			static const int EVENT_CHANGE = 1;
			static const int EVENT_BLUR = 4;
			static const int EVENT_FOCUS = 3;
			static const int EVENT_EXPAND = 7;
			static const int EVENT_COLLAPSE = 8;

			Dropdown();

			virtual void onChange();
			virtual void onBlur();
			virtual void onFocus();
			virtual void onExpand();
			virtual void onCollapse();

			LRESULT onCreate(HWND parent, HINSTANCE hInst);
			LRESULT onCommand(int index, int wmEvent, WPARAM wParam, LPARAM lParam);

			int getSelectedIndex();
			void setValue(int index);
			int addItem(std::string label);
			int addItem(char *label);
			void toggleEnabled();
			int count();
			void reset();
	};

#endif
