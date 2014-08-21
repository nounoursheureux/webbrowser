#include <QtWidgets>
#include <QWebView>
#include <QtPlugin>

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
        void reloadTab();
        void backTab();
        void forwardTab();
        void stopTab();

    private:
        QWebView *web;
        QToolBar *toolbar;
        QAction *quit, *reload, *previous, *next, *addtab, *closetab, *stop;
        QMenu *fileMenu;
        QIcon icon_quit;
        QLineEdit *urlbar;
        QProgressBar *progressbar;
        QTabWidget *tabs;
        QWidget *webPage;
        QVBoxLayout *layout;
        QUrl *url;
        QRegExp *url_regex;
        QNetworkCookieJar *cookie;
};
