#include <QtWidgets>
#include <QWebView>

class Window : public QMainWindow
{
    Q_OBJECT;
    public:
        Window();

    public slots:
        void loadPage();

    private:
        QWebView *web;
        QToolBar *toolbar;
        QAction *quit;
        QMenu *fileMenu;
        QIcon icon_quit;
        QLineEdit *urlbar;
        QUrl url;
};
