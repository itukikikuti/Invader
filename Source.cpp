#include "XLibrary11.hpp"
using namespace XLibrary11;

int MAIN()
{
    const int width = 7;
    const int height = 3;

    Camera camera;
    camera.color = Float4(0.0f, 0.0f, 0.0f, 1.0f);

    Sprite enemy(L"enemy.png");
    enemy.scale = 2.0f;

    Float3 enemyPositions[width][height];
    int enemyLift[width][height];

    Sprite bullet(L"bullet.png");
    bullet.scale = 2.0f;

    Sprite player(L"player.png");
    player.position = Float3(0.0f, -200.0f, 0.0f);
    player.scale = 2.0f;

    Sound hitSound(L"hit.wav");
    Sound shotSound(L"shot.wav");

    App::SetWindowSize(320, 480);

    bool initFlag = true;

    while (App::Refresh())
    {
        camera.Update();

        if (initFlag)
        {
            initFlag = false;

            for (int x = 0; x < width; x++)
            {
                for (int y = 0; y < height; y++)
                {
                    Float3 offset(-width / 2 * 35.0f, 160.0f, 0.0f);
                    enemyPositions[x][y] = Float3(x * 35.0f, y * 20.0f, 0.0f) + offset;
                    enemyLift[x][y] = y + 1;
                }
            }

            bullet.position = Float3(0.0f, App::GetWindowSize().y / 2.0f, 0.0f);
        }

        initFlag = true;

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                if (enemyLift[x][y] <= 0)
                    continue;

                initFlag = false;

                enemyPositions[x][y].y -= 0.2f;
                enemy.position = enemyPositions[x][y];

                if (bullet.position.x > enemy.position.x - 24.0f &&
                    bullet.position.x < enemy.position.x + 24.0f &&
                    bullet.position.y > enemy.position.y - 16.0f &&
                    bullet.position.y < enemy.position.y + 16.0f)
                {
                    bullet.position = Float3(0.0f, App::GetWindowSize().y / 2.0f, 0.0f);
                    enemyLift[x][y]--;
                    hitSound.Play();
                }

                if (enemyLift[x][y] == 3)
                {
                    enemy.color = Float4(1.0f, 0.0f, 0.0f, 1.0f);
                }
                else if (enemyLift[x][y] == 2)
                {
                    enemy.color = Float4(0.0f, 1.0f, 0.0f, 1.0f);
                }
                else if (enemyLift[x][y] == 1)
                {
                    enemy.color = Float4(0.0f, 0.0f, 1.0f, 1.0f);
                }

                enemy.Draw();
            }
        }

        bullet.position.y += 10.0f;

        bullet.Draw();

        if (App::GetKey(VK_RIGHT))
        {
            player.position.x += 5.0f;
        }
        if (App::GetKey(VK_LEFT))
        {
            player.position.x -= 5.0f;
        }
        if (App::GetKeyDown(VK_SPACE))
        {
            if (bullet.position.y > App::GetWindowSize().y / 2.0f)
            {
                bullet.position = player.position;
                shotSound.Play();
            }
        }

        if (player.position.x > App::GetWindowSize().x / 2.0f)
        {
            player.position.x = App::GetWindowSize().x / 2.0f;
        }
        if (player.position.x < -App::GetWindowSize().x / 2.0f)
        {
            player.position.x = -App::GetWindowSize().x / 2.0f;
        }

        player.Draw();
    }

    return 0;
}
