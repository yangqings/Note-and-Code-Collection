#include <iostream>
using namespace std;

int main(void)
{
    int a = 0, b = 0;
    while(scanf("%d %d\n",&a, &b) != EOF){
        printf("%d\n",(a+b));
    }
    return 0;
}