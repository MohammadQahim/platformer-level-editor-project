#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void selectTile(char tile);
    void onTileClicked(int row, int col);
    void undoTilePlacement();

    void clearLevel();
    void resizeLevel();

    void exportToFile();
    void onUndoClicked();
    bool eventFilter(QObject* obj, QEvent* event);

    struct TileAction {
        int row;
        int col;
        QIcon previousIcon;
        char previousData;
    };

    enum TileType
    {
        Coin     = '*',
        Enemy    = '&',
        Exit     = 'E',
        Player   = '@',
        Spikes   = '^',
        Wall     = '#',
        DarkWall = '=',
        Air      = ' '
    };

    TileType selectedTile;
    QStack<TileAction> undoStack;

    /*
    QGraphicsGridLayout *level;
    */

    QPushButton* createButton(const QIcon &icon, TileType tileType, QHBoxLayout*);
    QPushButton* undoButton;
    QPushButton* clearButton;
    QPushButton* resizeButton;
    QTableWidget *level = nullptr;
    const float iconSize = 24.0f;
};

#endif // MAIN_WINDOW_H
