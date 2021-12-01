#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void driverForMenu_4(int m,int n,int arr[][n]);
void driverForMenu_5(int m,int n,int arr[][n]);


void plot(char *fname){
    int pid;
    if((pid = fork())==0){
        if(execlp("python3", "python3","visualise.py",fname,(char*)NULL)==-1){
            execlp("python3", "python3","visualise.py",fname,(char*)NULL);
        };
    }
    exit(0);
}

char str[10000][1000];//assuming there are not more than 10000 websites and none has length more than 1000 letters

//main menu
void mainMenu()
{
    printf("\n");
    printf("*********************************************Main Menu********************************************* \n");
    printf("1. Does every website has a link to itself?\n");
    printf("2. Is it possible to always return back to the previous website from the current website in one step?\n");
    printf("3. Does every website has all the links to the websites which are reachable from it?\n");
    printf("4. Does there exist any website that contains a link to itself?\n");
    printf("5. Is it impossible to return to the previous website from the current website in one step?\n");
    printf("6. Is it impossible to return to the previous website from the current website in one step (excluding the cases where the current and the previous website is same)?\n");
    printf("7. Is it possible to divide the network into multiple pieces such that every website in a piece is reachable from every other website in that piece?\n");
    printf("8. Is this relation an example of poset?\n");
    printf("9. Exit\n");
}
int minimum(int a,int b)
{
    if(a<b)
        return a;
    else
        return b;
}

void print(int m,int n,int arr[][n])
{
    printf("Array formed is as follows: \n");
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}

//methods present for main menu
int everyLinkItself(int m,int n,int arr[][n])
{
    int flag=0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j && arr[i][j]!=1)
            {
                flag=1;//raising a flag
                return 0;
            }
        }
    }
    return 1;
}

int oneStepPrevWebsite(int m,int n,int arr[][n])
{
    int flag=0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==1 && arr[j][i]==0)
                return 0;
        }
    }
    return 1;
}

int allReachable(int m,int n,int arr[][n])
{
    int D[m][n];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            D[i][j]=arr[i][j];
        }
    }
    for(int k=0;k<m;k++)
    {
        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(D[i][j]==1)
                    continue;
                else if(D[i][k]==1 && D[k][j]==1)
                {
                    D[i][j]=1;
                }
            }
        }
    }
    //print(m,n,D);
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]!=D[i][j])
                return 0;
        }
    }
    return 1;
}

int linkItself(int m,int n,int arr[][n])
{
    for(int i=0;i<m;i++)
    {
        if(arr[i][i]==1)
            return 1;
    }
    return 0;
}

int isImpossibe_1(int m,int n,int arr[][n])
{
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==1 && arr[j][i]==1)
            {
                return 0;
            }
        }
    }
    return 1;
}

int isImpossibe_2(int m,int n,int arr[][n])
{
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==1 && arr[j][i]==1 && i!=j)
            {
                return 0;
            }
        }
    }
    return 1;
}

int dividePiece(int m,int n,int arr[][n])
{
    for(int i=0;i<m;i++)
    {
        if(arr[i][i]!=1)//reflexive check
            return 0;
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==0)
                continue;
            if(!(arr[i][j]==1 && arr[j][i]==1))//symmetric check
            {
                return 0;
            }
        }
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==1)
            {
                for(int k=0;k<n;k++)
                {
                    if(arr[j][k]==1 && arr[i][k]==0)//transitive check
                    {
                           return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int isPoset(int m,int n,int arr[][n])
{
    for(int i=0;i<m;i++)
    {
        if(arr[i][i]==0)
            return 0;
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==1 && arr[j][i]==1 && i!=j)
                return 0;
        }
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==1)
            {
                for(int k=0;k<n;k++)
                {
                    if(arr[j][k]==1 && arr[i][k]==0)//transitive check
                    {
                           return 0;
                    }
                }
            }
        }
    }
    return 1;
    
}

void toExit()
{
    exit(0);
}

//methods for menu 2
void menu_2()
{
    printf("\n");
    printf("*********************************************Menu 2********************************************* \n");
    printf("Do you want to visualise how the network will look if we add minimum links to satisfy the property? \n");
}

void satisfyLinkItself(int m,int n,int arr[][n])//method to make relation reflexive
{
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
            {
                arr[i][j]=1;
            }
        }
    }

    //writing in another file
    FILE *fp;
    fp=fopen("menu2.csv","w");

    FILE *fp1;
    fp1=fopen("SampleInput.csv","r");

    for(char c=getc(fp1);c!='\n';c=getc(fp1))
    {
        putc(c,fp);
    }
    putc('\n',fp);
    int i=0,j=0;
    for(char c=getc(fp1);c!=EOF;c=getc(fp1))
    {
        if(c=='\n')
        {
            i++;
            j=0;
        }
        if(c!='1' && c!='0')
        {
            putc(c,fp);
        }
        else
        {
            putc((char)(arr[i][j]+'0'),fp);
            j++;
        }
    }
    fclose(fp1);
    fclose(fp);
    plot("menu2.csv");
}

void satisfyPrevWebsite(int m,int n,int arr[][n])//making relation symmetric
{
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==1)
            {
                arr[j][i]=1;
            }
        }
    }

    //writing to a different file
    FILE *fp;
    fp=fopen("menu2.csv","w");

    FILE *fp1;
    fp1=fopen("SampleInput.csv","r");

    for(char c=getc(fp1);c!='\n';c=getc(fp1))
    {
        putc(c,fp);
    }
    putc('\n',fp);
    int i=0,j=0;
    for(char c=getc(fp1);c!=EOF;c=getc(fp1))
    {
        if(c=='\n')
        {
            i++;
            j=0;
        }
        if(c!='1' && c!='0')
        {
            putc(c,fp);
        }
        else
        {
            putc((char)(arr[i][j]+'0'),fp);
            j++;
        }
    }
    fclose(fp1);
    fclose(fp);
    plot("menu2.csv");
}

void satisfyAllReachable(int m,int n,int arr[][n])
{
    //aplying floyd warshall algorithm
    int D[m][n];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            D[i][j]=arr[i][j];
        }
    }

    for(int k=0;k<m;k++)
    {
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(D[i][j]==1)//implies a direct connection
                    continue;
                else if(D[i][k]==1 && D[k][j]==1)//implies we need to make a connection
                {
                    D[i][j]=1;
                }
            }
            
        }
    }
    //storing into original matrix
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            arr[i][j]=D[i][j];
        }
    }

    //writing to another file
    FILE *fp;
    fp=fopen("menu2.csv","w");

    FILE *fp1;
    fp1=fopen("SampleInput.csv","r");

    for(char c=getc(fp1);c!='\n';c=getc(fp1))
    {
        putc(c,fp);
    }
    putc('\n',fp);
    int i=0,j=0;
    for(char c=getc(fp1);c!=EOF;c=getc(fp1))
    {
        if(c=='\n')
        {
            i++;
            j=0;
        }
        if(c!='1' && c!='0')
        {
            putc(c,fp);
        }
        else
        {
            putc((char)(arr[i][j]+'0'),fp);
            j++;
        }
    }
    fclose(fp1);
    fclose(fp);
    plot("menu2.csv");
}

void satisfyDividePiece(int m,int n,int arr[][n])//making relation equivalence
{
    for(int i=0;i<m;i++)
    {
        arr[i][i]=1;//making reflexive
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==0)
                continue;
            else
            {
                arr[j][i]=1;//making symmetric
            }
        }
    }
    //making transitive
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==1)
            {
                for(int k=0;k<n;k++)
                {
                    if(arr[j][k]==1)
                    {
                           arr[i][k]=1;
                    }
                }
            }
        }
    }
    //storing into file from array
    FILE *fp;
    fp=fopen("menu2.csv","w");

    FILE *fp1;
    fp1=fopen("SampleInput.csv","r");

    for(char c=getc(fp1);c!='\n';c=getc(fp1))
    {
        putc(c,fp);
    }
    putc('\n',fp);
    int i=0,j=0;
    for(char c=getc(fp1);c!=EOF;c=getc(fp1))
    {
        if(c=='\n')
        {
            i++;
            j=0;
        }
        if(c!='1' && c!='0')
        {
            putc(c,fp);
        }
        else
        {
            putc((char)(arr[i][j]+'0'),fp);
            j++;
        }
    }
    fclose(fp1);
    fclose(fp);
    plot("menu2.csv");
}

//methods for menu 3
void menu_3()
{
    printf("\n");
    printf("*********************************************Menu 3********************************************* \n");
    printf("Do you want to know the nodes in each piece? \n");
}

void nodesInEachPiece(int m,int n,int arr[][n])//to display the equivalence classes/partitions
{
    bool cover[n];
    int cnt=1;
    for(int i=0;i<n;i++)
    {
        cover[i]=false;
    }
    for(int i=0;i<n;i++)
    {
        if(cover[i])
            continue;
        bool s[n];
        for(int j=0;j<n;j++)
        {
            s[j]=false;//making 0 at every instance
        }
        s[i]=true;
        for(int j=i+1;j<n;j++)
        {
            if(arr[i][j]==1)
            {
                cover[j]=true;
                s[j]=true;
            }
        }

        printf("Equivalence class %d {", cnt++);
        for(int k=0;k<n;k++)
        {
            if(s[k]==true)
            {
                printf("%s",str[k+1]);
            }
        }
        printf("}\n");
    }
}


//methods for menu 4
void menu_4()
{
    printf("\n");
    printf("*********************************************Menu 4********************************************* \n");
    printf("1. Display the hasse diagram.\n");
    printf("2. Display the website whose link is available in every website.\n");
    printf("3. Display the website which has links of every website.\n");
    printf("4. Display the website that do not have links to any other website except itself.\n");
    printf("5. Display the websites which can't be reached from any other website except itself.\n");
    printf("6. Given some websites, display the websites which are reachable from all of them.\n");
    printf("7. Given some websites, display the websites from which you can reach all those websites.\n");
    printf("8. Is this relation an example of lattice?\n");
    printf("9. Return to Main Menu.\n");
}

void displayHasse(int m,int n,int arr[][n])
{
    for(int i=0;i<m;i++)
    {
        arr[i][i]=0;//making irreflexive
    }

    //transitive reduction
    for(int j=0;j<n;j++)
    {
        for(int i=0;i<m;i++)
        {
            if(arr[i][j]==1)
            {
                for(int k=0;k<n;k++)
                {
                    if(arr[j][k]==1)
                    {
                        arr[i][k]=0;
                    }
                }
            }
        }
    }

    //writing array to another file
    FILE *fp;
    fp=fopen("menu4.csv","w");

    FILE *fp1;
    fp1=fopen("SampleInput.csv","r");

    for(char c=getc(fp1);c!='\n';c=getc(fp1))
    {
        putc(c,fp);
    }
    putc('\n',fp);
    int i=0,j=0;
    for(char c=getc(fp1);c!=EOF;c=getc(fp1))
    {
        if(c=='\n')
        {
            i++;
            j=0;
        }
        if(c!='1' && c!='0')
        {
            putc(c,fp);
        }
        else
        {
            putc((char)(arr[i][j]+'0'),fp);
            j++;
        }
    }
    fclose(fp1);
    fclose(fp);
    plot("menu4.csv");
}

void displayWebsite_1(int m,int n,int arr[][n])
{
    int flag=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(arr[j][i]==0)
            {
                flag=1;//flag raised that this webiste is not present in every website
                break;
            }
        }
        if(flag==0)
        {
            printf("%s \n", str[i+1]);
        }
        flag=0;
    }
}

void displayWebsite_2(int m,int n,int arr[][n])
{
    int flag=0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==0)
            {
                flag=1;//flag raised that this webiste is not present in every website
                break;
            }
        }
        if(flag==0)
        {
            printf("%s \n", str[i+1]);
        }
        flag=0;
    }
}

void displayWebsite_3(int m,int n,int arr[][n])
{
    int flag=0;
    for(int i=0;i<m;i++)
    {
        if(arr[i][i]==0)
            continue;
        for(int j=0;j<n;j++)
        {
            if(arr[i][j]==1 && i!=j)
            {
                flag=1;//flag raised that this webiste is not present in every website
                break;
            }
        }
        if(flag==0)
        {
            printf("%s \n", str[i+1]);
        }
        flag=0;
    }
}

void displayWebsite_4(int m,int n,int arr[][n])
{
    int D[m][n];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            D[i][j]=arr[i][j];
        }
    }
    for(int k=0;k<m;k++)
    {
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(D[i][j]==1)
                    continue;
                else if(D[i][k]==1 && D[k][j]==1)
                {
                    D[i][j]=1;
                }
            }
            
        }
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            arr[i][j]=D[i][j];
        }
    }
    int flag=0;
    for(int i=0;i<n;i++)
    {
        if(arr[i][i]==0)
            continue;
        for(int j=0;j<m;j++)
        {
            if(arr[j][i]==1 && i!=j)
            {
                flag=1;//flag raised that this webiste is not present in every website
                break;
            }
        }
        if(flag==0)
        {
            printf("%s \n", str[i+1]);
        }
        flag=0;
    }
}
void displayWebsite_5(int m,int n,int arr[][n])
{
    printf("Please enter the number of websites you want to check? \n");
    int num;
    scanf(" %d", &num);
    int temp[num];
    for(int i=0;i<num;i++)
    {
        int val;
        printf("Enter the website index: \n");
        scanf(" %d", &val);
        temp[i]=val;
    }
    int D[m][n];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            D[i][j]=arr[i][j];
        }
    }
    for(int k=0;k<m;k++)
    {
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(D[i][j]==1)
                    continue;
                else if(D[i][k]==1 && D[k][j]==1)
                {
                    D[i][j]=1;
                }
            }
            
        }
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            arr[i][j]=D[i][j];
        }
    }

    for(int i=0;i<n;i++)
    {
        int bit=1;
        for(int j=0;j<num;j++)
        {
            bit=bit&arr[temp[j]][i];
        }
        if(bit==1)
        {
            printf("%s \n", str[i+1]);
        }
    }
}

void displayWebsite_6(int m,int n,int arr[][n])
{
    printf("Please enter the number of websites you want to check? \n");
    int num;
    scanf(" %d", &num);
    int temp[num];
    for(int i=0;i<num;i++)
    {
        int val;
        printf("Enter the website index: \n");
        scanf(" %d", &val);
        temp[i]=val;
    }
    int D[m][n];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            D[i][j]=arr[i][j];
        }
    }
    for(int k=1;k<=m;k++)
    {
        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(D[i][j]==1)
                    continue;
                else if(D[i][k]==1 && D[k][j]==1)
                {
                    D[i][j]=1;
                }
            }
            
        }
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            arr[i][j]=D[i][j];
        }
    }

    for(int i=0;i<m;i++)
    {
        int bit=1;
        for(int j=0;j<num;j++)
        {
            bit=bit&arr[i][temp[j]];
        }
        if(bit==1)
        {
            printf("%s \n", str[i+1]);
        }
    }
}


int lub(int p,int q,int m,int n,int arr[][n])
{  
    FILE *fp;
    fp=fopen("SampleInput.csv","r");
        for(char c=getc(fp);c!='\n';c=getc(fp))//skipping first line
        {

        }
        for(int i=0;i<m;i++)
        {
            int cnt=0;
            for(char c=getc(fp);c!='\n';c=getc(fp))
            {
                if(c=='0' || c=='1')
                {
                    arr[i][cnt]=(int)(c-'0');
                    cnt++;
                }
            }
        }
        fclose(fp);
    int D[m][n];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            D[i][j]=arr[i][j];
        }
    }
    for(int k=0;k<m;k++)
    {
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(D[i][j]==1)
                    continue;
                else if(D[i][k]==1 && D[k][j]==1)
                {
                    D[i][j]=1;
                }
            }
            
        }
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            arr[i][j]=D[i][j];
        }
    }

    int ub[m];//upper bound array
    for(int i=0;i<m;i++)
    {
        ub[i]=0;
    }

    for(int i=0;i<n;i++)
    {
        if(arr[p][i]==1&&arr[q][i]==1){
            ub[i]=1;
        }
    }
    for(int i=0;i<n;i++){
        if(ub[i]==1)
        {
            bool ans=true;
            for(int j=0;ans && j<n;j++)
            {
                if(ub[j]==1 && arr[i][j]==0)
                {
                    ans=false;
                }
            }
            if(ans)return i;
        }
    }
    return -1;

}


int glb(int p,int q,int m,int n,int arr[][n])
{  
    FILE *fp;
    fp=fopen("SampleInput.csv","r");
        for(char c=getc(fp);c!='\n';c=getc(fp))//skipping first line
        {

        }
        for(int i=0;i<m;i++)
        {
            int cnt=0;
            for(char c=getc(fp);c!='\n';c=getc(fp))
            {
                if(c=='0' || c=='1')
                {
                    arr[i][cnt]=(int)(c-'0');
                    cnt++;
                }
            }
        }
        fclose(fp);
    int elem1=p,elem2=q;
    int D[m][n];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            D[i][j]=arr[i][j];
        }
        if(D[i][i]==0)
            D[i][i]=1;
    }
    for(int k=0;k<m;k++)
    {
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(D[i][j]==1)
                    continue;

                else if(D[i][k]==1 && D[k][j]==1)
                {
                    D[i][j]=1;
                }
            }
            
        }
    }
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            arr[i][j]=D[j][i];
        }
    }

    int lb[m];
    for(int i=0;i<m;i++)
    {
        lb[i]=0;
    }

    for(int i=0;i<n;i++)
    {
        if(arr[p][i]==1 && arr[q][i]==1){
            lb[i]=1;
        }
    }

    for(int i=0;i<n;i++){
        if(lb[i]==1)
        {
            bool ans=true;
            for(int j=0;ans && j<n;j++)
            {
                if(lb[j]==1 && arr[i][j]==0)
                {
                    ans=false;
                }
            }
            if(ans)return i;
        }
    }
    return -1;

}

int isLattice(int m,int n,int arr[][n])
{
    for(int i=0;i<m;i++)
    {
        arr[i][i]=0;
    }

    for(int j=0;j<n;j++)
    {
        for(int i=0;i<m;i++)
        {
            if(arr[i][j]==1)
            {
                for(int k=0;k<n;k++)
                {
                    if(arr[j][k]==1)
                    {
                        arr[i][k]=0;
                    }
                }
            }
        }
    }

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
                continue;
            if(glb(i,j,m,n,arr)==-1 || lub(i,j,m,n,arr)==-1)
            {
                //printf("%d %d \n",i,j);
                return 0;
            }
        }
    }
    return 1;
}


//methods for menu 5
void menu_5()
{
    printf("\n");
    printf("*********************************************Menu 5********************************************* \n");
    printf("1. Given two websites A and B, display the website which is reachable by both A and B and can also reach to all such websites that both A and B can reach.\n");
    printf("2. Given two websites A and B, display the website which can reach to both A and B and is also reachable from all such websites which can reach to both A and B.\n");
    printf("3. Is the lattice distributive?\n");
    printf("4. Return to Menu 4\n ");
}

void displayWebsite_7(int m,int n,int arr[][n])
{
    printf("Enter 2 websites index: \n");
    int num1,num2;
    scanf(" %d",&num1);
    scanf(" %d",&num2);
    int index=lub(num1,num2,m,n,arr);
    printf("%s \n", str[index+1]);
}

void displayWebsite_8(int m,int n,int arr[][n])
{
    printf("Enter 2 websites index: \n");
    int num1,num2;
    scanf(" %d %d",&num1,&num2);
    int index=glb(num1,num2,m,n,arr);
    printf("%s \n", str[index+1]);
}

int isDistributive(int m,int n,int arr[][n])
{
    for(int i=0;i<m-2;i++)
    {
        for(int j=i+1;j<n-1;j++)
        {
            for(int k=j+1;j<n;j++)

            if((glb(i,lub(j,k,m,n,arr),m,n,arr)!=lub(glb(i,j,m,n,arr),glb(i,k,m,n,arr),m,n,arr))
                ||(lub(i,glb(j,k,m,n,arr),m,n,arr)!=glb(lub(i,j,m,n,arr),lub(i,k,m,n,arr),m,n,arr)))
                {
                    return 0;
                }
        }
    }
    return 1;
}

void driverForMenu_5(int m,int n,int arr[][n])
{
        int key_3;
        printf("Please enter the option for menu 5: \n");
        scanf("%d", &key_3);

        if(key_3==1)
        {
            displayWebsite_7(m,n,arr);
            mainMenu();
        }
        else if(key_3==2)
        {
            displayWebsite_8(m,n,arr);
            mainMenu();
        }
        else if(key_3==3)
        {
            int ans=isDistributive(m,n,arr);
            if(ans==1)
            {
                printf("Yes \n");
                mainMenu();
            }
            else
            {
                printf("No \n");
                mainMenu();
            }
        }
        else if(key_3==4)
        {
            menu_4();
            driverForMenu_4(m,n,arr);
        }
}

void driverForMenu_4(int m,int n,int arr[][n])
{
    int key_2;
        printf("Please enter the option for menu 4: \n");
        scanf(" %d", &key_2);
        if(key_2==1)
        {
            displayHasse(m,n,arr);
            mainMenu();
        }
        else if(key_2==2)
        {
            displayWebsite_1(m,n,arr);
            mainMenu();
        }
        else if(key_2==3)
        {
            displayWebsite_2(m,n,arr);
            mainMenu();
        }
        else if(key_2==4)
        {
            displayWebsite_3(m,n,arr);
            mainMenu();
        }
        else if(key_2==5)
        {
            displayWebsite_4(m,n,arr);
            mainMenu();
        }
        else if(key_2==6)
        {
            displayWebsite_5(m,n,arr);
            mainMenu();
        }
        else if(key_2==7)
        {
            displayWebsite_6(m,n,arr);
            mainMenu();
        }
        else if(key_2==8)
        {
            int ans=isLattice(m,n,arr);
            if(ans==1)
            {
                printf("Yes \n");
                menu_5();
                driverForMenu_5(m,n,arr);
            }
            else
            {
                printf("No \n");
                mainMenu();
            }
        }
        else if(key_2==9)
        {
            mainMenu();
        }
}    


int main()
{
    FILE *fp;
    fp=fopen("SampleInput.csv","r");


    //first step is to calculate the number of rows and columns. This will help in determining the number of websites.
    int m=0,n=0;
    for(char c=getc(fp);c!=EOF;c=getc(fp))
    {
        if(c=='\n')//encountering end of line
        {
            m++;
        }
    }
    int rows=m-1,col=m-1;
    fclose(fp);

    //taking input in 2d array
    fp=fopen("SampleInput.csv","r");
    int i=0,j=0;
    for(char c=getc(fp);c!='\n';c=getc(fp))
    {
        if(c==',')
        {
            str[i][j]='\0';//so as to terminate the string
            i++;
            j=0;
        }
        else
        {
            str[i][j]=c;
            j++;
        }
    }
    str[i][j]='\0';//so as to terminate the string
    fclose(fp);
    for(int i=0;i<m;i++)
    {
        printf("%s \n",str[i]);
    }
    mainMenu();//to display main menu
    while(1)//so as to keep the loop running
    {   
        
        //taking input in 2d array
        fp=fopen("SampleInput.csv","r");
        for(char c=getc(fp);c!='\n';c=getc(fp))//skipping first line
        {

        }
        int arr[rows][col];
        for(int i=0;i<rows;i++)
        {
            int cnt=0;
            for(char c=getc(fp);c!='\n';c=getc(fp))
            {
                if(c=='0' || c=='1')
                {
                    arr[i][cnt]=(int)(c-'0');
                    cnt++;
                }
            }
        }
        fclose(fp);
        int key;
        printf("Please enter the option: \n");
        scanf("%d", &key);
        if(key==1)//for option one of main menu
        {
            int ans=everyLinkItself(rows,col,arr);
            if(ans==1)
            {
                printf("Yes \n");
                mainMenu();
            }
            else
            {
                printf("No \n");
                menu_2();
                printf("Please enter Y or N: \n");
                char c1;
                scanf(" %c", &c1);
                if(c1=='Y')
                {
                    satisfyLinkItself(rows,col,arr);//method call for satisfying the links
                }
                else
                {
                    mainMenu();
                }
            }
        }
        else if(key==2)//for option 2 of main menu
        {
            int ans=oneStepPrevWebsite(rows,col,arr);
            if(ans==1)
            {
                printf("Yes \n");
                mainMenu();
            }
            else
            {
                printf("No \n");
                menu_2();
                char c1;
                printf("Please enter Y or N: \n");
                scanf(" %c", &c1);
                if(c1=='Y')
                {
                    satisfyPrevWebsite(rows,col,arr);
                }
            
                mainMenu();
            }
        }
        
        else if(key==3)//for option 3 of main menu
        {
            int ans=allReachable(rows,col,arr);
            if(ans==1)
            {
                printf("Yes \n");
                mainMenu();
            }
            else
            {
                printf("No \n");
                menu_2();
                char c1;
                printf("Please enter Y or N: \n");
                scanf(" %c", &c1);
                if(c1=='Y')
                {
                    satisfyAllReachable(rows,col,arr);
                }
                
                mainMenu();
            }
        }
        
        else if(key==4)//for option 4 of main menu
        {
           int ans=linkItself(rows,col,arr);
           if(ans==1)
           {
                printf("Yes \n");
                mainMenu();
           }
           else
           {
                printf("No \n");
                mainMenu();
           }
        }
        else if(key==5)//for option 5 of main menu
        {
            int ans=isImpossibe_1(rows,col,arr);
            if(ans==1)
            {
                printf("Yes \n");
                mainMenu();
            }
           else
           {
                printf("No \n");
                mainMenu();
           }
        }
        else if(key==6)//for option 6 of main menu
        {
            int ans=isImpossibe_2(rows,col,arr); 
            if(ans==1)
            {
                printf("Yes \n");
                mainMenu();
            }
            else
            {
                printf("No \n");
                mainMenu();
            }  
        }
        else if(key==7)//for option 7 of main menu
        {
            int ans=dividePiece(rows,col,arr);
            if(ans==1)
            {
                printf("Yes \n");
                menu_3();
                char c1;
                printf("Please enter Y or N: \n");
                scanf(" %c", &c1);
                if(c1=='Y')
                {
                    nodesInEachPiece(rows,col,arr);
                }
                
                mainMenu();
            }
            else
            {
                printf("No \n");
                menu_2();
                char c1;
                printf("Please enter Y or N: \n");
                scanf(" %c", &c1);
                if(c1=='Y')
                {
                    satisfyDividePiece(rows,col,arr);
                }
                
                mainMenu();
            }
        }
        else if(key==8)//for option 8 of main menu
        {
            int ans=isPoset(rows,col,arr);
            if(ans==1)
            {
                printf("Yes \n");
                menu_4();
                driverForMenu_4(rows,col,arr);
            }
            else
            {
                printf("No \n");
                mainMenu();
            }
        }
        else if(key==9)//for option 9 of main menu
        {
            toExit();//exit method
        }
    }
    return 0;
}