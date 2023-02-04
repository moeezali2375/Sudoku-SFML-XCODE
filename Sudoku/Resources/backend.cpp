#include<iostream>
#include <ctime>
#include <math.h>
using namespace std;
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
    int num2 = (int)floor(
        (float)(rand() / double(RAND_MAX) * num + 1));
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
//int main()
//{
//    int solution_array[9][9];
//    int user_array[9][9];
//    int difficulty = 20;
//    set_solution_array(solution_array, user_array, difficulty);
//    display_board(solution_array);
//    cout << endl;
//    display_board(user_array);
//
//}
							
