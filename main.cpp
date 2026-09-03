#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace sf;
using namespace std;

struct Block
{
    sf::RectangleShape shape;
    bool destroyed = false;
    int hp;
    bool isGood = false;
    bool isBad = false;
};

int oo(int mins, int maxs){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> ra(mins, maxs);
    return ra(gen);
}

void createBlocks(vector<Block>& blocks, bool hard){
    blocks.clear();
    float shir = 60.f;
    float vasot = 20.f;
    float padding = 5.f; // расстояние между блоками
    float offsetX = 35.f;
    float offsetY = 50.f;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Block block;
            int ont = oo(1, 5);
            if (ont%5==0)
            {
                block.shape.setFillColor(Color::Red);
                block.hp = 2;
            }else{
                block.shape.setFillColor(Color::Blue);
                block.hp = 1;
            }
            block.shape.setSize({shir, vasot});
            block.shape.setOutlineColor(Color::Black);
            block.shape.setOutlineThickness(2.f);
            block.shape.setPosition({offsetX + j * (shir + padding),
                                     offsetY + i * (vasot + padding)});
            blocks.push_back(block);
        }
    }
    if (!hard)
    {
        int goodCount = 3;
        for (int i = 0; i < goodCount; ){
            int index = rand() % blocks.size();
            if (!blocks[index].isGood){
                blocks[index].shape.setFillColor(Color::Green);
                blocks[index].hp = 1;
                blocks[index].isGood = true;
                i++;
            }
        }
    }

    if (hard)
    {
  
            int index = rand() % blocks.size();
            if (!blocks[index].isBad){
                blocks[index].shape.setFillColor(Color(255, 165, 0));
                blocks[index].hp = 1;
                blocks[index].isBad = true;
            }
    }
}


int main()
{
    RenderWindow window(VideoMode({700, 800}), "SFML Window");
    
    Texture t1, t2, t3, t4, t5, t6;
    t1.loadFromFile("/Users/liza/Desktop/Курсач/arkanoid/pic/cat.jpeg");
    t2.loadFromFile("/Users/liza/Desktop/Курсач/arkanoid/pic/name.png");
    t3.loadFromFile("/Users/liza/Desktop/Курсач/arkanoid/pic/st.png");
    t4.loadFromFile("/Users/liza/Desktop/Курсач/arkanoid/pic/op.png");
    t5.loadFromFile("/Users/liza/Desktop/Курсач/arkanoid/pic/ex.png");
    t6.loadFromFile("/Users/liza/Desktop/Курсач/arkanoid/pic/png-klev-club-qkys-p-knopka-nazad-png-15-Photoroom.png");

    Sprite fon(t1);
    Sprite nam(t2);
    nam.setScale({2.f, 2.f});
    nam.setPosition({50, 50});
    Sprite pl(t3);
    pl.setScale({0.4f, 0.4f});
    pl.setPosition({200, 400});
    Sprite op(t4);
    op.setScale({0.4f, 0.4f});
    op.setPosition({30, 580});
    Sprite ex(t5);
    ex.setScale({0.4f, 0.4f});
    ex.setPosition({375, 590});
    Sprite nazad(t6);
    nazad.setScale({0.1f, 0.1f});
    nazad.setPosition({50, 700});

    Font font;
    if (!font.openFromFile("/Users/liza/Desktop/Курсач/arkanoid/timesnewromanps_italicmt.ttf"))
    {
        cout << "Ошибка!\n";
        return 1;
    }
    Text ad(font);
    ad.setString("A D");
    ad.setCharacterSize(60);
    ad.setFillColor(Color::White);
    ad.setPosition({200.f, 400.f});
    Text strl(font);
    strl.setString("< >");
    strl.setCharacterSize(60);
    strl.setFillColor(Color::White);
    strl.setPosition({350.f, 400.f});
    Text ng(font);
    Text ngh(font);
    Text mn(font);
    Text yW(font);
    Text yL(font);
    ng.setString("New game");
    ng.setCharacterSize(50);
    ng.setFillColor(Color::White);
    ng.setPosition({240.f, 300.f});
    ngh.setString("New game with hard mode");
    ngh.setCharacterSize(50);
    ngh.setFillColor(Color::White);
    ngh.setPosition({90.f, 400.f});
    mn.setString("Menu");
    mn.setCharacterSize(50);
    mn.setFillColor(Color::White);
    mn.setPosition({270.f, 500.f});
    yW.setString("You Win!");
    yW.setCharacterSize(70);
    yW.setFillColor(Color::Green);
    yW.setPosition({235.f, 200.f});
    yL.setString("You Lost!");
    yL.setCharacterSize(70);
    yL.setFillColor(Color::Red);
    yL.setPosition({230.f, 200.f});
    Text wout(font);
    wout.setString("New game without hard mode");
    wout.setCharacterSize(50);
    wout.setFillColor(Color::White);
    wout.setPosition({80.f, 400.f});

    Text livesText(font);
    livesText.setCharacterSize(30);
    livesText.setFillColor(Color::White);
    livesText.setPosition({575.f, 725.f});

    Text mode(font);
    mode.setString("Hard mode");
    mode.setCharacterSize(60);
    mode.setFillColor(Color::White);
    mode.setPosition({200.f, 200.f});

    RectangleShape square(Vector2f(100.f, 100.f)); //квадратик для управлени
    square.setPosition({195.f, 395.f}); 
    square.setFillColor(Color::Transparent);
    square.setOutlineColor(Color::White);
    square.setOutlineThickness(3.f);

    RectangleShape square2(Vector2f(275.f, 100.f)); // квадратик для мода
    square2.setPosition({195.f, 200.f}); 
    square2.setFillColor(Color::Transparent);
    square2.setOutlineColor(Color::White);
    square2.setOutlineThickness(3.f);

    vector<Block> blocks;
    float shir = 60.f;
    float vasot = 20.f;
    float padding = 5.f; // расстояние между блоками
    float offsetX = 35.f;
    float offsetY = 50.f;

    RectangleShape line;
    line.setSize({700.f, 3.f});
    line.setPosition({1.f, 696.f});
    line.setFillColor(Color::Black);

    RectangleShape pad;
    pad.setSize({100.f, 20.f});   // платформа
    pad.setPosition({300.f, 550.f}); 
    pad.setFillColor(Color::White);

    RectangleShape autoPad(Vector2f(100.f, 20.f));
    autoPad.setFillColor(Color(128,128,128)); // серая платформа
    autoPad.setPosition({0.f, 350.f});     
    float autoSpeed = 0.04f;
    float autoNapr = 1.f;

    CircleShape ball;
    ball.setRadius(10.f);              
    ball.setPosition({340.f, 530.f});
    ball.setFillColor(Color::White);
    Vector2f ballV = {0.f, -0.07f};



    bool menu = true;
    bool ops = false;
    bool play = false;
    bool knp = true;
    bool mash = false;
    bool win = false;
    bool lost = false;
    bool allDestroyed = false;
    bool hard = false;
    bool autoMove = false;

    int liv = 3;
    
    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<Event::Closed>()){
                window.close();
            }
            if (const auto* mouseEvent = event->getIf<Event::MouseButtonPressed>()){
                if (mouseEvent->button == Mouse::Button::Left)
                {
                    Vector2i pos = Mouse::getPosition(window);
                    if (menu && pos.x >= 30 && pos.x <= 320 && pos.y >= 580 && pos.y <= 670)   // настройки
                    {
                        menu = false;
                        ops = true;
                    }
                    if (ops && pos.x >= 200 && pos.x <= 475 && pos.y >= 200 && pos.y <= 300)   // хард
                    {
                        hard = !hard;
                    }
                    if (menu && pos.x >= 375 && pos.x <= 575 && pos.y >= 590 && pos.y <= 670)     // екзист 2
                    {
                        window.close();
                    }
                    if (!menu && (ops || play) && pos.x >= 50 && pos.x <= 250 && pos.y >= 700 && pos.y <= 800) // настройки и плей с назад
                    {
                        menu = true;
                        ops = false;
                        play = false;
                    }
                    if (!menu && ops && pos.x >= 310 && pos.x <= 500 && pos.y >= 430 && pos.y <= 650) // квадратик
                    {
                        square.setPosition({345.f, 395.f}); 
                        knp = false;
                    }
                    if (!menu && ops && pos.x >= 150 && pos.x <= 290 && pos.y >= 430 && pos.y <= 650) // квадратик
                    {
                        square.setPosition({195.f, 395.f});
                        knp = true;
                    }
                    if (menu && pos.x >= 200 && pos.x <= 450 && pos.y >= 400 && pos.y <= 550) // кнопка плей
                    {
                        play = true;
                        menu = false;
                        mash = false;
                        ballV = {0.f, -0.07f};
                        liv = 3;
                        win = false;
                        lost = false;
                        autoMove = false;
                        createBlocks(blocks, hard);
                    }
                    if ((win||lost) && !menu && !ops&& pos.x >= 270 && pos.x <= 475 && pos.y >= 500 && pos.y <= 600) // мени если игра окончена
                    {
                        menu = true;
                        win = false;
                        lost = false;
                        autoMove = false;

                    }
                    if ((win||lost) && !menu && !ops && pos.x >= 240 && pos.x <= 540 && pos.y >= 300 && pos.y <= 350) // новая игра
                    {
                        play = true;
                        win = false;
                        lost = false;
                        liv = 3;
                        createBlocks(blocks, hard); 
                        mash = false;
                        ballV = {0.f, -0.07f};
                        autoMove = false;

                    }
                    if ((win||lost) && !menu && !ops && pos.x >= 80 && pos.x <= 770 && pos.y >= 400 && pos.y <= 450) // новая игра c хардом
                    {
                        play = true;
                        win = false;
                        lost = false;
                        hard = !hard;
                        mash = false;
                        ballV = {0.f, -0.07f};
                        liv = 3;
                        autoMove = false;
                        createBlocks(blocks, hard);  

                    }
                    
                }
            }
            
            
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Space))
        {
            mash = true;
            autoMove = true;
        }
        
        if (knp){
            if (Keyboard::isKeyPressed(Keyboard::Key::A)){
                pad.move({-0.15f, 0.f});
            }
        if (Keyboard::isKeyPressed(Keyboard::Key::D)){
                pad.move({0.15f, 0.f});
            }
        }
        else{
            if (Keyboard::isKeyPressed(Keyboard::Key::Left)){
                pad.move({-0.15f, 0.f});
            }
        if (Keyboard::isKeyPressed(Keyboard::Key::Right)){
                pad.move({0.15f, 0.f});
            }
        }

        Vector2f pos = pad.getPosition();
        if (pos.x < 0){
            pad.setPosition({0.f, pos.y});
        }
        if (pos.x + pad.getSize().x > 700){
            pad.setPosition({700.f - pad.getSize().x, pos.y});
        }

        if (hard && autoMove) {
            autoPad.move({autoSpeed * autoNapr, 0.f});
            Vector2f pos = autoPad.getPosition();
            if (pos.x <= 0.f) autoNapr = 1;
            if (pos.x + autoPad.getSize().x >= 700.f) autoNapr = -1;
        }
        if (!mash){
            ball.setPosition({
            pad.getPosition().x + pad.getSize().x / 2 - ball.getRadius(),
            pad.getPosition().y - ball.getRadius() * 2
        });
        }
        else{
            ball.move(ballV);
            Vector2f pos = ball.getPosition();
            float r = ball.getRadius();
            if (pos.x - r <= 0){
                
                ballV.x= abs(ballV.x);
            }
            if (pos.x + r >= 700){
                
                ballV.x = -abs(ballV.x);
            }
            if (pos.y - r <= 0)
            {
                
                ballV.y = abs(ballV.y);
            }
            Vector2f ballPos = ball.getPosition();
            float ballR = ball.getRadius();
            Vector2f padPos = pad.getPosition();
            Vector2f padSize = pad.getSize();
            if (ballPos.x + 2*ballR > padPos.x &&   // правая граница мяча > левая граница платформы
                ballPos.x < padPos.x + padSize.x && // левая граница мяча < правая граница платформы
                ballPos.y + 2*ballR > padPos.y &&   // нижняя граница мяча > верх платформы
                ballPos.y < padPos.y + padSize.y){
                    ballV.y = -abs(ballV.y);
                    float padCenter = padPos.x + padSize.x / 2.f;
                    float distance = ((ballPos.x + ballR) - padCenter) / (padSize.x / 2.f);
                    ballV.x = 0.07f * distance;             // меняем горизонтальную скорость в зависимости от удара(Ускорение короче)
            }
            Vector2f ballPos2 = ball.getPosition();         // серая платформа
            float ballR2 = ball.getRadius();
            Vector2f autoPadPos = autoPad.getPosition();
            Vector2f autoPadSize = autoPad.getSize();
            float ballLeft = ball.getPosition().x;
            float ballRight  = ball.getPosition().x + 2*ball.getRadius(); // тяжелая артилерия чтобы точно не проходила на сквозь
            float ballTop = ball.getPosition().y;
            float ballBottom = ball.getPosition().y + 2*ball.getRadius();

            float padLeft = autoPad.getPosition().x;
            float padRight  = autoPad.getPosition().x + autoPad.getSize().x;
            float padTop = autoPad.getPosition().y;
            float padBottom = autoPad.getPosition().y + autoPad.getSize().y;

            if (hard && ballRight > padLeft && ballLeft < padRight &&
                ballBottom > padTop && ballTop < padBottom) 
            {
                float overlapLeft   = ballRight - padLeft;
                float overlapRight  = padRight - ballLeft;
                float overlapTop    = ballBottom - padTop;
                float overlapBottom = padBottom - ballTop;
                float minOverlap = min({overlapLeft, overlapRight, overlapTop, overlapBottom});
                if (minOverlap == overlapLeft)
                {
                    ballV.x = -abs(ballV.x);
                    ball.setPosition({padLeft - 2*ball.getRadius(), ball.getPosition().y});
                }else if (minOverlap == overlapRight)
                {
                    ballV.x = abs(ballV.x);
                    ball.setPosition({padRight, ball.getPosition().y});
                }else if (minOverlap == overlapTop)
                {
                    ballV.y = -abs(ballV.y);
                    ball.setPosition({ball.getPosition().x, padTop - 2*ball.getRadius()});
                }else
                {
                    ballV.y = abs(ballV.y);
                    ball.setPosition({ball.getPosition().x, padBottom});
                }
            }

            if (ball.getPosition().y + ball.getRadius() * 2 >= 800)
            {
                mash = false;
                ballV = {0.f, -0.07f};
                liv--;
            }

            for (auto &block : blocks)
            {
                if (block.destroyed) continue;
                Vector2f bPos = block.shape.getPosition();
                Vector2f bSize = block.shape.getSize();
                if (ballPos.x + 2*ballR > bPos.x &&
                    ballPos.x < bPos.x + bSize.x &&
                    ballPos.y + 2*ballR > bPos.y &&
                    ballPos.y < bPos.y + bSize.y)
                {
                        block.hp--;
                        if (block.hp <= 0)
                        {
                            if (block.isGood)
                            {
                                liv++;
                            }
                            if (block.isBad)
                            {
                                liv--;
                            }
                            
                            block.destroyed = true;
                        }else{
                            block.shape.setFillColor(Color::Blue);
                        }
                        ballV.y = -ballV.y;
                        
                        break;
                        
                }
                
                
            }
            
        }
        

        livesText.setString("Lives: " + to_string(liv));
        
        window.clear(Color::Black);
        window.draw(fon);
        allDestroyed = true;

        for (auto &b : blocks)                  // проверка на наличее кубиков, оранжевый не учитываем
        {
            if (!b.destroyed && !b.isBad)
            {
                allDestroyed = false;
                break;
            }
        }
        if (allDestroyed)
        {
            win = true;
            play = false;
        }
        if (!allDestroyed and liv<=0)
        {
            lost = true;
            play = false;
        }
        
        
        if (play)  
        {
            for (auto &block : blocks)
            {
                if (!block.destroyed){
                    window.draw(block.shape);
                }
            }
            window.draw(line);
            window.draw(pad);
            window.draw(ball);
            window.draw(livesText);
            if (hard)
            {
                window.draw(autoPad);
            }
            
        }
        if (lost && !menu && !ops)
        {
            window.draw(yL);
            window.draw(ng);
            window.draw(mn);
            if (hard)
            {
                window.draw(wout);
            }else{
                window.draw(ngh);
            }
            
        }
         if (win && !menu && !ops)
        {
            window.draw(yW);
            window.draw(ng);
            window.draw(mn);
            if (hard)
            {
                window.draw(wout);
            }else{
                window.draw(ngh);
            }
        }
        
        if (!menu && play)
        {
            window.draw(nazad);
        }
        
        if (ops && !menu)
        {
            window.draw(ad);
            window.draw(strl);
            window.draw(nazad);
            window.draw(square);
            window.draw(mode);
            if (hard)
            {
                window.draw(square2);
            }
            

        }
        
        if (menu){
            window.draw(nam);
            window.draw(pl);
            window.draw(op);
            window.draw(ex);
        }
        
        window.display();
    }
    
    return 0;
}