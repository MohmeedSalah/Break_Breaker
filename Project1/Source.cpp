#include<SFML/Graphics.hpp>
#include<string>
#include<sstream>
#include<iostream>
using namespace std;
using namespace sf;
Texture Block01, Block02;
Sprite sball, spritepaddle, Block[250], Block2[250];
void ball_dir_lose_Move(float& dirx, float& diry, int& count);
void paddle_move();
void ball_paddle_intersects(float& diry);
void higher(int& x, int y);
int main()
{
    //score
    int score1 = 0, highscore = 0;
    Font font;
    font.loadFromFile("score.TTF");
    Text textscore, hightext;
    textscore.setFont(font);
    hightext.setFont(font);
    hightext.setString(" 0");
    textscore.setString(" 0");
    textscore.setCharacterSize(10);
    hightext.setCharacterSize(10);
    textscore.setScale(4, 5);
    hightext.setScale(4, 5);
    hightext.setFillColor(sf::Color::Cyan);
    hightext.setPosition(200, 650);
    textscore.setFillColor(sf::Color::Cyan);
    textscore.setPosition(400, 825);
    /// ///// picture all programe 
    RenderWindow window(VideoMode(785, 900), "Break");
    window.setFramerateLimit(70);
    /// //////////      اسامي الصور
    Texture paddle, backgroundphoto, score, Block01, Block02, Block04, Ball, gameover, sf, backgroundplay;
    backgroundphoto.loadFromFile("sf.jpg");
    paddle.loadFromFile("paddle.jpg");
    Block01.loadFromFile("block01.jpg");
    Block02.loadFromFile("block03.jpg");
    Ball.loadFromFile("ball.jpg");
    sf.loadFromFile("ss.png");
    backgroundplay.loadFromFile("Background.jpg");
    /// ////////// sprite to picture
    Sprite spritebackground, sm, Block[250], Block2[250], Block4[100], sgameover, spscore, sbackgroundplay;
    spritebackground.setTexture(backgroundphoto);
    sball.setTexture(Ball);
    sball.setPosition(400, 750);
    spritepaddle.setTexture(paddle);
    spritepaddle.setPosition(400, 780);
    spritepaddle.scale(2, 1);
    sgameover.setTexture(gameover);
    spscore.setTexture(score);
    sm.setTexture(sf);
    sm.scale(0.21, 0.6);
    spscore.setPosition(10, 820);
    spritebackground.scale(0.8, 0.45);
    sbackgroundplay.setTexture(backgroundplay);
    sbackgroundplay.setScale(0.9, 1);
    /// ///////////////////        رسم الطوب        

    int n = 0;
    for (int i = 0; i < 23; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Block[n].setTexture(Block01);
            Block2[n].setTexture(Block02);
            Block[n].setPosition(i * 34, j * 45);
            Block2[n].setPosition(i * 34, j * 45 + 22);
            n++;
        }
    }
    /// ////////////////////////// تحرك الكورة في الهواء 
    float dirx = 4, diry = 3; int count = -1;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        ball_dir_lose_Move(dirx, diry, count);
        paddle_move();
        /// <summary>
        /// ////////////////////// اصطدام الكورة بالحجر 
        for (int i = 0; i < n; i++)
        {
            if (sball.getGlobalBounds().intersects(Block[i].getGlobalBounds()))
            {
                Block[i].setPosition(-100, 0);
                dirx = -dirx;
                diry = -diry;
                score1++;
            }
            if (sball.getGlobalBounds().intersects(Block2[i].getGlobalBounds()))
            {
                Block2[i].setPosition(-100, 0);
                dirx = -dirx;
                diry = -diry;
                score1++;
            }
        }
        ball_paddle_intersects(diry);
        higher(highscore, score1);
        /// //////////////////////////       window.... 
        window.clear();
        if (count == -1)
        {
            window.draw(sbackgroundplay);
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                count = 0;
            }
        }
        else if (count == 0)
        {
            window.draw(spritebackground);
            window.draw(spritepaddle);
            window.draw(sball);
            window.draw(textscore);
            std::stringstream score2;
            score2 << " " << score1;
            textscore.setString(score2.str());
            for (int i = 0; i < n; i++)
            {
                window.draw(Block[i]);
                window.draw(Block2[i]);
            }
            stringstream high;
            high << "your high score : " << highscore;
            hightext.setString(high.str());
        }
        else if (count == 1)
        {
            window.draw(sm);
            textscore.setPosition(400, 550);
            window.draw(textscore);
            window.draw(hightext);
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                dirx = 4, diry = 4;
                score1 = 0;
                textscore.setPosition(400, 825);
                sball.setPosition(400, 750);
                spritepaddle.setPosition(400, 780);
                count = 0;
                n = 0;
                for (int i = 0; i < 23; i++)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        Block[n].setPosition(-100, 0);
                        Block2[n].setPosition(-100, 0);
                        n++;
                    }
                }
                n = 0;
                for (int i = 0; i < 23; i++)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        Block[n].setTexture(Block01);
                        Block[n].setPosition(i * 34, j * 45);
                        Block2[n].setTexture(Block02);
                        Block2[n].setPosition(i * 34, j * 45 + 22);
                        n++;
                    }
                }
            }
        }
        window.display();
    }
    return 0;
}
/// / function 
void ball_dir_lose_Move(float& dirx, float& diry, int& count)
{
    /// اتجاة الكورة داخل الويندو 
    Vector2f p = sball.getPosition();
    if (p.x < 0 || p.x > 785)
    {
        dirx = -dirx;
    }
    if (p.y < 0 || p.y > 900)
    {
        diry = -diry;
        dirx = -dirx;
    }
    /// // lose 
    if (p.y > 790 && count == 0)
    {
        count = 1;
    }
    //
    if (count == 0)
    {
        sball.move(dirx, diry);
    }
}
void paddle_move()
{
    Vector2f pos_spaddle = spritepaddle.getPosition();
    //cout << pos_spaddle.x << endl;
    if (pos_spaddle.x < 605 && pos_spaddle.x > 0)
    {
        if (Keyboard::isKeyPressed(Keyboard::Right))
            spritepaddle.move(10, 0);
        if (Keyboard::isKeyPressed(Keyboard::D))
            spritepaddle.move(10, 0);
        if (Keyboard::isKeyPressed(Keyboard::Left))
            spritepaddle.move(-10, 0);
        if (Keyboard::isKeyPressed(Keyboard::A))
            spritepaddle.move(-10, 0);
    }
    else if (pos_spaddle.x <= 0)
    {
        if (Keyboard::isKeyPressed(Keyboard::Right))
            spritepaddle.move(10, 0);
        if (Keyboard::isKeyPressed(Keyboard::D))
            spritepaddle.move(10, 0);
    }
    else if (pos_spaddle.x >= 605)
    {
        if (Keyboard::isKeyPressed(Keyboard::Left))
            spritepaddle.move(-10, 0);
        if (Keyboard::isKeyPressed(Keyboard::A))
            spritepaddle.move(-10, 0);
    }
}
void ball_paddle_intersects(float& diry)
{
    if (sball.getGlobalBounds().intersects(spritepaddle.getGlobalBounds()))
    {
        diry = -diry;
    }
}
void higher(int& x, int y) {

    if (x < y) {
        x = y;
    }
}