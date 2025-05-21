#include "main_window.h"
#include "utilities.h"
#include "QtWidgets"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), selectedTile(TileType::Air)
{

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setWindowTitle("Platformer Level Editor");

    setFocusPolicy(Qt::StrongFocus);
    centralWidget->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    level = new QTableWidget(10, 10);

    level->verticalHeader()->setDefaultSectionSize(24);
    level->horizontalHeader()->setDefaultSectionSize(24);

    level->verticalHeader()->setMinimumSectionSize(24);
    level->horizontalHeader()->setMinimumSectionSize(24);

    level->verticalHeader()->setMaximumSectionSize(24);
    level->horizontalHeader()->setMaximumSectionSize(24);

    level->verticalHeader()->hide();
    level->horizontalHeader()->hide();

    level->setEditTriggers(QAbstractItemView::NoEditTriggers);
    level->setSelectionMode(QAbstractItemView::NoSelection);
    level->setSelectionBehavior(QAbstractItemView::SelectItems);

    connect(level, &QTableWidget::cellClicked, this, &MainWindow::onTileClicked);

    mainLayout->addWidget(level);

    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* airButton = createButton(QIcon(), Air, buttonLayout);
    QPushButton* wallButton = createButton(QIcon("data/sprites/wall.png"), Wall, buttonLayout);
    QPushButton* wallDarkButton = createButton(QIcon("data/sprites/wall_dark.png"), DarkWall, buttonLayout);
    QPushButton* coinButton = createButton(QIcon("data/sprites/coin.png"), Coin, buttonLayout);
    QPushButton* playerButton = createButton(QIcon("data/sprites/player.png"), Player, buttonLayout);
    QPushButton* enemyButton = createButton(QIcon("data/sprites/enemy.png"), Enemy, buttonLayout);
    QPushButton* spikesButton = createButton(QIcon("data/sprites/spikes.png"), Spikes, buttonLayout);
    QPushButton* exitButton = createButton(QIcon("data/sprites/exit.png"), Exit, buttonLayout);

    mainLayout->addLayout(buttonLayout);

    centralWidget->show();
}


MainWindow::~MainWindow() { }

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // TODO

    QMainWindow::keyPressEvent(event);
}

void MainWindow::selectTile(char tile)
{
    switch (tile) {
        case '*': selectedTile = Coin; break;
        case '&': selectedTile = Enemy; break;
        case 'E': selectedTile = Exit; break;
        case '@': selectedTile = Player; break;
        case '^': selectedTile = Spikes; break;
        case '#': selectedTile = Wall; break;
        case '=': selectedTile = DarkWall; break;
        case '-': selectedTile = Air; break;
    }
}

void MainWindow::onTileClicked(int row, int column)
{
    QTableWidgetItem* item = level->item(row, column);

    if (item == nullptr) {
        item = new QTableWidgetItem();
        level->setItem(row, column, item);
    }

    QIcon icon;

    switch (selectedTile) {
        case Coin: icon = QIcon("data/sprites/coin.png"); break;
        case Enemy: icon = QIcon("data/sprites/enemy.png"); break;
        case Exit: icon = QIcon("data/sprites/exit.png"); break;
        case Player: icon = QIcon("data/sprites/player.png"); break;
        case Spikes: icon = QIcon("data/sprites/spikes.png"); break;
        case Wall: icon = QIcon("data/sprites/wall.png"); break;
        case DarkWall: icon = QIcon("data/sprites/wall_dark.png"); break;
    }

    item->setIcon(icon);
    char data = '-';

    switch (selectedTile) {
        case Coin: data = '*'; break;
        case Enemy: data = '&'; break;
        case Exit: data = 'E'; break;
        case Player: data = '@'; break;
        case Spikes: data = '^'; break;
        case Wall: data = '#'; break;
        case DarkWall: data = '='; break;
    }

    item->setData(Qt::UserRole, data);
}

void MainWindow::undoTilePlacement()
{
    if (undoStack.isEmpty()) return;
    TileAction action = undoStack.pop();

    // TODO
}

QPushButton* MainWindow::createButton(const QIcon &icon, TileType tileType, QHBoxLayout* layout) {
    QPushButton *button = new QPushButton();
    button->setFixedSize(32, 32);
    button->setIcon(icon);
    connect(button, &QPushButton::clicked, this, [this, tileType]() {
        selectTile(static_cast<char>(tileType));
    });
    layout->addWidget(button);
    return button;
}

void MainWindow::clearLevel()
{
    // TODO
}

void MainWindow::resizeLevel()
{
    QDialog resizeDialog(this);
    // TODO
    if (resizeDialog.exec() == QDialog::Accepted) {
        // TODO
    }
}

void MainWindow::exportToFile()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Export Level",
        "",
        "RLL Files (*.rll);;All Files (*)"
    );

    QFile file(filePath);
    QTextStream out(&file);

    // TODO

    /* Snippets:
     * std::vector<char> data(rows * cols, '-');
     * char tile = item->data(Qt::UserRole).toChar().toLatin1();
     * encrypt(rows, cols, data.data(), output);
     * out << output;
     */

    file.close();
}
