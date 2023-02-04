#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <ctime>
#include <math.h>
using namespace std;
using namespace sf;
//! DECLARATIONS
int random_value(int num);
// This function set the values for the game
void set_solution_array(int array[][9], int array2[][9], int difficulty);
// This function fills the diagonal values
void fill_diagonal(int array[][9]);
void fill_sub_array(int array[][9], int row, int col);
// This Function checks if the box is empty or not
bool check_box(int array[][9], int row_s, int col_s, int num);
// This function sets the non diagonal values
bool fill_non_diagonal_values(int array[][9], int i, int j);
// Safe index check
bool non_diagonal_safe_index(int array[][9], int i, int j, int num);
// Safe row check
int non_diagonal_safe_row(int array[][9], int i, int num);
// Safe column check
int non_diagonal_safe_col(int array[][9], int j, int num);
// Sets BOARD
void set_user_array(int array2[][9], int num);
//! Definitions
int non_diagonal_safe_col(int array[][9], int j, int num)
{
    bool flag = 1;
    for (int i = 0; i < 9; i++)
    {
        if (array[i][j] == num)
            flag = 0;
    }
    if (flag)
        return 1;
    return 0;
}
int non_diagonal_safe_row(int array[][9], int i, int num)
{
    bool flag = 1;
    for (int j = 0; j < 9; j++)
    {
        if (array[i][j] == num)
        {
            flag = 0;
        }
    }
    if (flag)
        return 1;
    return 0;
}
bool non_diagonal_safe_index(int array[][9], int i, int j, int num)
{

    if (non_diagonal_safe_row(array, i, num) && non_diagonal_safe_col(array, j, num) && check_box(array, i - i % 3, j - j % 3, num))
        return true;
    else
        return false;
}
bool fill_non_diagonal_values(int array[][9], int i, int j)
{
    if (j > 8 && i < 8)
    {
        j = 0;
        i += 1;
    }
    if (i >= 9 && j >= 9)
    {
        return 1;
    }
    if (i < 3)
    {
        if (j <= 2)
            j = 3;
    }
    else if (i <= 5)
    {
        if (j == (int)(i / 3) * 3)
            j += 3;
    }
    else
    {
        if (j == 6)
        {
            j = 0;
            i++;
            if (i >= 9)
                return 1;
        }
    }
    for (int q = 1; q < 10; q++)
    {
        if (non_diagonal_safe_index(array, i, j, q))
        {
            array[i][j] = q;
            if (fill_non_diagonal_values(array, i, j + 1))
                return 1;
            else
                array[i][j] = 0;
        }
    }
    return 0;
}
int random_value(int num)
{
    //    int num2 = (int)floor(
    //        (float)(rand() / double(RAND_MAX) * num + 1));
    int num2 = rand() % num + 1;
    return num2;
}
bool check_box(int array[][9], int row_s, int col_s, int num)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (array[row_s + i][col_s + j] == num)
            {
                return 0;
            }
        }
    }
    return 1;
}
void fill_sub_array(int array[][9], int row, int col)
{
    srand(time(NULL));
    int num;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            do
            {
                num = random_value(9);
            } while (!check_box(array, row, col, num));
            array[row + i][col + j] = num;
        }
    }
}
void fill_diagonal(int array[][9])
{
    for (int i = 0; i < 9; i = i + 3)
    {
        fill_sub_array(array, i, i);
    }
}
void set_solution_array(int array[][9], int array2[][9], int difficulty)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            array[i][j] = 0;
        }
    }
    fill_diagonal(array);
    fill_non_diagonal_values(array, 0, 3);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            array2[i][j] = array[i][j];
        }
    }
    set_user_array(array2, difficulty);
}
void set_user_array(int array2[][9], int num)
{
    while (num != 0)
    {
        int index = random_value(9 * 9) - 1;
        int j = index % 9;
        if (j != 0)
            j--;
        int i = (index / 9);
        if (array2[i][j] == 0)
            continue;
        else
        {
            array2[i][j] = 0;
            num--;
        }
    }
}
void display_board(int array[][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

//! DRIVER
// int main()
//{
//     int solution_array[9][9];
//     int user_array[9][9];
//     int difficulty = 20;
//     set_solution_array(solution_array, user_array, difficulty);
//     display_board(solution_array);
//     cout << endl;
//     display_board(user_array);
//
// }

//==================================================
//
//               ####  #####  ###    ###  ##
//              ##     ##     ## #  # ##  ##
//               ###   #####  ##  ##  ##  ##
//                 ##  ##     ##      ##  ##
//              ####   ##     ##      ##  ######
//
//==================================================

bool tile_checker(int x, int y, int r, int c, int w)
{

    int flag0 = 0;
    int flag1 = 0;
    for (int j = 0; j < c; j++)
    {
        if (x >= j * (w + 10) + 50 && x <= j * (w + 10) + 50 + w)
        {
            flag1 = 1;
        }
    }
    for (int i = 0; i < r; i++)
    {
        if (y >= i * (w + 10) + 100 && y <= i * (w + 10) + 100 + w)
            flag0 = 1;
    }
    if (flag1 == 1 && flag0 == 1)
    {
        return true;
    }
    return false;
}

void display_tiles(int tiles[][9], int r, int c, int w, RenderWindow &window)
{
    Texture t;
    Sprite s(t);
    Texture num0, num1, num2, num3, num4, num5, num6, num7, num8, mine, flag;
    RectangleShape small_box_grid(Vector2f(50, 50));
    num0.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#1/PROJECTS/Sudoku/Sudoku/Resources/0.png");
    num1.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#1/PROJECTS/Sudoku/Sudoku/Resources/1.png");
    num2.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#1/PROJECTS/Sudoku/Sudoku/Resources/2.png");
    num3.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#1/PROJECTS/Sudoku/Sudoku/Resources/3.png");
    num4.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#1/PROJECTS/Sudoku/Sudoku/Resources/4.png");
    num5.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#1/PROJECTS/Sudoku/Sudoku/Resources/5.png");
    num6.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#1/PROJECTS/Sudoku/Sudoku/Resources/6.png");
    num7.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#1/PROJECTS/Sudoku/Sudoku/Resources/7.png");
    num8.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#1/PROJECTS/Sudoku/Sudoku/Resources/8.png");
    mine.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#1/PROJECTS/Sudoku/Sudoku/Resources/9.png");
    Sprite n0(num0), n1(num1), n2(num2), n3(num3), n4(num4), n5(num5), n6(num6), n7(num7), n8(num8), mi(mine);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {

            small_box_grid.setOutlineThickness(3);
            small_box_grid.setOutlineColor(Color::Black);
            small_box_grid.setFillColor(Color::Transparent);
            small_box_grid.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
            window.draw(small_box_grid);
            if (tiles[i][j] == -1)
            {
                s.setTextureRect(IntRect(0, 0, w, w));
                s.setColor(Color::Black);
                s.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(s);
            }
            if (tiles[i][j] == 0)
            {
                ;
            }
            if (tiles[i][j] == 1)
            {
                n1.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(n1);
            }
            if (tiles[i][j] == 2)
            {
                n2.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(n2);
            }
            if (tiles[i][j] == 3)
            {
                n3.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(n3);
            }
            if (tiles[i][j] == 4)
            {
                n4.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(n4);
            }
            if (tiles[i][j] == 5)
            {
                n5.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(n5);
            }
            if (tiles[i][j] == 6)
            {
                n6.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(n6);
            }
            if (tiles[i][j] == 7)
            {
                n7.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(n7);
            }
            if (tiles[i][j] == 8)
            {
                n8.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(n8);
            }
            if (tiles[i][j] == 9)
            {
                mi.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(mi);
            }
            if (tiles[i][j] == 10)
            {
                s.setTextureRect(IntRect(0, 0, w, w));
                s.setColor(Color::Red);
                s.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(s);
            }
        }
    }
}

int main()
{
    sf::RenderWindow start_screen(sf::VideoMode(2400, 1350), "Sudoku", sf::Style::Close);

    sf::Texture background_texture;
    background_texture.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#1/PROJECTS/Sudoku/Sudoku/Resources/main_screen.jpg");

    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png"))
    {
        return EXIT_FAILURE;
    }
    start_screen.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Sprite background;
    background.setTexture(background_texture);

    while (start_screen.isOpen())
    {
        sf::Event event;
        while (start_screen.pollEvent(event))
        {
            start_screen.clear();
            start_screen.draw(background);
            start_screen.display();

            if (event.type == sf::Event::Closed)
            {
                start_screen.close();
                break;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                start_screen.close();
                cout << "Welcome to the game!";
                // TODO
                // option window

                //! Game Screen
                sf::RenderWindow window(sf::VideoMode(1440, 858), "CONSOLE", sf::Style::Close | sf::Style::Resize);
                // ASAL KAAM
                // TILES GENERATOR
                int tiles[9][9];
                int solution[9][9];
                cout << "Select Difficulty: " << endl;
                cout << "1. Easy\n";
                cout << "2. Medium\n";
                cout << "3. Hard\n";
                int variable;
                int difficulty = 20;
                cin >> variable;
                if (variable == 1)
                    difficulty = 10;
                else if (variable == 2)
                    difficulty = 15;
                else
                    difficulty = 20;
                set_solution_array(solution, tiles, difficulty);
                int w = 50;

                // RENDER_WINDOW
                // WINDOW_DISPLAY
                while (window.isOpen())
                {
                    int count = 0;
                    for (int i = 0; i < 9; i++)
                    {
                        for (int j = 0; j < 9; j++)
                        {
                            if (tiles[i][j] == 0)
                                count++;
                        }
                    }
                    if (count == 0)
                    {

                        window.close();
                        cout << "You Win!\n";
                        break;
                    }
                    window.clear(Color::Color::White);
                    Event event2;
                    while (window.pollEvent(event2))
                    {
                        if (event2.type == sf::Event::Closed)
                        {
                            window.close();
                            break;
                        }
                    }
                    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                    if (tile_checker(mouse_position.x, mouse_position.y, 9, 9, w) == 1)
                    {
                        Texture t;
                        Sprite s(t);
                        int x = (mouse_position.x - 50) / (w + 10);
                        int y = (mouse_position.y - 100) / (w + 10);
                        s.setTextureRect(IntRect(0, 0, w, w));
                        s.setColor(Color::Cyan);
                        s.setPosition(x * (w + 10) + 50, y * (w + 10) + 100);
                        window.draw(s);
                    }
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        sf::Vector2i left = sf::Mouse::getPosition(window);
                        int x = (left.x - 50) / (w + 10);
                        int y = (left.y - 100) / (w + 10);
                        if (x >= 0 && x < 9 && y >= 0 && y < 9)
                        {

                            {
                                int num;
                                cout << "Enter data you want to insert: ";
                                cin >> num;
                                if (num == solution[y][x])
                                    tiles[y][x] = num;
                                else
                                    cout << "Invalid data inserted";
                            }
                        }
                    }
                    display_tiles(tiles, 9, 9, w, window);

                    window.display();
                }
            }
        }
    }
}
