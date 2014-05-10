#include <QtWidgets>
#include <QWebView>

class Window : public QMainWindow
{
    Q_OBJECT;
    public:
        Window();

    public slots:
        void loadPage();
        void refreshUrl(QUrl url);

    private:
        QWebView *web;
        QToolBar *toolbar;
        QAction *quit, *reload, *previous, *next;
        QMenu *fileMenu;
        QIcon icon_quit;
        QLineEdit *urlbar;
        QProgressBar *progressbar;
};
