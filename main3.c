#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>


#define R(piece) "\033[31m"#piece"\033[0m"//红色棋子
//#define B(piece) "\033[30m"#piece"\033[0m"//黑色棋子
#define B(piece) "\033[34m"#piece"\033[0m"//藍色棋子
#define CROSS "\033[33m十\033[0m"

//定義外部變量,棋盤座標
char* array[9][9];
int xi,yi;//要移动的棋子
int xj,yj;//移動的目標位置
bool isStandard = 1;//是否符合規則，初始值1，符合
bool gameOverSign = 1;//遊戲是否结束，0结束
bool restart = 0;
//生成棋盤
void chessboardBuilding();
//打印棋盤
void printChessboard();
//判斷是红棋還是黑棋,红棋返回1,黑棋返回-1,否則返回0
int redOrBlack(int x,int y);
//红棋移動
void redMove();
//藍棋移動
void blackMove();
//每種棋子的規則
void rulesOfAllKindsOfChessPieces();
//判斷遊戲結束
void isGameOver();

//**************************主函數******************************
int main()
{
    //生成棋盤
    chessboardBuilding();
    //打印棋盤
    printChessboard();
    //開始下棋
    int turn = -1;
    while (gameOverSign) 
    {
        isStandard = 1;
        turn *= (-1);//交替下棋
        switch (turn) 
        {
            case 1:
                redMove();
                turn = (restart) ? (turn*-1) : turn;
                break;
            case -1:
                blackMove();
                turn = (restart) ? (turn*-1) : turn;
                break;
        }
        isGameOver();
        
    }
    printf("遊戲结束!\n");
    
  
    
}//主函式


//*************************自定義函數*****************************

//生成棋盤
void chessboardBuilding()
{
    for (int i = 0; i < 9; i ++) {
        for (int j = 0; j < 9 ; j ++) {
            array[i][j] = CROSS;
        }
        printf("\n");
    }
    
    
    //布置红棋
    array[0][0] = array[0][8] = R(香);
    array[0][1] = array[0][7] = R(桂);
    array[0][2] = array[0][6] = R(銀);
    array[0][3] = array[0][5] = R(金);
    array[0][4] = R(王);
    array[1][1] = R(飛);
    array[1][7] = R(角);
    array[2][0] = array[2][1] = array[2][2] = array[2][3] = array[2][4] = array[2][5] = array[2][6] = array[2][7] = array[2][8] = R(步);
    
    //布置黑棋
    array[8][0] = array[8][8] = B(香);
    array[8][1] = array[8][7] = B(桂);
    array[8][2] = array[8][6] = B(銀);
    array[8][3] = array[8][5] = B(金);
    array[8][4] = B(王);
    array[7][1] = B(角);
    array[7][7] = B(飛);
    array[6][0] = array[6][1] = array[6][2] = array[6][3] = array[6][4] = array[6][5] = array[6][6] = array[6][7] = array[6][8] = B(步);
}

//打印棋盤
void printChessboard()
{
	system("clear");
    
    //顯示
    printf("  \033[43;30 日日本將棋\033[0m\n\n");
    for (int i = 0; i < 9;  i ++) {
        for (int j = 0; j < 9; j ++) {
            printf("%s",array[i][j]);
        }
        printf("\n");
    }

}

//判斷紅黑棋 紅棋等於1 黑棋等於-1
int redOrBlack(int x,int y)
{
    if (array[x][y] == R(香) || array[x][y] == R(桂) || array[x][y] == R(銀) || array[x][y] == R(桂) || array[x][y] == R(王) || array[x][y] == R(飛) || array[x][y] == R(角) || array[x][y] == R(步))
    {
        return  1;
    }
    else if (array[x][y] == B(香) || array[x][y] == B(桂) || array[x][y] == B(銀) || array[x][y] == B(金) || array[x][y] == B(王) || array[x][y] == B(飛) || array[x][y] == R(角) || array[x][y] == B(步))
    {
        return -1;
    }
    else
        return 0;
}

//红棋移動
void redMove()
{
    if (restart) {
        printf("違反遊戲規則，請重新輸入\n");
        restart = 0;
    }
    printf("[红棋]請输入你要移動的棋子:\n");
    scanf("%d %d",&xi,&yi);
    printf("[红棋]請输入你要放置的位置:\n");
    scanf("%d %d",&xj,&yj);
    rulesOfAllKindsOfChessPieces();
    printChessboard();
}

//黑棋移動
void blackMove()
{
    if (restart) {
        printf("違反遊戲規則，請重新输入\n");
        restart = 0;
    }
    printf("[黑棋]請输入你要移動的棋子:\n");
    scanf("%d %d",&xi,&yi);
    printf("[黑棋]請输入你要放置的位置:\n");
    scanf("%d %d",&xj,&yj);
    rulesOfAllKindsOfChessPieces();
    printChessboard();
}

//判斷遊戲結束
void isGameOver()
{
    bool sign_r = 0;
    bool sign_b = 0;
    for (int i = 0; i < 9; i ++) {
        for (int j = 0; j < 9; j ++) {
            if (array[i][j] == R(王)) {
                sign_r = 1;
            }
            else if (array[i][j] == B(王))
            {
                sign_b = 1;
            }
        }
    }
    if ((sign_r == 0)||(sign_b == 0)) {
        gameOverSign = 0;
    }
}

//每種棋規定
void rulesOfAllKindsOfChessPieces()
{
//R（香）----------------------------------------
    if (array[xi][yi] == R(香))
    {
        if (yi == yj)//列座標不變，同列移動
        {
            for (int i = xi+1; i < xj; i ++)
            {
                if (array[i][yi] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
            }
            for (int i = xi-1; i > xj; i --)
            {
                if (array[i][yi] != CROSS)
                    isStandard = 0;
            }
        }
        else if (xi == xj)//行座標不變，同行移動
        {
            for (int i = yi+1; i < yj; i ++)
                if (array[xi][i] != CROSS)
                    isStandard = 0;
            for (int i = yi-1; i > yj; i --)
                if (array[xi][i] != CROSS)
                    isStandard = 0;
        }
        
        if ((xi == xj || yi == yj)&& isStandard && (redOrBlack(xj, yj) != 1))//如果棋子直行、没有犯規且落點不是红棋，可移動
        {
            
            array[xi][yi] = CROSS;
            array[xj][yj] = R(香);
        }
        else
        {
            restart = 1;
        }
    }

//B（香）----------------------------------------
    else if (array[xi][yi] == B(香))
    {
        
        if (yi == yj)///列座標不變，同列移動
        {
            for (int i = xi+1; i < xj; i ++)
            {
                if (array[i][yi] != CROSS)
                    isStandard = 0;//如果初始位置和目標位置之間有棋子，则不符合規則
            }
            for (int i = xi-1; i > xj; i --)
            {
                if (array[i][yi] != CROSS)
                    isStandard = 0;
            }
        }
        else if (xi == xj)//行座標不變，同行移動
        {
            for (int i = yi+1; i < yj; i ++)
                if (array[xi][i] != CROSS)
                    isStandard = 0;
            for (int i = yi-1; i > yj; i --)
                if (array[xi][i] != CROSS)
                    isStandard = 0;
        }
        if ((xi == xj || yi == yj)&& isStandard && redOrBlack(xj, yj) != -1)///如果棋子直行、没有犯規且落點不黑棋，可移動
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(香);
        }
        else
        {
            restart = 1;
        }
    }

//R（桂）----------------------------------------
    else if (array[xi][yi] == R(桂))
    {
        if ((xj == xi+2 && yj == yi-1 ) || (xj == xi+2 && yj == yi+1 ) && isStandard && redOrBlack(xj, yj) != -1)
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R(桂);
        }
        else
        {
            restart = 1;
        }
    }
    
//B（桂）----------------------------------------
    else if (array[xi][yi] == B(桂))
    {
        if ((xj == xi-2 && yj == yi-1 || (xj == xi-2 && yj == yi+1 ) && isStandard && redOrBlack(xj, yj) != 1))
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(桂);
        }
        else
        {
            restart = 1;
        }
    }
    
//R（飛）----------------------------------------
    else if (array[xi][yi] == R(飛))
    {
        if (yi == yj)//列坐标不变，同列移动
        {
            for (int i = xi+1; i < xj; i ++)
            {
                if (array[i][yi] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
            }
            for (int i = xi-1; i > xj; i --)
            {
                if (array[i][yi] != CROSS)
                    isStandard = 0;
            }
        }
        else if (xi == xj)//行坐标不变，同行移动
        {
            for (int i = yi+1; i < yj; i ++)
                if (array[xi][i] != CROSS)
                    isStandard = 0;
            for (int i = yi-1; i > yj; i --)
                if (array[xi][i] != CROSS)
                    isStandard = 0;
        }
        if ((xi == xj || yi == yj)&& isStandard && redOrBlack(xj, yj) != -1)//如果棋子直行、没有犯规且落点不是红棋，可以移动
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(香);
        }
        else
        {
            restart = 1;
        }
    }
    
//B（飛）----------------------------------------
    else if (array[xi][yi] == B(飛))
    {
        if (yi == yj)//列坐标不变，同列移动
        {
            for (int i = xi+1; i < xj; i ++)
            {
                if (array[i][yi] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
            }
            for (int i = xi-1; i > xj; i --)
            {
                if (array[i][yi] != CROSS)
                    isStandard = 0;
            }
        }
        else if (xi == xj)//行坐标不变，同行移动
        {
            for (int i = yi+1; i < yj; i ++)
                if (array[xi][i] != CROSS)
                    isStandard = 0;
            for (int i = yi-1; i > yj; i --)
                if (array[xi][i] != CROSS)
                    isStandard = 0;
        }
        if ((xi == xj || yi == yj)&& isStandard && redOrBlack(xj, yj) != -1)//如果棋子直行、没有犯规且落点不是红棋，可以移动
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(香);
        }
        else
        {
            restart = 1;
        }
    }
    //R（角）----------------------------------------
    else if (array[xi][yi] == R(角))
    {
        if (yj > yi && xj < xi)//位於座標右上
        {
            for (int i = 1; i < xi-xj+1 ; i ++)
            {
                if (array[xi-i][yi+i] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
           }
        }
        if (yj < yi && xj < xi)//位於座標左上
        {
            for (int i = 1; i < xi-xj+1 ; i ++)
            {
                if (array[xi-i][yi-i] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
           }
        }
        if (yj < yi && xj > xi)//位於座標左下
        {
            for (int i = 1; i < xj-xi+1 ; i ++)
            {
                if (array[xi+i][yi-i] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
           }
        }
        if (yj > yi && xj > xi)//位於座標右下
        {
            for (int i = 1; i < xj-xi+1 ; i ++)
            {
                if (array[xi+i][yi+i] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
           }
        }
        if ((abs(xi - xj) == abs(yi - yj))&& isStandard && redOrBlack(xj, yj) != 1)//如果棋子為對角、没有犯规且落点不是红棋，可以移动
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R(角);
        }
        else
        {
            restart = 1;
        }
    }
    
    //B（角）----------------------------------------
    else if (array[xi][yi] == B(角))
    {
        if (yj > yi && xj < xi)//位於座標右上
        {
            for (int i = 1; i < xi-xj+1 ; i ++)
            {
                if (array[xi-i][yi+i] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
           }
        }
        if (yj < yi && xj < xi)//位於座標左上
        {
            for (int i = 1; i < xi-xj+1 ; i ++)
            {
                if (array[xi-i][yi-i] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
           }
        }if (yj < yi && xj > xi)//位於座標左下
        {
            for (int i = 1; i < xj-xi+1 ; i ++)
            {
                if (array[xi+i][yi-i] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
           }
        }
        if (yj > yi && xj > xi)//位於座標右下
        {
            for (int i = 1; i < xj-xi+1 ; i ++)
            {
                if (array[xi+i][yi+i] != CROSS)
                    isStandard = 0;//如果初始位置和目标位置之间有棋子，则不符合规则
           }
        }
        if ((abs(xi - xj) == abs(yi - yj))&& isStandard && redOrBlack(xj, yj) != -1)//如果棋子為對角、没有犯规且落点不是红棋，可以移动
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(角);
        }
        else
        {
            restart = 1;
        }
    }
    //R（步）----------------------------------------
    else if (array[xi][yi] == R(步))
    {
        if (xi > xj)
            isStandard = 0;//如果倒退，则不符合规范
        if ((xi + 1 == xj && yi == yj)&& isStandard && redOrBlack(xj, yj) != 1)//
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R (步);
        }
        else
        {
            restart = 1;
        }
    }
    
    //B（步）----------------------------------------
    else if (array[xi][yi] == B(步))
    {
        if (xi < xj)
            isStandard = 0;//如果倒退，则不符合规范
        if ((xi - 1 == xj && yi == yj)&& isStandard && redOrBlack(xj, yj) != -1)//
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B (步);
        }
        else
        {
            restart = 1;
        }
    }

    //R（銀）----------------------------------------
    else if (array[xi][yi] == R(銀))
    {
        if (array[xj][yj] != CROSS)
        {
            isStandard = 0;//代表有旗子錯誤
        }
        if (((xj==xi+1&&yj==yj-1)||(xj==xi+1&&yj==yj)||(xj==xi+1 && yj==yj+1)||(xj==xi-1 && yj==yj-1)||(xj==xi-1 && yj==yj+1)) && isStandard && redOrBlack(xj, yj) != 1)
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R(銀);
        }
        else
        {
            restart = 1;
        }
    }
    
    //B（銀）----------------------------------------
    else if (array[xi][yi] == B(銀))
    {
        if (array[xj][yj] != CROSS)
        {
            isStandard = 0;//代表有旗子錯誤
        }
        if (((xj==xi-1&&yj==yj-1)||(xj==xi-1&&yj==yj)||(xj==xi-1 && yj==yj+1)||(xj==xi+1 && yj==yj-1)||(xj==xi+1 && yj==yj+1)) && isStandard && redOrBlack(xj, yj) != -1)
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(銀);
        }
        else
        {
            restart = 1;
        }
    }

    //R（金）----------------------------------------
    else if (array[xi][yi] == R(金))
    {
        if (array[xj][yj] != CROSS)
        {
            isStandard = 0;//代表有旗子錯誤
        }
        if (((xj==xi+1&&yj==yj-1)||(xj==xi+1&&yj==yj)||(xj==xi+1 && yj==yj+1)||(xj==xi-1 && yj==yj-1)||(xj==xi-1 && yj==yj+1)) && isStandard && redOrBlack(xj, yj) != 1)
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R(金);
        }
        else
        {
            restart = 1;
        }
    }

    //B（金）----------------------------------------
    else if (array[xi][yi] == B(金))
    {
        if (array[xj][yj] != CROSS)
        {
            isStandard = 0;//代表有旗子錯誤
        }
        if (((xj==xi-1&&yj==yj-1)||(xj==xi-1&&yj==yj)||(xj==xi-1 && yj==yj+1)||(xj==xi+1 && yj==yj+1)||(xj==xi-1 && yj==yj+1)) && isStandard && redOrBlack(xj, yj) != -1)
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(金);
        }
        else
        {
            restart = 1;
        }
    }

    //R（王）----------------------------------------
    else if (array[xi][yi] == R(王))
    {
        if (array[xj][yj] != CROSS)
        {
            isStandard = 0;//代表有旗子錯誤
        }
        if (((xj==xi+1&&yj==yj-1)||(xj==xi+1&&yj==yj)||(xj==xi+1 && yj==yj+1)||(xj==xi-1 && yj==yj-1)||(xj==xi-1 && yj==yj+1||(xj==xi-1 && yj==yj||(xj==xi && yj==yj-1)||(xj==xi && yj==yj+1)))) && isStandard && redOrBlack(xj, yj) != 1)
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R(王);
        }
        else
        {
            restart = 1;
        }
    }

    //B（王）----------------------------------------
    else if (array[xi][yi] == B(王))
    {
        if (array[xj][yj] != CROSS)
        {
            isStandard = 0;//代表有旗子錯誤
        }
        if (((xj==xi+1&&yj==yj-1)||(xj==xi+1&&yj==yj)||(xj==xi+1 && yj==yj+1)||(xj==xi-1 && yj==yj-1)||(xj==xi-1 && yj==yj+1||(xj==xi-1 && yj==yj||(xj==xi && yj==yj-1)||(xj==xi && yj==yj+1)))) && isStandard && redOrBlack(xj, yj) != -1)
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R(王);
        }
        else
        {
            restart = 1;
        }
    }
}
