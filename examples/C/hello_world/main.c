/*
    WebUI Library 2.x
    C99 Example

    http://webui.me
    https://github.com/alifcommunity/webui

    Licensed under GNU General Public License v3.0.
    Copyright (C)2022 Hassan DRAGA <https://github.com/hassandraga>.
*/

#include "webui.h"

// Check the password function
void check_the_password(webui_event_t* e) {

	// This function get called every time the user click on "MyButton1"

	webui_script_t js = {
		.script = " return document.getElementById(\"MyInput\").value; ",
		.timeout = 3
	};

    // Run the JavaScript on the UI (Web Browser)
	webui_script(e->window, &js);

	// Check if there is any JavaScript error
	if(js.result.error) {

		printf("JavaScript Error: %s\n", js.result.data);
		return;
	}

	// Get the password
	const char* password = js.result.data;
	printf("Password: %s\n", password);

	// Check the password
	if(strcmp(password, "123456") == 0) {

		// Correct password
		js.script = "alert('Good. Password is correct.')";
		webui_script(e->window, &js);
	}
	else {

		// Wrong password
		js.script = "alert('Sorry. Wrong password.')";
		webui_script(e->window, &js);
	}

	// Free data resources
	webui_free_script(&js);
}

void close_the_application(webui_event_t* e){

	// Close all opened windows
	webui_exit();
}

int main() {

	// HTML
	const char* my_html = "<!DOCTYPE html>"
	"<html><head><title>WebUI 2 - C99 Example</title>"
	"<style>body{color: white; background: #0F2027;"
	"background: -webkit-linear-gradient(to right, #2C5364, #203A43, #0F2027);"
	"background: linear-gradient(to right, #2C5364, #203A43, #0F2027);"
	"text-align:center; font-size: 18px; font-family: sans-serif;}</style></head><body>"
	"<h1>WebUI 2 - C99 Example</h1><br>"
	"<input type=\"password\" id=\"MyInput\"><br><br>"
	"<button id=\"MyButton1\">Check Password</button> - <button id=\"MyButton2\">Exit</button>"
	"</body></html>";

	// Create a window
    webui_window_t* my_window = webui_new_window();
    
	// Bind HTML elements with functions
	webui_bind(my_window, "MyButton1", check_the_password);
	webui_bind(my_window, "MyButton2", close_the_application);

    // Show the window
	if(!webui_show(my_window, my_html, webui.browser.chrome))	// Run the window on Chrome
		webui_show(my_window, my_html, webui.browser.any);		// If not, run on any other installed web browser

    // Wait until all windows get closed
	webui_wait();

    return 0;
}

#if defined(_MSC_VER)
	int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
		main();
	}
#endif
