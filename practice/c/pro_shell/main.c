#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#if 0
// 读取输入内容
#define LSH_RL_BUFSIZE 1024
char *lsh_read_line(void)
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize); // 定义一个接受用户输入的 buffer 并申请内存
    int c;

    if (!buffer)
    {
        fprintf(stderr, "lsh: 分配内存发生错误\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // 读取以嗯字符
        c = getchar(); // 保存为𨹝整型而不是char

        // 如果读取的字符是结束符或者换行符，把它替换成空字符然后返回
        // EOF 是一个 int 型，等于 -1
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        // 读取的字符超出 buffer 范围，重新分配内存
        if (position >= bufsize)
        {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "lsh: 分配内存发生错误\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

#else
char *lsh_read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0; // 定义一个 bufsize

    if (getline(&line, &bufsize, stdin) == -1) // getline 函数会给 line 分配内存需要用户自行释放资源
    {
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS); // Ctrl+D 退出
        }
        else
        {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }

    return line; // 返回读取内容
}
#endif

// 解析用户输入
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a:" // 分隔符
char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *)); // 定义一个字符串数组并分配内存
    char *token;                                      // 存放读取的用户的某个输入

    if (!tokens)
    {
        fprintf(stderr, "lsh: 分配内存错误\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM); // 根据给定分隔符获取一个 token
    while (token != NULL)
    {
        tokens[position] = token; // 添加到 token 数组中
        position++;               // 下一个存放位置

        // 根据需要扩展数组大小
        if (position >= bufsize)
        {
            bufsize += LSH_TOK_BUFSIZE; // 扩展一倍
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "lsh: 分配内存错误\n");
                exit(EXIT_FAILURE);
            }
        }

        // 获取下一个参数
        token = strtok(NULL, LSH_TOK_DELIM); // 第二次调用的时候第一个参数必须为 NULL
    }
    tokens[position] = NULL;
    return tokens;
}

// 执行命令
int lsh_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork(); // 创建进程
    if (pid == 0)
    {
        // child 进程
        if (execvp(args[0], args) == -1) // 使用 execvp 系统调用执行命令
        {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        // fork 错误
        perror("lsh");
    }
    else
    {
        // parent 进程
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status)); // 不是 exited 或者 killed 导致 child 进程退出才结束
    }

    return 1;
}

// shell 的 builtin 命令
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

// builtin 命令列表
char *builtin_str[] = {"cd", "help", "exit"};

// builtin 命令对应函数列表
int (*builtin_func[])(char **) = {&lsh_cd, &lsh_help, &lsh_exit};

// 获取 builtin 命令个数
int lsh_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

// builtin 命令实现
int lsh_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0) // 改变进程的工作目录
        {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(char **args)
{
    int i;
    printf("一个简单的 shell\n");
    printf("输入命令和参数然后按回车键执行\n");

    printf("下面是一些已有 builtin 命令详情\n");
    for (i = 0; i < lsh_num_builtins(); i++)
    {
        printf("  %s\n", builtin_str[i]);
    }

    printf("在程序中执行 man + 命令名 查看更多信息\n");
    return 1;
}

int lsh_exit(char **args)
{
    return 0;
}

int lsh_execute(char **args)
{
    int i;

    if (args[0] == NULL)
    {
        // 输入了一个空内容(比如直接按回车)直接返回
        return 1;
    }

    for (i = 0; i < lsh_num_builtins(); i++)
    {
        // 如果第一个参数也就是要执行的命令在定义的命令数组中，执行对应函数并返回执行的结果
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }

    // 不是 builtin 命令则调用 lsh_launch 函数执行其他命令
    return lsh_launch(args);
}

void lsh_loop(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("> ");                // 命令行提示符
        line = lsh_read_line();      // 读取输入
        args = lsh_split_line(line); // 解析输入
        status = lsh_execute(args);  // 执行命令

        // 释放资源
        free(line);
        free(args);

    } while (status);
}

int main()
{
    lsh_loop();

    return EXIT_SUCCESS;
}
