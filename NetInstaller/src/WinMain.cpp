#include "../header/WinMain.h"
#include "../header/Controller.h"

/* PRIVATE */

WinMain::WinMain() {
	this->controls = new ViewControls();
}

LRESULT WinMain::onCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	//Inicializa os Controls para que sejam renderizados na janela
	if(this->controls != NULL) this->controls->initObjects(hWnd, hInst);
	Controller::getInstance()->onReady(hWnd);

	return 0;
}

LRESULT WinMain::onCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	int controlId = LOWORD(wParam);
	int wmEvent = HIWORD(wParam);

	//Dispara o evento no Control especificado
	if (this->controls != NULL) this->controls->fireEvent(controlId, wmEvent, wParam, lParam);

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT WinMain::onPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	EndPaint(hWnd, &ps);

	return 0;
}

/* PUBLIC */

ControlsStore *WinMain::getControlsStore() {
	return this->controls;
}

int WinMain::tMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	//Inicializando propriedades
	this->hInst = hInstance;
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_NETINSTALLER, szWindowClass, MAX_LOADSTRING);
	registerClass(hInstance);

	width = INIT_WIDTH;
	height = INIT_HEIGHT;

	// Perform application initialization:
	if (!initWin32Instance(hInstance, nCmdShow)) {
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NETINSTALLER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

ATOM WinMain::registerClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = _WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NETINSTALLER));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	//TODO: Se precisar de menu, bolar algum mecanismo para manipular-lo
	//wcex.lpszMenuName = MAKEINTRESOURCE(IDC_NETINSTALLER);
	wcex.lpszMenuName = NULL;

	return RegisterClassEx(&wcex);
}

BOOL WinMain::initWin32Instance(HINSTANCE hInstance, int nCmdShow) {
	
	hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd) {
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WinMain::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

		case WM_CREATE:
			onCreate(hWnd, message, wParam, lParam);
			break;

		case WM_COMMAND:
			onCommand(hWnd, message, wParam, lParam);
			break;

		case WM_PAINT:
			onPaint(hWnd, message, wParam, lParam);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:	
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HINSTANCE WinMain::getHandleInstance() {
	return hInst;
}

HWND WinMain::getWindowHandle() {
	return hWnd;
}

std::string WinMain::loadString(int resourceId){
	TCHAR str[MAX_LOADSTRING] = { 0 };
	LoadString(this->hInst, resourceId, str, MAX_LOADSTRING);
	return Conversions::TCHARToString(str);
}