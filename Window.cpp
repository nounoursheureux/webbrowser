#include "Window.hpp"
#include <iostream>

Window::Window(): QMainWindow() 
{
    toolbar = addToolBar("Action");
    fileMenu = menuBar()->addMenu("&Fichier");
    quit = fileMenu->addAction("&Quitter");
    reload = toolbar->addAction("&Recharger");
    previous = toolbar->addAction("Précédent");
    next = toolbar->addAction("Suivant");
    addtab = toolbar->addAction("Nouvel onglet");
    closetab = toolbar->addAction("Fermer l'onglet");
    icon_quit = QIcon::fromTheme("window-close");
    urlbar = new QLineEdit;
    stop = toolbar->addAction("Stop");
    progressbar = new QProgressBar;
    tabs = new QTabWidget;
    url = new QUrl;
    url_regex = new QRegExp;

    quit->setShortcut(QKeySequence("Ctrl+Q"));
    reload->setShortcut(QKeySequence("Ctrl+R"));
    reload->setIcon(QIcon("icons/reload.png"));
    previous->setShortcut(QKeySequence("Alt+Left"));
    previous->setIcon(QIcon("icons/previous.png"));
    next->setShortcut(QKeySequence("Alt+Right"));
    next->setIcon(QIcon("icons/next.png"));
    addtab->setShortcut(QKeySequence("Ctrl+t"));
    addtab->setIcon(QIcon("icons/addtab.png"));
    closetab->setShortcut(QKeySequence("Ctrl+w"));
    closetab->setIcon(QIcon("icons/closetab.png"));
    stop->setShortcut(QKeySequence("Ctrl+x"));
    stop->setIcon(QIcon("icons/stop.png"));
    toolbar->addWidget(urlbar);
    QMetaObject::invokeMethod(this, "newTab");
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(reload, SIGNAL(triggered()), web, SLOT(reload()));
    connect(previous, SIGNAL(triggered()), web, SLOT(back()));
    connect(next, SIGNAL(triggered()), web, SLOT(forward()));
    connect(stop, SIGNAL(triggered()), web, SLOT(stop()));
    connect(addtab, SIGNAL(triggered()), this, SLOT(newTab()));
    connect(closetab, SIGNAL(triggered()), this, SLOT(closeTab()));
    connect(urlbar, SIGNAL(returnPressed()), this, SLOT(loadPage()));
    connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(refreshUrl()));
    setCentralWidget(tabs);
}

void Window::loadPage()
{
    url->setUrl(urlbar->text());
    url_regex->setPattern(".*\\.\\w{2,4}");
    if (url_regex->exactMatch(url->toString()))
    {
        url->setUrl(url->toString().insert(0,QString("www.")));
    }
    url_regex->setPattern("\\w{2,3}\\..*\\.\\w{2,4}");
    if (url_regex->exactMatch(url->toString())) 
    {
        url->setUrl(url->toString().insert(0,QString("http://")));
    }
    currentTab()->load(*url);
}

void Window::refreshUrl()
{
    urlbar->setText(currentTab()->url().toString());
}

void Window::newTab()
{
    layout = new QVBoxLayout;
    page = new QWidget;
    web = new QWebView;
    layout->addWidget(web);
    page->setLayout(layout);
    tabs->addTab(page, "Test");
    connect(web, SIGNAL(urlChanged(QUrl)), this, SLOT(refreshUrl()));
}

void Window::closeTab()
{
    tabs->removeTab(tabs->currentIndex());
}

QWebView* Window::currentTab()
{
    return tabs->currentWidget()->findChild<QWebView *>();
}
