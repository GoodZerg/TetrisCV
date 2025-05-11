#include "Game.h"

constexpr int BLOCK_SIZE = 30; 
constexpr int FIELD_WIDTH = 10;
constexpr int FIELD_HEIGHT = 20;
constexpr int INFO_AREA = 200;

int main() {
    int windowWidth = FIELD_WIDTH * BLOCK_SIZE + INFO_AREA;
    int windowHeight = FIELD_HEIGHT * BLOCK_SIZE;

    cv::namedWindow("Tetris", cv::WINDOW_AUTOSIZE);
    cv::resizeWindow("Tetris", windowWidth, windowHeight);

    Game game(FIELD_WIDTH, FIELD_HEIGHT, BLOCK_SIZE, INFO_AREA);
    cv::Mat gameImage(windowHeight, windowWidth, CV_8UC3);

    auto lastUpdate = std::chrono::steady_clock::now();
    while (true) {
        int key = cv::waitKey(30);
        if (key == 27) break; // ESC

        if (!game.isGameOver()) {
            game.handleInput(key);
        } else if (key == 'r') {
            game = Game(FIELD_WIDTH, FIELD_HEIGHT, BLOCK_SIZE, INFO_AREA);
        }


        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count() > 500) {
            game.update();
            lastUpdate = now;
        }


        gameImage.setTo(cv::Scalar(0, 0, 0));
        game.draw(gameImage);
        imshow("Tetris", gameImage);
    }

    return 0;
}