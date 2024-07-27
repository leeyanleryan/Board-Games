// #include <QApplication>
// #include <QGraphicsView>
// #include <QGraphicsScene>
// #include <QGraphicsRectItem>
// #include <QTimer>

// class Game : public QGraphicsView {
// public:
//     Game() {
//         // Create a scene
//         QGraphicsScene *scene = new QGraphicsScene();
//         setScene(scene);

//         // Create a player item
//         QGraphicsRectItem *player = new QGraphicsRectItem(0, 0, 50, 50);
//         scene->addItem(player);
//         player->setPos(250, 250);

//         // Set up a timer to move the player
//         QTimer *timer = new QTimer();
//         connect(timer, &QTimer::timeout, [player]() {
//             player->moveBy(5, 0);
//         });
//         timer->start(100);
//     }
// };

// int main(int argc, char *argv[]) {
    // QApplication app(argc, argv);

    // Game game;
    // game.show();

    // return app.exec();
    // cout << "Hello";
// }

#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}