#include <iostream>
#include <cmath>

struct Circle {
    float x, y;   // 円の中心座標
    float radius; // 円の半径
};

bool checkCollision(const Circle& circle1, const Circle& circle2) {
    // 2つの円の中心座標の差分を計算
    float dx = circle2.x - circle1.x;
    float dy = circle2.y - circle1.y;

    // 2つの円の中心座標の距離を計算
    float distance = std::sqrt(dx * dx + dy * dy);

    // 2つの円の半径の和を計算
    float radiusSum = circle1.radius + circle2.radius;

    // 2つの円の距離が半径の和より小さい場合、当たり判定が成立する
    if (distance < radiusSum) {
        return true; // 当たり判定成立
    }

    return false;    // 当たり判定不成立
}

int main() {
    // 円の情報を設定
    Circle circle1;
    circle1.x = 0.0f;
    circle1.y = 0.0f;
    circle1.radius = 1.0f;

    Circle circle2;
    circle2.x = 2.0f;
    circle2.y = 2.0f;
    circle2.radius = 1.5f;

    // 当たり判定を実行
    if (checkCollision(circle1, circle2)) {
        std::cout << "Collision detected!" << std::endl;
    }
    else {
        std::cout << "No collision." << std::endl;
    }

    return 0;
}