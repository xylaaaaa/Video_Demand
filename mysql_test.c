#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
void add(MYSQL *mysql)
{
    char *sql = "insert into test_tb values(null, 18, '小张', 77.5 )";
    int ret = mysql_query(mysql, sql);
    if (ret != 0)
    {
        printf("query failed:%s\n", mysql_error(mysql));
    }
    return;
}

void mod(MYSQL *mysql)
{
    char *sql = "update test_tb set name='小王' where id = 2";
    int ret = mysql_query(mysql, sql);
    if (ret != 0)
    {
        printf("query failed:%s\n", mysql_error(mysql));
    }
    return;
}
void del(MYSQL *mysql)
{
    char *sql = "delete from test_tb where name='小王';";
    int ret = mysql_query(mysql, sql);
    if (ret != 0)
    {
        printf("query failed:%s\n", mysql_error(mysql));
    }
    return;
}
void get(MYSQL *mysql)
{
    char *sql = "select * from test_tb;";
    int ret = mysql_query(mysql, sql);
    if (ret != 0)
    {
        printf("query failed:%s\n", mysql_error(mysql));
    }
    MYSQL_RES *res = mysql_store_result(mysql);
    if (res == NULL)
    {
        printf("store falied : %s", mysql_error(mysql));
    }
    int row_num = mysql_num_rows(res);
    int col_num = mysql_num_fields(res);
    for (int i = 0; i < row_num; i++)
    {
        MYSQL_ROW row = mysql_fetch_row(res);
        for (int j = 0; j < col_num; j++)
        {
            printf("%s", row[j]);
        }
        printf("\n");
    }
    mysql_free_result(res);
    return;
}
int main()
{
    MYSQL *mysql = mysql_init(NULL);

    if (!mysql_real_connect(mysql, "127.0.0.1", "root", "Chen123@", "test_db", 0, NULL, 0))
    {
        printf("faild : %s\n", mysql_error(mysql));
    }
    mysql_set_character_set(mysql, "utf8mb4");
    add(mysql);
    add(mysql);
    add(mysql);
    mod(mysql);
    del(mysql);
    get(mysql);
    mysql_close(mysql);
    return 0;
}
