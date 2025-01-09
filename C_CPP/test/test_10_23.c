/**
 * 某人准备跑20圈来锻炼自己的身体，他准备分多次(>1)跑完，每次都跑正整数圈，然后休息下再继续跑。
 * 为了有效地提高自己的体能，他决定每次跑的圈数都必须比上次跑的多
 * 设第一次圈数不能小于1，那么请问他可以有多少种跑完这 20 圈的方案?
 * 输出方案总数，以及每种方案的排序。
 * eg. 1 19
 *     1 2 17
 *     1 2 3 14
 *     递归 + 回溯
*/
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

// 最多解决方案个数
#define MAX_SOLUSION    100
// 最大圈数
#define MAX_LAPS        20

// 存储表
int memory_tabel[MAX_SOLUSION][MAX_LAPS];
// 存储方案数量
int memory_solutions = 0;

// 目前方案
int cur_tabel[MAX_LAPS];
// 目前方案的圈数
int cur_solutions_laps = 0;

// 递归 + 回溯
void detailed_solutions(int remain_laps, int min_laps)
{
    // 剩余圈数为零，方案合适入表
    if (remain_laps == 0)
    {
        for (int i = 0; i < cur_solutions_laps; ++i)
        {
            memory_tabel[memory_solutions][i] = cur_tabel[i];
        }
        memory_solutions++;
        return ;
    }
    
    for (int i = min_laps; i <= remain_laps; ++i)
    {
        cur_tabel[cur_solutions_laps++] = i;
        detailed_solutions(remain_laps - i, i + 1);
        cur_solutions_laps--;
    }
}

int main(void)
{
    
    detailed_solutions(MAX_LAPS, 1);

    printf("total solutions = %d\r\n", memory_solutions - 1);
    
    for (int i = 0; i < memory_solutions - 1; ++i)
    {
        for (int j = 0; memory_tabel[i][j] != 0; ++j)
        {
            printf("%d ", memory_tabel[i][j]);
        }
        printf("\r\n");
    }

    return 0;
}