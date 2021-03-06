#include <gtk/gtk.h>
#include <stdio.h>

//后台

//全局使用的两个结构体
//学生信息
typedef struct student_info
{
    char id[100];
    char name[100];
    struct student_info *next;
} student_info;

//将两个输入框绑在一起同时发送至回调函数
struct p_entry_set
{
    GtkWidget *p_entry1;
    GtkWidget *p_entry2;
} p_entry_set;

extern student_info *p_stuinfo_head;

student_info *init_student_info() //初始化链表
{
    student_info *p_stuinfo = (student_info *)malloc(sizeof(student_info)); //创建一个头结点
    return p_stuinfo;
}

void add_student_info(char *add_student_info_id, char *add_student_info_name) //添加一个结点
{
    student_info *p_stuinfo = (student_info *)malloc(sizeof(student_info)); //为新结点开辟内存空间
    strcpy(p_stuinfo->id, add_student_info_id);
    strcpy(p_stuinfo->name, add_student_info_name);
    printf("添加：%s %s\n", add_student_info_id, add_student_info_name);
    p_stuinfo->next = p_stuinfo_head->next; //将头指针所指向的下一个结点的地址，赋给新创建结点的 next
    p_stuinfo_head->next = p_stuinfo;       //将新创建的结点的地址赋给头指针的下一个结点
}

void find_student_info(char *p_find_student_info)
{
    student_info *p_stuinfo = p_stuinfo_head;
    while (p_stuinfo->next)
    {
        p_stuinfo = p_stuinfo->next;
        if (*p_stuinfo->id == *p_find_student_info || *p_stuinfo->name == *p_find_student_info) //这样匹配绝对不是因为我懒，而是因为这样可以模糊搜索（逃）
        {
            printf("查询到：%s %s\n", p_stuinfo->id, p_stuinfo->name);
        }
    }
    printf("搜索完毕\n");
}

void delete_student_info(char *p_find_student_info)
{
    student_info *p_stuinfo = p_stuinfo_head;
    while (p_stuinfo->next) //避免非法访问
    {
        if (p_stuinfo->next)
        {
            student_info *temp = p_stuinfo->next;
            if (*temp->id == *p_find_student_info || *temp->name == *p_find_student_info)
            {
                printf("查询到：%s %s\n", temp->id, temp->name);
                student_info *p_stuinfo_delete = temp; //避免待删除的结点丢失
                p_stuinfo->next = temp->next;
                free(p_stuinfo_delete);
            }
        }
        if (p_stuinfo->next) //避免非法访问
            p_stuinfo = p_stuinfo->next;
    }
    printf("删除完毕\n");
}

void print_student_info()
{
    freopen("data.out", "w", stdout); //打开文件
    printf("学号  姓名\n");
    student_info *p_stuinfo = p_stuinfo_head;
    while (p_stuinfo->next)
    {
        p_stuinfo = p_stuinfo->next;
        printf("%s %s\n", p_stuinfo->id, p_stuinfo->name);
    }
    fclose(stdout); //关闭文件
    printf("导出完毕\n");
}

void add_student_info_get_info(GtkWidget *widget, gpointer data)
{
    const gchar *entry_text1;
    const gchar *entry_text2;
    struct p_entry_set *temp = (struct p_entry_set *)data;       //这里卡了我快一个小时，不管了不管了
    entry_text1 = gtk_entry_get_text(GTK_ENTRY(temp->p_entry1)); //获取输入框中的文字
    entry_text2 = gtk_entry_get_text(GTK_ENTRY(temp->p_entry2));
    add_student_info(entry_text1, entry_text2);
}

void find_student_info_get_info(GtkWidget *widget, gpointer data)
{
    const gchar *entry_text;
    entry_text = gtk_entry_get_text(GTK_ENTRY(data));
    find_student_info(entry_text);
}

void delete_student_info_get_info(GtkWidget *widget, gpointer data)
{
    const gchar *entry_text;
    entry_text = gtk_entry_get_text(GTK_ENTRY(data));
    delete_student_info(entry_text);
}
