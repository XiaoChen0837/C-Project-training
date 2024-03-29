#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
public:
    Controller() : speed(200), key(1), score(0) {}
    void Game();
    void Start();
    void Slect();
    void DrawGame();
    int PlayGame();
    int Menu();
    void UpdateScore(const int&);
    void RewriteScore();
    int GameOver();

private:
    int speed;
    int key;
    int score;
};

#endif // CONTROLLER_H
