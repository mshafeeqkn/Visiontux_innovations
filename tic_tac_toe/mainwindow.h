#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_tableWidget_cellClicked(int row, int column);
    void Newgame();
    void options();
    void quit();
    void how();


    void on_comboBox1_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    bool rtdwn(int player);
    bool ltdwn(int player);
    bool testCol(int player);
    bool testRow(int player);
    int checkwinner(int player);
    void restart(int);
};

#endif // MAINWINDOW_H
