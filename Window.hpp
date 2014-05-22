#include <QtWidgets>
#include <QWebView>

class Window : public QMainWindow
{
    Q_OBJECT;

    public:
        Window();
        QWebView* currentTab();

    public slots:
        void loadPage();
        void refreshUrl();
        void newTab();
        void closeTab();

    private:
        QWebView *web;
        QToolBar *toolbar;
        QAction *quit, *reload, *previous, *next, *addtab, *closetab, *stop;
        QMenu *fileMenu;
        QIcon icon_quit;
        QLineEdit *urlbar;
        QProgressBar *progressbar;
        QTabWidget *tabs;
        QWidget *page;
        QVBoxLayout *layout;
        QUrl *url;
        QRegExp *url_regex;
};
