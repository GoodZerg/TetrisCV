#include "Game.h"

void Game::drawTetromino(cv::Mat& image, const Tetromino& tetromino) {
    cv::Point pos = tetromino.getPosition();
    auto shape = tetromino.getShape();
    int blockSize = board.getBlockSize();
    cv::Scalar color = tetromino.getColor();

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (shape[y][x]) {
                int fieldX = pos.x + x;
                int fieldY = pos.y + y;

                if (fieldY >= 0) {
                    cv::Point topLeft(fieldX * blockSize, fieldY * blockSize);
                    cv::Point bottomRight(topLeft.x + blockSize, topLeft.y + blockSize);
                    rectangle(image, topLeft, bottomRight, color, cv::FILLED);
                    rectangle(image, topLeft, bottomRight, cv::Scalar(50, 50, 50), 1);
                }
            }
        }
    }
}

Game::Game(int width, int height, int blockSize, int infoSize) :
    board(width, height, blockSize, cv::Scalar(30, 30, 30)),
    score(0), _infoSize(infoSize), gameOver(false),
    randomEngine(std::chrono::system_clock::now().time_since_epoch().count()) {

    colors = {
        cv::Scalar(0, 255, 255), cv::Scalar(255, 255, 0),
        cv::Scalar(128, 0, 128), cv::Scalar(255, 165, 0),
        cv::Scalar(0, 0, 255), cv::Scalar(0, 255, 0),
        cv::Scalar(255, 0, 0)
    };

    currentTetromino = createRandomTetromino();
    nextTetromino = createRandomTetromino();
    currentTetromino->setPosition(cv::Point(width / 2 - 2, -1));
}

Tetromino* Game::createRandomTetromino() {
    std::uniform_int_distribution<int> dist(0, 6);
    return new Tetromino(dist(randomEngine), colors[dist(randomEngine)]);
}

void Game::update() {
    if (gameOver) return;

    cv::Point currentPos = currentTetromino->getPosition();
    currentTetromino->setPosition(cv::Point(currentPos.x, currentPos.y + 1));

    if (board.checkCollision(*currentTetromino)) {
        currentTetromino->setPosition(currentPos);
        board.placeTetromino(*currentTetromino);

        int lines = board.clearLines();
        score += lines * lines * 100;

        delete currentTetromino;
        currentTetromino = nextTetromino;
        nextTetromino = createRandomTetromino();
        currentTetromino->setPosition(cv::Point(board.getWidth() / 2 - 2, -1));

        if (board.checkCollision(*currentTetromino))
            gameOver = true;
    }
}

void Game::handleInput(int key) {
    if (gameOver) return;

    cv::Point currentPos = currentTetromino->getPosition();
    cv::Point newPos = currentPos;

    switch (key) {
    case 'a': newPos.x--; break;
    case 'd': newPos.x++; break;
    case 's': newPos.y++; break;
    case 'w':
        currentTetromino->rotate();
        if (board.checkCollision(*currentTetromino))
            currentTetromino->rotate(), currentTetromino->rotate(), currentTetromino->rotate();
        return;
    }

    currentTetromino->setPosition(newPos);
    if (board.checkCollision(*currentTetromino))
        currentTetromino->setPosition(currentPos);
}

void Game::draw(cv::Mat& image) {
    image.setTo(cv::Scalar(0, 0, 0));
    board.draw(image);
    drawTetromino(image, *currentTetromino);

    // render INFO
    int gameArea = board.getWidth() * board.getBlockSize();
    rectangle(image, cv::Point(gameArea, 0), cv::Point(image.cols, image.rows), cv::Scalar(40, 40, 40), cv::FILLED);
    putText(image, "Score: " + std::to_string(score), 
        cv::Point(gameArea + 20, 40), 
        cv::FONT_HERSHEY_SIMPLEX, 0.7, 
        cv::Scalar(255, 255, 255), 2);

    putText(image, "Next:", 
        cv::Point(gameArea + 20, 100), 
        cv::FONT_HERSHEY_SIMPLEX, 0.7, 
        cv::Scalar(255, 255, 255), 2);

    // render next TETROMINO
    int previewSize = board.getBlockSize() * 4;
    int startX = gameArea + (_infoSize - previewSize) / 2;
    int startY = 120;

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (nextTetromino->getShape()[y][x]) {
                cv::Point topLeft(startX + x * board.getBlockSize(), startY + y * board.getBlockSize());
                cv::Point bottomRight(topLeft.x + board.getBlockSize(), topLeft.y + board.getBlockSize());

                rectangle(image, topLeft, bottomRight, nextTetromino->getColor(), cv::FILLED);
                rectangle(image, topLeft, bottomRight, cv::Scalar(50, 50, 50), 1);
            }
        }
    }

    // GAME OVER
    if (gameOver) {
        std::string text = "GAME OVER";
        cv::Size sz = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 2, 3, 0);
        putText(image, text, cv::Point((image.cols - sz.width) / 2, (image.rows - sz.height) / 2),
            cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 0, 255), 3);
    }
}

bool Game::isGameOver() const { return gameOver; }
