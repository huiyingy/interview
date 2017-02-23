#include <stdio.h>
#include <assert.h>
#include <queue>
#include <utility>
#include <cmath>


#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

int aux_read(const char* input, int & j, int len){
    int n = 0;
    while(j<len && (input[j]==',' || input[j]=='\n') ){
        j++;
    }
    if(j>=len )
        return 0;
    for (;j<len;j++)
    {
            if(input[j]!='\n' && input[j]!=',' ){
                n *=10;
                n += input[j]-'0';
            }
            else break;
    }

    return  n;
}

int aux_resolve(int array[][3],int n ){

    int cur_x,cur_h = 0;
    int pre_x=0,pre_h ;
    int i =0;
    std::priority_queue<std::pair<int,int>> pq;
    int sum = 0;
    while(!pq.empty() || i<n  ){
        cur_x = pq.empty()?array[i][0]: pq.top().second;
        

        while(i<n && cur_x >= array[i][0] ){
            if(array[i][2]>cur_h ){
                cur_x = array[i][0];
            }
            pq.push(std::make_pair(array[i][2],array[i][1] ) );
            i++;
        }

        while(!pq.empty() && pq.top().second<=cur_x ){
            pq.pop();
        }

        pre_h = cur_h;
        cur_h = pq.empty()? 0:pq.top().first;

        //计算
        sum += (cur_x-pre_x )+ abs(cur_h- pre_h);
        pre_x = cur_x;

       // printf("%d %d\n",cur_x,cur_h );

    }

    return sum;

};

int resolve(const char* input)
{

    int len = strlen(input);
    int j=0,n;
    n = aux_read(input,j,len );

    int (*p)[3]= new int[n][3];

    for (int i = 0; i < n; ++i)
    {
        for (int k = 0; k < 3; ++k)
        {
            p[i][k] = aux_read(input,j,len );
            //printf("%d ",p[i][k] );
        }//printf("\n");
    }


    int tp = aux_resolve(p,n );
    delete []p;
    return tp;
}



int main(int argc, char* argv[]) 
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
        //TODO please add more test case here
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
        
    }
    return 0;
}
