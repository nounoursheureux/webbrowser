#include "Window.hpp"

Window::Window(): QMainWindow() 
{
    web = new QWebView;
    toolbar = addToolBar("Action");
    fileMenu = menuBar()->addMenu("&Fichier");
    quit = fileMenu->addAction("&Quitter");
    reload = toolbar->addAction("&Recharger");
    previous = toolbar->addAction("Précédent");
    next = toolbar->addAction("Suivant");
    icon_quit = QIcon::fromTheme("window-close");
    urlbar = new QLineEdit;
    progressbar = new QProgressBar;

    quit->setShortcut(QKeySequence("Ctrl+Q"));
    quit->setIcon(icon_quit);
    reload->setShortcut(QKeySequence("Ctrl+R"));
    previous->setShortcut(QKeySequence("Alt+Left"));
    next->setShortcut(QKeySequence("Alt+Right"));
    toolbar->addWidget(urlbar);
    web->load(QUrl("http://www.wilhem.org"));
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(reload, SIGNAL(triggered()), web, SLOT(reload()));
    connect(previous, SIGNAL(triggered()), web, SLOT(back()));
    connect(next, SIGNAL(triggered()), web, SLOT(forward()));
    connect(urlbar, SIGNAL(returnPressed()), this, SLOT(loadPage()));
    connect(web, SIGNAL(urlChanged(QUrl)), this, SLOT(refreshUrl(QUrl)));
    setCentralWidget(web);
}

void Window::loadPage()
{
    web->load(urlbar->text());
}

void Window::refreshUrl(QUrl url)
{
    urlbar->setText(url.toString());
}
