#include "Window.hpp"

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
    progressbar = new QProgressBar;
    tabs = new QTabWidget;

    quit->setShortcut(QKeySequence("Ctrl+Q"));
    quit->setIcon(icon_quit);
    reload->setShortcut(QKeySequence("Ctrl+R"));
    previous->setShortcut(QKeySequence("Alt+Left"));
    next->setShortcut(QKeySequence("Alt+Right"));
    addtab->setShortcut(QKeySequence("Ctrl+t"));
    closetab->setShortcut(QKeySequence("Ctrl+w"));
    toolbar->addWidget(urlbar);
    QMetaObject::invokeMethod(this, "newTab");
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(reload, SIGNAL(triggered()), web, SLOT(reload()));
    connect(previous, SIGNAL(triggered()), web, SLOT(back()));
    connect(next, SIGNAL(triggered()), web, SLOT(forward()));
    connect(addtab, SIGNAL(triggered()), this, SLOT(newTab()));
    connect(closetab, SIGNAL(triggered()), this, SLOT(closeTab()));
    connect(urlbar, SIGNAL(returnPressed()), this, SLOT(loadPage()));
    connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(refreshUrl()));
    setCentralWidget(tabs);
}

void Window::loadPage()
{
    currentTab()->load(urlbar->text());
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
