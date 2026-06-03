#include <stdio.h>
#include <limits.h>

int main() {
    int n,i,time=0,done=0,choice;
    int at[10],bt[10],rt[10],ct[10],wt[10],tat[10];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("AT and BT of P%d: ",i+1);
        scanf("%d%d",&at[i],&bt[i]);
        rt[i]=bt[i];
    }

    printf("\nSelect Type:\n");
    printf("1. Non-Preemptive\n");
    printf("2. Preemptive\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if(choice==1){   // Non-preemptive
        int vis[10]={0};
        while(done<n){
            int min=INT_MAX,p=-1;
            for(i=0;i<n;i++)
                if(at[i]<=time && !vis[i] && bt[i]<min){
                    min=bt[i]; p=i;
                }
            if(p==-1){
                time++;
                continue;
            }

            time+=bt[p];
            ct[p]=time;
            vis[p]=1;
            done++;
        }
    }
    else{  // Preemptive (SRTF)
        while(done<n){
            int min=INT_MAX,p=-1;
            for(i=0;i<n;i++)
                if(at[i]<=time && rt[i]>0 && rt[i]<min){
                    min=rt[i]; p=i;
                }
            if(p==-1){
                time++;
                continue;
            }

            rt[p]--;
            time++;

            if(rt[p]==0){
                ct[p]=time;
                done++;
            }
        }
    }

    float tat_total=0;
    float wt_total=0;

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        tat_total+=tat[i];
        wt[i]=tat[i]-bt[i];
        wt_total+=wt[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
    }
    printf("Average tat: %f",(tat_total)/n);
    printf("Average wt: %f",(wt_total)/n);
    return 0;
}
