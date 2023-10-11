class skiplist
{
private:
    static constexpr int MAX_LEVEL = 2;
    static constexpr double P = 0.6;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

    struct node
    {
        int data{-1};
        node *next[MAX_LEVEL+1]{};

        node()
        {
            for(int i=1;i<=MAX_LEVEL;i++)
                next[i] = nullptr;
        }
    };

    node *head;

    int randomLevel()
    {
        int ret = 1;
        while(ret<MAX_LEVEL && dis(gen)<P)
            ret++;
        return ret;
    }


public:
    skiplist()
    {
        head = new node;
        gen = std::mt19937(rd());
        dis = std::uniform_real_distribution<> (0,1);
    }

    void insert(int x)
    {
        node *tmp = new node;
        tmp->data = x;
        node *pre[MAX_LEVEL+1];
        node *now = head;
        int level = randomLevel();
        cout<<"level: "<<level<<endl;
        for(int i=MAX_LEVEL;i>=1;i--)
        {
            while(now->next[i] != NULL && now->next[i]->data<x) now = now->next[i];
            pre[i] = now;
        }

        for(int i=level;i>=1;i--)
        {
            tmp->next[i] = pre[i]->next[i];
            pre[i]->next[i] = tmp;
        }
    }

    void print()
    {

        node *now = head->next[2];
        while(now != NULL)
        {
            printf("level0: %d ",now->data);
            now = now->next[2];
        }
        printf("\n");

        node *c= head->next[1];
        while(c != NULL)
        {
            printf("level0: %d ",c->data);
            c = c->next[1];
        }
        printf("\n");
    }
};

#include "opencv2/opencv.hpp"
int main(){
    vector<cv::Point2f>vec;
    vec.emplace_back(1,2);
    vec.emplace_back(3,4);
    cv::Mat xpts(1,2,CV_32F,&vec[0].x,2*sizeof(float));
    cout<<xpts.step<<endl;
    cout<<xpts.step1()<<endl;
    cout<<xpts<<endl;

    cv::AutoBuffer<float> dbuf(10);
    cv::Mat img(1,10,0,dbuf);
    for (int i = 0; i <10 ; ++i) {
        cout<<dbuf[i]<<" ";
    }

    img.setTo(17);

    cout<<endl;
    for (int i = 0; i <10 ; ++i) {
        cout<<dbuf[i]<<" ";
    }



//    skiplist L;
//    for(int i=6;i>=1;i--)
//        L.insert(i);
//    L.print();
}
