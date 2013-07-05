#include <bb/cascades/Application>
#include <bb/system/SystemPrompt>
#include <bb/system/SystemToast>
#include <bb/system/SystemDialog>
//#include <bb/system/SystemUiResult>

#include "app.hpp"

using ::bb::cascades::Application;

Q_DECL_EXPORT int main(int argc, char** argv)
{
	qmlRegisterType<bb::system::SystemPrompt>("bb.system.SystemPrompt", 1, 0, "SystemPrompt");
	qmlRegisterType<bb::system::SystemToast>("bb.system.SystemToast", 1, 0, "SystemToast");
	qmlRegisterType<bb::system::SystemDialog>("bb.system.SystemDialog", 1, 0, "SystemDialog");
//	qmlRegisterType<bb::system::SystemUiResult>("bb.system", 1, 0, "SystemUiResult");

    Application app(argc, argv);

    App mainApp;

    return Application::exec();
}

