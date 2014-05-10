#include "Window.hpp"

Window::Window(): QMainWindow() 
{
    web = new QWebView;
    toolbar = addToolBar("Action");
    fileMenu = menuBar()->addMenu("&Fichier");
    quit = fileMenu->addAction("&Quitter");
    icon_quit = QIcon::fromTheme("window-close");
    urlbar = new QLineEdit;
    QUrl url;

    quit->setShortcut(QKeySequence("Ctrl+Q"));
    quit->setIcon(icon_quit);
    fileMenu->addAction(quit);
    toolbar->addAction(quit);
    toolbar->addWidget(urlbar);
    web->load(QUrl("http://www.wilhem.org"));
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(urlbar, SIGNAL(returnPressed()), this, SLOT(loadPage()));
    setCentralWidget(web);
}

void Window::loadPage()
{
    url.setUrl(urlbar->text());
    web->load(url);
}

