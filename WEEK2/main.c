#include <stdio.h>
#include <stdlib.h>

int main(){
    int n,i,choice,count=0,time=0;
    printf("Enter no. of processes: \n");
    scanf("%d",&n);

    int at[n],bt[n],pr[n],ct[n],tat[n],wt[n],rt[n];
    for(i=0;i<n;i++){
        printf("Enter AT,BT and Priority for P%d: ",i+1);
        scanf("%d %d %d",&at[i],&bt[i],&pr[i]);
        rt[i]=bt[i];
    }
    printf("Select Type:\n");
    printf("1. Non preemptive\n");
    printf("2. Preemptive\n");
    printf("Enter choice: ");
    scanf("%d",&choice);

    if(choice==1){
        int completed[n];
        for(i=0;i<n;i++)
            completed[i]=0;

        while(count<n){
            int idx=-1;
            int highest=9999;

            for(i=0;i<n;i++){
                if(at[i]<=time && completed[i]==0){
                    if(pr[i]<highest){
                        highest=pr[i];
                        idx=i;
                    }
                }
            }

            if(idx!=-1){
                time+=bt[idx];

                ct[idx]=time;
                tat[idx]=ct[idx]-at[idx];
                wt[idx]=tat[idx]-bt[idx];

                completed[idx]=1;
                count++;
            }
            else time++;
        }
    }

    else if(choice==2){
        while(count<n){
            int idx=-1;
            int highest=9999;

            for(i=0;i<n;i++){
                if(at[i]<=time && rt[i]>0){
                    if(pr[i]<highest){
                        highest=pr[i];
                        idx=i;
                    }
                }
            }

            if(idx!=-1){
                rt[idx]--;
                time++;

                if(rt[idx]==0){
                    ct[idx]=time;
                    tat[idx]=ct[idx]-at[idx];
                    wt[idx]=tat[idx]-bt[idx];
                    count++;
                }
            }
            else time++;
        }
    }

    else printf("Enter from the choices given!\n");

    printf("\nP\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    float tatsum=0,wtsum=0;

    for(i=0;i<n;i++){
        tatsum+=tat[i];
        wtsum+=wt[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],pr[i],ct[i],tat[i],wt[i]);
    }

    printf("\nAvg TAT: %f\nAvg WT: %f\n",tatsum/n,wtsum/n);

    return 0;
}

